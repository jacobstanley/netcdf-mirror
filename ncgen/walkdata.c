/*********************************************************************
 *   Copyright 2009, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "includes.h"
#include "nciter.h"
#include "odom.h"
#include "offsets.h"

/**************************************************/
/* Code for generating data lists*/
/**************************************************/
/* For datalist constant rules: see the rules on the man page */

/* Forward*/
static void generate_array(Symbol*,Bytebuffer*,Datasrc*,Odometer*,int,Datalist*,Generator*);
static void generate_basetype(Symbol*,Constant*,Bytebuffer*,Datalist*,Generator*);
static void generate_primdata(Symbol*, Constant*, Bytebuffer*, Datalist* fillsrc, Generator*);
static void generate_fieldarray(Symbol*, Constant*, Dimset*, Bytebuffer*, Datalist* fillsrc, Generator*);

/* Mnemonics */
#define VLENLIST1
#define FIELDARRAY 1

void
generate_attrdata(Symbol* asym, Generator* generator, Writer writer)
{
    Symbol* basetype = asym->typ.basetype;
    Bytebuffer* codebuf = NULL; /* capture other decls*/
    nc_type typecode = basetype->typ.typecode;

    codebuf = bbNew();

    if(typecode == NC_CHAR) {
	gen_charattr(asym->data,codebuf);
    } else {
	int uid;
	size_t count;
        generator->listbegin(generator,ATTRLIST,asym->data->length,codebuf,NULL,&uid);
        for(count=0;count<asym->data->length;count++) {
	    Constant* con = datalistith(asym->data,count);
	    generator->list(generator,ATTRLIST,uid,count,codebuf,NULL);
            generate_basetype(asym->typ.basetype,con,codebuf,NULL,generator);
	}
        generator->listend(generator,ATTRLIST,uid,count,codebuf,NULL);
    }

    writer(asym,codebuf,0,NULL,NULL);

    bbFree(codebuf);
}

void
generate_vardata(Symbol* vsym, Generator* generator, Writer writer)
{
    Dimset* dimset = &vsym->typ.dimset;
    int isscalar = (dimset->ndims == 0);
    Bytebuffer* code = NULL;
    Datalist* fillsrc = NULL;
    Odometer* odom = NULL;
    int chartype = (vsym->typ.basetype->typ.typecode == NC_CHAR);
    Datasrc* src = NULL;

    if(vsym->data == NULL) return;

    code = bbNew();
    /* give the buffer a running start to be large enough*/
    bbSetalloc(code, nciterbuffersize);

    /* Fill in the local odometer instance */
    odom = newodometer(&vsym->typ.dimset,NULL,NULL);

    src = datalist2src(vsym->data);
 
    if(!isscalar && chartype) {
        gen_chararray(dimset,vsym->data,code,fillsrc);
	/* patch the odometer to use the right counts */
        writer(vsym,code,odom->rank,odom->start,odom->count);
    } else { /* not character constant */
        fillsrc = vsym->var.special._Fillvalue;
        /* Handle special cases first*/
        if(isscalar) {
            generate_basetype(vsym->typ.basetype,datalistith(vsym->data,0),code,fillsrc,generator);
            writer(vsym,code,0,NULL,NULL);
        } else { /* Non-scalar*/
            nciter_t iter;
            src = datalist2src(vsym->data);
            /* Create an iterator to generate blocks of data */
            nc_get_iter(vsym,nciterbuffersize,&iter);
            for(;;) {
                size_t nelems=nc_next_iter(&iter,odom->start,odom->count);
                if(nelems == 0) break;
                generate_array(vsym,code,src,odom,/*index=*/0,fillsrc,generator);
                writer(vsym,code,odom->rank,odom->start,odom->count);
            }
        }
    }
    odometerfree(odom);
    bbFree(code);
    /* See if we have too much data */
    if(srcmore(src)) {
	semerror(srcline(src),"Extra data found at end of datalist");
    }	
}

static void
generate_array(Symbol* vsym,
		  Bytebuffer* codebuf,
		  Datasrc* src,
		  Odometer* odom,
	          int index,
		  Datalist* fillsrc,
		  Generator* generator
		)
{
    int i;
    int rank = odom->rank;
    int pushed = 0;
    size_t count;
    Symbol* basetype = vsym->typ.basetype;
    Dimset* dimset = &vsym->typ.dimset;
    int lastdim = (index == (rank - 1)); /* last dimension*/
    int firstdim = (index == 0); /* first dimension*/
    int isunlimited = dimset->dimsyms[index]->dim.isunlimited;

    ASSERT(index >= 0 && index < rank);

    count = odom->count[index];

    if(!firstdim && isunlimited) {
	SRCPUSH(pushed,src);
    }
   
    if(lastdim) {
        for(i=0;i<count;i++) {
	    Constant* con = srcnext(src);
            generate_basetype(basetype,con,codebuf,fillsrc,generator);
	}
    } else {
        /* now walk count elements and generate recursively */
        for(i=0;i<count;i++) {
	   generate_array(vsym,codebuf,src,odom,index+1,fillsrc,generator);
	}
    }

    if(isunlimited) SRCPOP(pushed,src);

    return;
}

/* Generate an instance of the basetype */
static void
generate_basetype(Symbol* tsym, Constant* con, Bytebuffer* codebuf, Datalist* fillsrc, Generator* generator)
{
    Datalist* data;

    /* Do fill check */
   if(con == NULL || isfillconst(con)) {
	Datalist* filler = getfiller(tsym,fillsrc);
	ASSERT(filler->length == 1);
	con = &filler->data[0];
    }

    switch (tsym->subclass) {

    case NC_ENUM:
    case NC_OPAQUE:
    case NC_PRIM:
	if(islistconst(con)) {
	    semerror(constline(con),"Expected primitive found {..}");
	}
	generate_primdata(tsym,con,codebuf,fillsrc,generator);
	break;

    case NC_COMPOUND: {
	int i;
	if(!islistconst(con)) {/* fail on no compound*/
	    semerror(constline(con),"Compound data must be enclosed in {..}");
        }
	if(con == NULL || isfillconst(con)) {
	    Datalist* filler = getfiller(tsym,fillsrc);
	    ASSERT(filler->length == 1);
	    con = &filler->data[0];
	    if(!islistconst(con))
	        semerror(con->lineno,"Compound data fill value is not enclosed in {..}");
	}
	data = con->value.compoundv;
	generator->compoundbegin(generator,codebuf);
	ASSERT(listlength(tsym->subnodes) >= data->length);
        for(i=0;i<listlength(tsym->subnodes);i++) {
            Symbol* field = (Symbol*)listget(tsym->subnodes,i);
	    con = datalistith(data,i);
            generate_basetype(field,con,codebuf,NULL,generator);
	}
	generator->compoundend(generator,codebuf);
	} break;

    case NC_VLEN: {
	Bytebuffer* vlenbuf;
	if(!islistconst(con)) {
	    semerror(constline(con),"Vlen data must be enclosed in {..}");
        }
        data = con->value.compoundv;
        /* generate the nc_vlen_t instance*/
	vlenbuf = bbNew();	
	if(tsym->typ.basetype->typ.typecode == NC_CHAR) {
	    gen_charvlen(data,vlenbuf);
	    generator->vlenstring(generator,codebuf,vlenbuf);
	} else {
	    int uid;
	    size_t count;
    	    generator->listbegin(generator,VLENLIST,data->length,codebuf,&uid,(void*)vlenbuf);
            for(count=0;count<data->length;count++) {
   	        generator->list(generator,VLENLIST,uid,count,codebuf,vlenbuf);
                generate_basetype(tsym->typ.basetype,datalistith(data,count),vlenbuf,NULL,generator);
	    }
   	    generator->listend(generator,VLENLIST,uid,count,codebuf,(void*)vlenbuf);
	}
	bbFree(vlenbuf);
        } break;

    case NC_FIELD:
	/* enclose in braces if and only if field is an array */
	if(!islistconst(con) && tsym->typ.dimset.ndims > 0)
	    semerror(constline(con),"non-scalar field array data must be enclosed in {..}");	    
	if(tsym->typ.dimset.ndims > 0) {
            generate_fieldarray(tsym->typ.basetype,con,&tsym->typ.dimset,codebuf,fillsrc,generator);
	} else {
	    generate_basetype(tsym->typ.basetype,con,codebuf,NULL,generator);
	}
	break;

    default: PANIC1("generate_basetype: unexpected subclass %d",tsym->subclass);
    }
}

/* Used only for structure field arrays*/
static void
generate_fieldarray(Symbol* basetype, Constant* con, Dimset* dimset,
		 Bytebuffer* codebuf, Datalist* fillsrc, Generator* generator)
{
    int i;
    int chartype = (basetype->typ.typecode == NC_CHAR);
    Datalist* data;

    ASSERT(dimset->ndims > 0);
    ASSERT(islistconst(con));

    data = con->value.compoundv;

    if(chartype) {
	/* Collect the char field in a separate buffer */
	Bytebuffer* charbuf = bbNew();
        gen_chararray(dimset,data,charbuf,fillsrc);	
	generator->charconstant(generator,codebuf,charbuf);
	bbFree(charbuf);
    } else {
	int uid;
	size_t xproduct = crossproduct(dimset,0,0); /* compute total number of elements */
        generator->listbegin(generator,FIELDARRAY,xproduct,codebuf,NULL,&uid);
        for(i=0;i<xproduct;i++) {
	    generator->list(generator,FIELDARRAY,uid,i,codebuf,NULL);
            generate_basetype(basetype,datalistith(data,i),codebuf,NULL,generator);
	}
        generator->listend(generator,FIELDARRAY,uid,i,codebuf,NULL);
    }
}

static void
generate_primdata(Symbol* basetype, Constant* prim, Bytebuffer* codebuf,
		  Datalist* fillsrc, Generator* generator)
{
    Constant target;

    ASSERT(prim->nctype != NC_COMPOUND);

    if(prim == NULL || isfillconst(prim)) {
	Datalist* filler = getfiller(basetype,fillsrc);
	ASSERT(filler->length == 1);
	prim = datalistith(filler,0);
    }

    target.nctype = basetype->typ.typecode;

    switch (target.nctype) {
    case NC_ECONST:
        if(basetype->subclass != NC_ENUM) {
	    semerror(constline(prim),"Conversion to enum not supported (yet)");
	} else {
	    generate_primdata(prim->value.enumv->typ.basetype,prim,codebuf,fillsrc,generator);
	} break;
     case NC_OPAQUE:
	convert1(prim,&target);
	setprimlength(&target,basetype->typ.size*2);
	break;
    default:
	convert1(prim,&target);
	break;
    }
    generator->constant(generator,&target,codebuf);
    
    return;
}
