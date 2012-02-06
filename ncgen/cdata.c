/*********************************************************************
 *   Copyright 2009, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "includes.h"
#include "nciter.h"

#ifdef ENABLE_C

#include <math.h> 

/* Define common functions across stdarg */
static int
c_constant_shared(Generator* generator, Constant* con, Bytebuffer* buf)
{
    Bytebuffer* codetmp = bbNew();
    char* special = NULL;

    switch (con->nctype) {
    case NC_CHAR: { 
	char tmp[64];
	tmp[0] = '\0';
	escapifychar(con->value.charv,tmp,'\'');
	bbCat(codetmp,"'");
	bbCat(codetmp,tmp);
	bbCat(codetmp,"'");
	} break;
    case NC_BYTE:
	bbprintf(codetmp,"%hhd",con->value.int8v);
	break;
    case NC_SHORT:
	bbprintf(codetmp,"%hd",con->value.int16v);
	break;
    case NC_INT:
	bbprintf(codetmp,"%d",con->value.int32v);
	break;
    case NC_FLOAT:
	/* Special case for nanf */
	if(isnan(con->value.floatv))
	    bbprintf(codetmp,"nanf");
	else
	    bbprintf(codetmp,"%f",con->value.floatv);
	break;
    case NC_DOUBLE:
	/* Special case for nan */
	if(isnan(con->value.doublev))
	    bbprintf(codetmp,"nan");
	else
	    bbprintf(codetmp,"%lf",con->value.doublev);
	break;
    case NC_UBYTE:
        bbprintf(codetmp,"%hhu",con->value.uint8v);
	break;
    case NC_USHORT:
	bbprintf(codetmp,"%hu",con->value.uint16v);
	break;
    case NC_UINT:
	bbprintf(codetmp,"%uU",con->value.uint32v);
	break;
    case NC_INT64:
	bbprintf(codetmp,"%lldLL",con->value.int64v);
	break;
    case NC_UINT64:
	bbprintf(codetmp,"%lluLLU",con->value.uint64v);
	break;
    case NC_ECONST:
	bbprintf(codetmp,"%s",cname(con->value.enumv));
	break;
    case NC_STRING: { /* handle separately */
	char* escaped = escapify(con->value.stringv.stringv,
				 '"',con->value.stringv.len);
	special = poolalloc(1+2+strlen(escaped));
	strcpy(special,"\"");
	strcat(special,escaped);
	strcat(special,"\"");
	} break;
    case NC_OPAQUE: {
	char* p;
	int bslen;
	bslen=(4*con->value.opaquev.len);
	special = poolalloc(bslen+2+1);
	strcpy(special,"\"");
	p = con->value.opaquev.stringv;
	while(*p) {
	    strcat(special,"\\x");
	    strncat(special,p,2);	    	    
	    p += 2;	
	}
	strcat(special,"\"");
	} break;

    default: PANIC1("ncstype: bad type code: %d",con->nctype);

    }
    if(special == NULL)
        bbCatbuf(buf,codetmp);
    else
	bbCat(buf,special);
    bbFree(codetmp);
    return 1;
}

static int
c_alignbuffer(Generator* generator, Constant* con, Bytebuffer* buf)
{
    return 1;
}

static int
c_reset(Generator* generator, void* state)
{
    return 1;
}

#ifndef NO_STDARG

static int
c_charconstant(Generator* generator, Bytebuffer* codebuf, ...)
{
    return 1;
}

static int
c_constant(Generator* generator, Constant* con, Bytebuffer* buf,...)
{
    return c_constant_shared(generator,con,buf);
}

static int
c_listbegin(Generator* generator, ListClass lc, size_t size, Bytebuffer* codebuf, int* uidp, ...)
{
    return 1;
}

static int
c_list(Generator* generator, ListClass lc, int uid, size_t count, Bytebuffer* codebuf, ...)
{
    switch (lc) {
    case VLENLIST:
    case ATTRLIST:
        if(index > 0) bbCat(codebuf,", ");
	break;
    case FIELDARRAY:
        bbAppend(codebuf,' ');
	break;
    }
    return 1;
}

static int
c_listend(Generator* generator, ListClass lc, int uid, size_t count, Bytebuffer* buf, ...)
{
    return 1;
}

static int
c_compoundbegin(Generator* generator, Bytebuffer* codebuf,...)
{
    bbAppend(codebuf,'{');
    return 1;
}

static int
c_compoundend(Generator* generator,Bytebuffer* codebuf,...)
{
    bbAppend(codebuf,'}');
    return 1;
}


static int
c_vlenbegin(Generator* generator, Bytebuffer* buf,Symbol* tsym,int uid,...)
{
    Bytebuffer* tmp = bbNew();
    bbprintf0(tmp,"static const %s vlen_%u[] = ",
	        ctypename(tsym->typ.basetype),
                uid);
    bbCatbuf(buf,tmp);
    bbAppend(buf,'{');
    bbFree(tmp);
    return 1;
}

static int
c_vlenend(Generator* generator, Bytebuffer* codebuf,...)
{
    return 1;
}

static int
c_vlenstring(Generator* generator, Bytebuffer* codebuf, ...)
{
    Bytebuffer* vlenmem;
    nc_vlen_t ptr;
    va_list ap;
    vastart(ap,codebuf);
    vlenmem = va_arg(ap, Bytebuffer*);
    va_end(ap);
    ptr.len = bbLength(vlenmem);
    ptr.p = bbDup(vlenmem);
    bbAppendn(codebuf,(char*)&ptr,sizeof(ptr));
    return 1;
}

#else /*NO_STDARG*/

static int
c_primbegin(generator,va_alist)
    Generator* generator; va_dcl
{
    return 1;
}

static int
c_primend(generator,va_alist)
    Generator* generator; va_dcl
{
    return 1;
}

static int
c_charconstant(generator,buf,buf,va_alist)
    Generator* generator; Bytebuffer* buf; Bytebuffer* buf; va_dcl
{
    return 1;
}

static int
c_constant(generator,con,buf,va_alist)
    Generator* generator; Constant* con; Bytebuffer* buf; va_dcl
{
    return c_constant_shared(generator,con,buf);
}

static int
c_listbegin(generator,lc,size,uidp, va_alist)
    Generator* generator; ListClass lc; int size; int* uidp; va_dcl
{
    if(uidp) *uidp = 0; /* not used */
    return 1;
}

static int
c_list(generator,lc,uid,count,buf,va_alist)
    Generator* generator; ListClass lc; int uid; int count; Bytebuffer* buf; va_dcl
{
    return 1;
}

static int
c_listend(generator,lc,uid,count,buf,va_alist)
    Generator* generator; ListClass lc; int uid; int count; Bytebuffer* buf; va_dcl
{
    va_list ap;
    if(listclass == VLENLIST) {
        Bytebuffer* vlenmem;
        nc_vlen_t ptr;
        vastart(argv,buf);
        vlenmem = va_arg(ap, Bytebuffer*)
	va_end(ap);
        ptr.len = count;
        ptr.p = bbDup(vlenmem);
        bbAppendn(buf,(char*)&ptr,sizeof(ptr));
    }
    return 1;
}

static int
c_compoundbegin(generator,va_alist)
    Generator* generator; va_dcl
{
    return 1;
}

static int
c_compoundend(generator,va_alist)
    Generator* generator; va_dcl
{
    return 1;
}

static int
c_vlenbegin(generator, Bytebuffer* buf,Symbol* tsym,int uid,va_alist)
    Generator* generator; Bytebuffer* buf;Symbol* tsym; int uid; va_dcl
{
    return 1;
}

static int
c_vlenend(generator,buf,va_alist)
    Generator* generator; Bytebuffer* buf; va_dcl
{
    return 1;
}

static int
bin_vlenstring(generator,buf,va_alist)
    Generator* generator; Bytebuffer* buf; va_dcl
{
    Bytebuffer* vlenmem;
    nc_vlen_t ptr;
    vastart(argv,buf);
    vlenmem = va_arg(ap, Bytebuffer*)
    va_end(ap);
    ptr.len = count;
    ptr.p = bbDup(vlenmem);
    bbAppendn(buf,(char*)&ptr,sizeof(ptr));
}

#endif /*NO_STDARG*/


/* Define the single static bin data generator  */
static Generator c_generator_singleton = {
    NULL,
    c_reset,
    c_alignbuffer,
    c_charconstant,
    c_constant,
    c_listbegin,
    c_list,
    c_listend,
    c_compoundbegin,
    c_compoundend,
    c_vlenbegin,
    c_vlenend,
    c_vlenstring
};
Generator* c_generator = &c_generator_singleton;

#endif /*ENABLE_C*/
