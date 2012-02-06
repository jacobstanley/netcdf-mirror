/*********************************************************************
 *   Copyright 2009, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "includes.h"
#include "nciter.h"

#ifdef ENABLE_BINARY

/* Define common functions across stdarg */
static int
bin_constant_shared(Generator* generator, Constant* con, Bytebuffer* buf,...)
{
    switch (con->nctype) {
    case NC_OPAQUE: {
        unsigned char* bytes;
        size_t len;
        bytes=makebytestring(con->value.opaquev.stringv,&len);
        bbAppendn(buf,(void*)bytes,len);
        } break;
    case NC_CHAR:
        bbAppendn(buf,&con->value.charv,sizeof(con->value.charv));
        break;
    case NC_BYTE:
        bbAppendn(buf,(void*)&con->value.int8v,sizeof(con->value.int8v));
        break;
    case NC_SHORT:
        bbAppendn(buf,(void*)&con->value.int16v,sizeof(con->value.int16v));
        break;
    case NC_INT:
        bbAppendn(buf,(void*)&con->value.int32v,sizeof(con->value.int32v));
        break;
    case NC_FLOAT:
        bbAppendn(buf,(void*)&con->value.floatv,sizeof(con->value.floatv));
        break;
    case NC_DOUBLE:
        bbAppendn(buf,(void*)&con->value.doublev,sizeof(con->value.doublev));
        break;
    case NC_UBYTE:
        bbAppendn(buf,(void*)&con->value.uint8v,sizeof(con->value.uint8v));
        break;
    case NC_USHORT:
        bbAppendn(buf,(void*)&con->value.uint16v,sizeof(con->value.uint16v));
        break;
    case NC_UINT:
        bbAppendn(buf,(void*)&con->value.uint32v,sizeof(con->value.uint32v));
        break;
    case NC_INT64: {
        union SI64 { char ch[8]; long long i64;} si64;
        si64.i64 = con->value.int64v;
        bbAppendn(buf,(void*)si64.ch,sizeof(si64.ch));
        } break;
    case NC_UINT64: {
        union SU64 { char ch[8]; unsigned long long i64;} su64;
        su64.i64 = con->value.uint64v;
        bbAppendn(buf,(void*)su64.ch,sizeof(su64.ch));
        } break;
    case NC_STRING: {
        char* ptr;
        int len = (size_t)con->value.stringv.len;
        ptr = poolalloc(len+1); /* CAREFUL: this has short lifetime*/
        memcpy(ptr,con->value.stringv.stringv,len);
        ptr[len] = '\0';
        bbAppendn(buf,(void*)&ptr,sizeof(ptr));
        } break;

    default: PANIC1("bin_constant: unexpected type: %d",con->nctype);
    }
    return 1;
}

static int
bin_alignbuffer(Generator* generator, Constant* con, Bytebuffer* buf)
{
    alignbuffer(con,buf);
    return 1;
}

static int
bin_reset(Generator* generator, void* state)
{
    return 1;
}

#ifndef NO_STDARG

static int
bin_charconstant(Generator* generator, Bytebuffer* buf, ...)
{
    return 1;
}

static int
bin_constant(Generator* generator, Constant* con, Bytebuffer* buf,...)
{
    return bin_constant_shared(generator,con,buf);
}

static int
bin_listbegin(Generator* generator, ListClass lc, size_t size, Bytebuffer* buf, int* uidp, ...)
{
    if(uidp) *uidp = 0; /* not used */
    return 1;
}

static int
bin_list(Generator* generator, ListClass lc, int uid, size_t count, Bytebuffer* buf, ...)
{
    return 1;
}

static int
bin_listend(Generator* generator, ListClass lc, int uid, size_t count, Bytebuffer* buf, ...)
{
    va_list ap;
    if(lc == VLENLIST) {
        Bytebuffer* vlenmem;
        nc_vlen_t ptr;
        vastart(ap,buf);
        vlenmem = va_arg(ap, Bytebuffer*);
	va_end(ap);
        ptr.len = count;
        ptr.p = bbDup(vlenmem);
        bbAppendn(buf,(char*)&ptr,sizeof(ptr));
    }
    return 1;
}

static int
bin_compoundbegin(Generator* generator, Bytebuffer* buf, ...)
{
    return 1;
}

static int
bin_compoundend(Generator* generator, Bytebuffer* buf, ...)
{
    return 1;
}


static int
bin_vlenbegin(Generator* generator, Bytebuffer* buf,Symbol* tsym,int uid,...)
{
    return 1;
}

static int
bin_vlenend(Generator* generator, Bytebuffer* buf,...)
{
    return 1;
}

static int
bin_vlenstring(Generator* generator, Bytebuffer* codebuf, ...)
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
bin_charconstant(generator,buf,buf,va_alist)
    Generator* generator; Bytebuffer* buf; Bytebuffer* buf; va_dcl
{
    return 1;
}

static int
bin_constant(generator,con,buf,va_alist)
    Generator* generator; Constant* con; Bytebuffer* buf; va_dcl
{
    return bin_constant_shared(generator,con,buf);
}

static int
bin_listbegin(generator,lc,size,uidp, va_alist)
    Generator* generator; ListClass lc; int size; int* uidp; va_dcl
{
    if(uidp) *uidp = 0; /* not used */
    return 1;
}

static int
bin_list(generator,lc,uid,count,buf,va_alist)
    Generator* generator; ListClass lc; int uid; int count; Bytebuffer* buf; va_dcl
{
    return 1;
}

static int
bin_listend(generator,lc,uid,count,buf,va_alist)
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
bin_compoundbegin(generator,va_alist)
    Generator* generator; va_dcl
{
    return 1;
}

static int
bin_compoundend(generator,va_alist)
    Generator* generator; va_dcl
{
    return 1;
}

static int
bin_vlenbegin(generator, Bytebuffer* buf,Symbol* tsym,int uid,va_alist)
    Generator* generator; Bytebuffer* buf;Symbol* tsym; int uid; va_dcl
{
    return 1;
}

static int
bin_vlenend(generator,buf,va_alist)
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
static Generator bin_generator_singleton = {
    NULL,
    bin_reset,
    bin_alignbuffer,
    bin_charconstant,
    bin_constant,
    bin_listbegin,
    bin_list,
    bin_listend,
    bin_compoundbegin,
    bin_compoundend,
    bin_vlenbegin,
    bin_vlenend,
    bin_vlenstring
};
Generator* bin_generator = &bin_generator_singleton;

#endif /*ENABLE_BINARY*/
