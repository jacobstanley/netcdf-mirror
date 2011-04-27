/* Copyright 2009, UCAR/Unidata and OPeNDAP, Inc.
   See the COPYRIGHT file for more information. */

#ifndef OCDEBUG_H
#define OCDEBUG_H

#include <stdarg.h>
#include "ocdump.h"

#undef OCDEBUG

/* OCCATCHERROR is used to detect errors as close
   to their point of origin as possible. When
   enabled, one can set a breakpoint in ocbreakpoint()
   to catch the failure. Turing it on incurs a significant
   performance penalty, so it is off by default.*/

#define OCCATCHERROR

#define OCPANIC(msg) assert(ocpanic(msg))
#define OCPANIC1(msg,arg) assert(ocpanic(msg,arg))
#define OCPANIC2(msg,arg1,arg2) assert(ocpanic(msg,arg1,arg2))

/* Make it possible to catch assertion failures by breakpointing ocpanic*/
#define OCASSERT(expr) if(!(expr)) {OCPANIC((#expr));} else {}

/* Need some syntactic trickery to make these macros work*/
#ifdef OCDEBUG
#define DEBUG(l,msg) {oc_log(LOGDBG,msg);}
#define DEBUG1(l,msg,arg) {oc_log(LOGDBG,msg,arg);}
#define DEBUG2(l,msg,arg1,arg2) {oc_log(LOGDBG,msg,arg1,arg2);}
#define DEBUGTEXT(l,text) {oc_logtext(LOGNOTE,text);} else {}
#define DEBUGCODE(l,code) {code;}

#else
#define DEBUG(l,msg)
#define DEBUG1(l,msg,arg)
#define DEBUG2(l,msg,arg1,arg2)
#define DEBUGTEXT(l,text)
#define DEBUGCODE(l,code)
#endif


/*
OCPROGRESS attempts to provide some info
about how IO is getting along.
*/
#undef OCPROGRESS

extern int ocdebug;
extern int cedebug;

/*extern char* dent2(int n);*/
/*/extern char* dent(int n);*/
extern int ocpanic(const char* fmt, ...);

extern int xdrerror(void);

/*
Provide wrapped versions of calloc and malloc.
The wrapped version panics if memory
is exhausted.  It also guarantees that the
memory has been zero'd.
*/

extern void* occalloc(size_t size, size_t nelems);
extern void* ocmalloc(size_t size);
extern void  ocfree(void*);

#define MEMCHECK(var,throw) {if((var)==NULL) return (throw);}

#ifdef OCCATCHERROR
/* Place breakpoint on ocbreakpoint to catch errors close to where they occur*/
#define THROW(e) octhrow(e)
#define THROWCHK(e) (void)octhrow(e)
extern int ocbreakpoint(int err);
extern int octhrow(int err);
#else
#define THROW(e) (e)
#define THROWCHK(e)
#endif


#endif /*OCDEBUG_H*/

