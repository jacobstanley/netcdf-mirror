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
static void generate_primdata(Symbol*, Constant*, Bytebuffer*, Datalist* fillsrc, Generator*);
static void generate_fieldarray(Symbol*, Constant*, Dimset*, Bytebuffer*, Datalist* fillsrc, Generator*);

/* Mnemonics */
#define VLENLIST1
#define FIELDARRAY 1

/**************************************************/
/* Generator general procedures */

int
generator_getstate(Generator* generator ,void** statep)
{
    if(statep) *statep = (void*)generator->state;
    return 1;
}

int generator_reset(Generator* generator, void* state)
{
    generator->state = state;
    return 1;
}

/**************************************************/

void
generate_attrdata(Symbol* asym, Generator* generator, Writer writer, Bytebuffer* codebuf)
{
    Symbol* basetype = asym->typ.basetype;
    nc_type typecode = basetype->typ.typecode;

    if(typecode == NC_CHAR) {
	gen_charattr(asym->data,codebuf);
    } else {
	int uid;
	size_t count;
        generator->listbegin(generator,LISTATTR,asym->data->length,codebuf,NULL,&uid);
        for(count=0;count<asym->data->length;count++) {
	    Constant* con = datalistith(asym->data,count);
	    generator->list(generator,LISTATTR,uid,count,codebuf,NULL);
            generate_basetype(asym->typ.basetype,con,codebuf,NULL,generator);
	}
        generator->listend(generator,LISTATTR,uid,count,codebuf,NULL);
    }
    writer(generator,asym,codebuf,0,NULL,NULL);
}

void
generate_vardata(Symbol* vsym, Generator* generator, Writer write, Bytebuffer* code)
{
    Dimset* dimset = &vsym->typ.dimset;
    int isscalar = (dimset->ndims == 0);
    Datalist* fillsrc = NULL;
    Odometer* odom = NULL;
    int chartype = (vsym->typ.basetype->typ.typecode == NC_CHAR);
    Datasrc* src = NULL;

    if(vsym->data == NULL) return;

    /* give the buffer a running start to be large enough*/
    bbSetalloc(code, nciterbuffersize);

    /* Fill in the local odometer instance */
    odom = newodometer(dimset,NULL,NULL);

    if(chartype) { /* Handle separately */
	Bytebuffer* charbuf = bbNew();
        gen_chararray(dimset,vsym->data,charbuf,fillsrc);
	generator->charconstant(generator,code,charbuf);
	bbFree(charbuf);
	/* patch the odometer to use the right counts */
        write(generator,vsym,code,odom->rank,odom->start,odom->count);
    } else { /* not character constant */
        fillsrc = vsym->var.special._Fillvalue;
        /* Handle special cases first*/
        if(isscalar) {
            generate_basetype(vsym->typ.basetype,datalistith(vsym->data,0),code,fillsrc,generator);
            write(generator,vsym,code,0,NULL,NULL);
        } else { /* Non-scalar */
            nciter_t iter;
            src = datalist2src(vsym->data);
            /* Create an iterator to generate blocks of data */
            nc_get_iter(vsym,nciterbuffersize,&iter);
            for(;;) {
                size_t nelems=nc_next_iter(&iter,odom->start,odom->count);
                if(nelems == 0) break;
		odom->counter = nelems;		
                generate_array(vsym,code,src,odom,
                               /*dim index=*/0,
			       fillsrc,generator
			       );
		ASSERT(odom->counter == 0);
                write(generator,vsym,code,odom->rank,odom->start,odom->count);
            }
	    /* See if we have too much data */
	    if(srcmore(src)) {
		semwarn(srcline(src),"Extra data found at end of datalist");
	    }	
	    odometerfree(odom);
        }
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
    Symbol* basetype = vsym->typ.basetype;
    Dimset* dimset = &vsym->typ.dimset;
    int rank = dimset->ndims;
    int lastdim = (index == (rank - 1)); /* last dimension*/
    int isunlimited = dimset->dimsyms[index]->dim.isunlimited;
    int uid;
    size_t count;

    if(odom->counter == 0) return; /* stop writing for now */

    ASSERT(index >= 0 && index < rank);
    ASSERT(basetype->typ.typecode != NC_CHAR);

    count = odom->count[index];

    if(lastdim) {
        /* data should be simple list of basetype objects */
        generator->listbegin(generator,LISTDATA,count,codebuf,&uid);
        for(i=0;i<count && odom->counter > 0;i++) {
            Constant* con = srcnext(src);
            generator->list(generator,LISTDATA,uid,i,codebuf);
            generate_basetype(basetype,con,codebuf,fillsrc,generator);
	    odom->counter--;
        }
        generator->listend(generator,LISTDATA,uid,i,codebuf);
    } else {
	if(index > 0 && !lastdim && isunlimited) srcpush(src);
        /* now walk elements and generate recursively */
        for(i=0;i<count && odom->counter > 0;i++) {
	   generate_array(vsym,codebuf,src,odom,index+1,fillsrc,generator);
	}
	if(index > 0 && !lastdim && isunlimited) srcpop(src);
    }
    return;
}

/* Generate an instance of the basetype */
void
generate_basetype(Symbol* tsym, Constant* con, Bytebuffer* codebuf, Datalist* fillsrc, Generator* generator)
{
    Datalist* data;

#ifdef IGNORE
    /* Do fill check */
   if(con == NULL || isfillconst(con)) {
	Datalist* filler = getfiller(tsym,fillsrc);
	ASSERT(filler->length == 1);
	con = &filler->data[0];
    }
#endif

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
	int i,uid;
	if(con == NULL || isfillconst(con)) {
	    Datalist* filler = getfiller(tsym,fillsrc);
	    ASSERT(filler->length == 1);
	    con = &filler->data[0];
	    if(!islistconst(con))
	        semerror(con->lineno,"Compound data fill value is not enclosed in {..}");
	}
	if(!islistconst(con)) {/* fail on no compound*/
	    semerror(constline(con),"Compound data must be enclosed in {..}");
        }
	data = con->value.compoundv;
	generator->listbegin(generator,LISTCOMPOUND,listlength(tsym->subnodes),codebuf,&uid);
        for(i=0;i<listlength(tsym->subnodes);i++) {
            Symbol* field = (Symbol*)listget(tsym->subnodes,i);
	    con = datalistith(data,i);
	    generator->list(generator,LISTCOMPOUND,uid,i,codebuf);
            generate_basetype(field,con,codebuf,NULL,generator);
	}
	generator->listend(generator,LISTCOMPOUND,uid,i,codebuf);
	} break;

    case NC_VLEN: {
	Bytebuffer* vlenbuf;
        int uid;
	size_t count;

	if(con == NULL || isfillconst(con)) {
	    Datalist* filler = getfiller(tsym,fillsrc);
	    ASSERT(filler->length == 1);
	    con = &filler->data[0];
	    if(con->nctype != NC_COMPOUND) {
	        semerror(con->lineno,"Vlen data fill value is not enclosed in {..}");
	    }
	}

	if(!islistconst(con)) {
	    semerror(constline(con),"Vlen data must be enclosed in {..}");
        }
        data = con->value.compoundv;
        /* generate the nc_vlen_t instance*/
	vlenbuf = bbNew();	
	if(tsym->typ.basetype->typ.typecode == NC_CHAR) {
	    gen_charvlen(data,vlenbuf);
	    generator->vlenstring(generator,vlenbuf,&uid,&count);
	} else {
    	    generator->listbegin(generator,LISTVLEN,data->length,codebuf,&uid);
            for(count=0;count<data->length;count++) {
   	        generator->list(generator,LISTVLEN,uid,count,vlenbuf);
                generate_basetype(tsym->typ.basetype,datalistith(data,count),vlenbuf,NULL,generator);
	    }
   	    generator->listend(generator,LISTVLEN,uid,count,codebuf,(void*)vlenbuf);
	}
	generator->vlendecl(generator,codebuf,tsym,uid,count,vlenbuf);
	bbFree(vlenbuf);
        } break;

    case NC_FIELD:
	if(tsym->typ.dimset.ndims > 0) {
	    /* Verify that we have a sublist (or fill situation) */
	    if(con != NULL && !isfillconst(con) && !islistconst(con)) 
		semerror(constline(con),"Dimensioned fields must be enclose in {...}");
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

    if(con != NULL && !isfillconst(con))
        data = con->value.compoundv;
    else
	data = NULL;

    if(chartype) {
	/* Collect the char field in a separate buffer */
	Bytebuffer* charbuf = bbNew();
        gen_chararray(dimset,data,charbuf,fillsrc);	
	generator->charconstant(generator,codebuf,charbuf);
	bbFree(charbuf);
    } else {
	int uid;
	size_t xproduct = crossproduct(dimset,0,0); /* compute total number of elements */
        generator->listbegin(generator,LISTFIELDARRAY,xproduct,codebuf,NULL,&uid);
        for(i=0;i<xproduct;i++) {
	    con = (data == NULL ? NULL : datalistith(data,i));
	    generator->list(generator,LISTFIELDARRAY,uid,i,codebuf,NULL);
            generate_basetype(basetype,con,codebuf,NULL,generator);
	}
        generator->listend(generator,LISTFIELDARRAY,uid,i,codebuf,NULL);
    }
}

static void
generate_primdata(Symbol* basetype, Constant* prim, Bytebuffer* codebuf,
		  Datalist* fillsrc, Generator* generator)
{
    Constant target;

    if(prim == NULL || isfillconst(prim)) {
	Datalist* filler = getfiller(basetype,fillsrc);
	ASSERT(filler->length == 1);
	prim = datalistith(filler,0);
    }

    ASSERT(prim->nctype != NC_COMPOUND);

    target.nctype = basetype->typ.typecode;

    if(target.nctype != NC_ECONST) {
	convert1(prim,&target);
    }

    switch (target.nctype) {
    case NC_ECONST:
        if(basetype->subclass != NC_ENUM) {
	    semerror(constline(prim),"Conversion to enum not supported (yet)");
	} break;
     case NC_OPAQUE:
	setprimlength(&target,basetype->typ.size*2);
	break;
    default:
	break;
    }
    generator->constant(generator,&target,codebuf);
    
    return;
}
