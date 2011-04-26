/*********************************************************************
 *   Copyright 2010, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Header$
 *********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dapurl.h"

#define DAPURLDEBUG

#define LBRACKET '['
#define RBRACKET ']'

#ifndef FIX
#define FIX(s) ((s)==NULL?"":(s))
#endif

#ifndef NILLEN
#define NILLEN(s) ((s)==NULL?0:strlen(s))
#endif

#ifndef nulldup
#define nulldup(s) ((s)==NULL?NULL:strdup(s))
#endif

static char* legalprotocols[] = {
"file:",
"http:",
"https:",
"ftp:",
NULL /* NULL terminate*/
};

/* Do a simple url parse: return 0 if fail, 1 otherwise*/
int
dapurlparse(const char* url0, DAPURL** dapurlp)
{
    DAPURL* dapurl = NULL;
    char* url;
    char** pp;
    char* p;
    char* p1;
    int c;

    /* accumulate parse points*/
    char* protocol = NULL;
    char* params = NULL;
    char* host = NULL;
    char* port = NULL;
    char* constraint = NULL;
    char* user = NULL;
    char* pwd = NULL;
    char* file = NULL;
    char* stop;

    dapurl = (DAPURL*)calloc(1,sizeof(DAPURL));
    if(dapurl == NULL) return 0;    

    /* make local copy of url */
    url = strdup(url0);

    /* remove all whitespace*/
    p = url;
    p1 = url;
    while((c=*p1++)) {if(c != ' ' && c != '\t') *p++ = c;}

    p = url;
    stop = p + strlen(p);

    /* break up the url string into pieces*/

    /* 1. leading bracketed parameters */
    if(*p == LBRACKET) {
	params = p+1;
	/* find end of the clientparams*/
        for(;*p;p++) {if(p[0] == RBRACKET && p[1] != LBRACKET) break;}
	if(*p == 0) goto fail; /* malformed client params*/
	*p = '\0'; /* leave off the trailing rbracket for now */
	p++; /* move past the params*/
    }

    /* verify that the url starts with an acceptable protocol*/
    for(pp=legalprotocols;*pp;pp++) {
        if(strncmp(p,*pp,strlen(*pp))==0) break;
    }
    if(*pp == NULL) goto fail; /* illegal protocol*/
    /* save the protocol */
    protocol = *pp;

    /* 4. skip protocol */
    p += strlen(protocol);

    /* 5. skip // */
    if(*p != '/' && *(p+1) != '/')
	goto fail;
    p += 2;

    /* 6. Mark the end of the host section */
    file = strchr(p,'/');
    if(file) {
	*file++ = '\0'; /* warning: we just overwrote the leading / */
    }

    /* 7. extract any user:pwd */
    p1 = strchr(p,'@');
    if(p1) {/* Assume we have user:pwd@ */
	*p1 = '\0';
	user = p;
	pwd = strchr(p,':');
	if(!pwd) goto fail; /* malformed */
	*pwd++ = '\0';
	p = pwd+strlen(pwd)+1;
    }

    /* 8. extract host and port */
    host = p;
    port = strchr(p,':');
    if(port) {
	*port++ = '\0';
    }

    /* 9. Look for '?' */
    constraint = strchr(file,'?');
    if(constraint) {
	*constraint++ = '\0';
    }

    /* assemble the component pieces*/
    if(url0 && strlen(url0) > 0)
        dapurl->url = strdup(url0);
    if(protocol && strlen(protocol) > 0) {
        dapurl->protocol = strdup(protocol);
        /* remove trailing ':' */
        dapurl->protocol[strlen(protocol)-1] = '\0';
    }
    if(user && strlen(user) > 0)
        dapurl->user = strdup(user);
    if(pwd && strlen(pwd) > 0)
        dapurl->password = strdup(pwd);
    if(host && strlen(host) > 0)
        dapurl->host = strdup(host);
    if(port && strlen(port) > 0)
        dapurl->port = strdup(port);
    if(file && strlen(file) > 0) {
	/* Add back the leading / */
        dapurl->file = malloc(strlen(file)+2);
	strcpy(dapurl->file,"/");
        strcat(dapurl->file,file);
    }
    if(constraint && strlen(constraint) > 0)
        dapurl->constraint = strdup(constraint);
    dapurlsetconstraints(dapurl,constraint);
    if(params != NULL && strlen(params) > 0) {
        dapurl->params = (char*)malloc(1+2+strlen(params));
        strcpy(dapurl->params,"[");
        strcat(dapurl->params,params);
        strcat(dapurl->params,"]");
    }

#ifdef DAPXDEBUG
	{
        fprintf(stderr,"dapurl:");
        fprintf(stderr," params=|%s|",FIX(dapurl->params));
        fprintf(stderr," protocol=|%s|",FIX(dapurl->protocol));
        fprintf(stderr," host=|%s|",FIX(dapurl->host));
        fprintf(stderr," port=|%s|",FIX(dapurl->port));
        fprintf(stderr," file=|%s|",FIX(dapurl->file));
        fprintf(stderr," constraint=|%s|",FIX(dapurl->constraint));
        fprintf(stderr,"\n");
    }
#endif
    free(url);
    if(dapurlp != NULL) *dapurlp = dapurl;
    return 1;

fail:
    if(url != NULL) free(url);
    return 0;
}

void
dapurlfree(DAPURL* dapurl)
{
    if(dapurl == NULL) return;
    if(dapurl->url != NULL) {free(dapurl->url);}
    if(dapurl->protocol != NULL) {free(dapurl->protocol);}
    if(dapurl->user != NULL) {free(dapurl->user);}
    if(dapurl->password != NULL) {free(dapurl->password);}
    if(dapurl->host != NULL) {free(dapurl->host);}
    if(dapurl->port != NULL) {free(dapurl->port);}
    if(dapurl->file != NULL) {free(dapurl->file);}
    if(dapurl->constraint != NULL) {free(dapurl->constraint);}
    if(dapurl->projection != NULL) {free(dapurl->projection);}
    if(dapurl->selection != NULL) {free(dapurl->selection);}
    if(dapurl->params != NULL) {free(dapurl->params);}
    if(dapurl->paramlist != NULL) dapparamfree(dapurl->paramlist);
    free(dapurl);
}

/* Replace the constraints */
void
dapurlsetconstraints(DAPURL* durl,const char* constraints)
{
    char* proj = NULL;
    char* select = NULL;
    const char* p;

    if(durl->constraint == NULL) free(durl->constraint);
    if(durl->projection != NULL) free(durl->projection);
    if(durl->selection != NULL) free(durl->selection);
    durl->constraint = NULL;	
    durl->projection = NULL;	
    durl->selection = NULL;

    if(constraints == NULL || strlen(constraints)==0) return;

    durl->constraint = strdup(constraints);
    if(*durl->constraint == '?')
	strcpy(durl->constraint,durl->constraint+1);

    p = durl->constraint;
    proj = (char*) p;
    select = strchr(proj,'&');
    if(select != NULL) {
        size_t plen = (select - proj);
	if(plen == 0) {
	    proj = NULL;
	} else {
	    proj = (char*)malloc(plen+1);
	    memcpy((void*)proj,p,plen);
	    proj[plen] = '\0';
	}
	select = nulldup(select);
    } else {
	proj = nulldup(proj);
	select = NULL;
    }
    durl->projection = proj;
    durl->selection = select;
}


/* Construct a complete DAP URL without the client params
   and optionally with the constraints;
   caller frees returned string
*/

char*
dapurlgeturl(DAPURL* durl, const char* prefix, const char* suffix, int pieces)
{
    size_t len = 0;
    char* newurl;
    int withparams = ((pieces&DAPURLPARAMS)
			&& durl->params != NULL);
    int withuserpwd = ((pieces&DAPURLUSERPWD)
	               && durl->user != NULL && durl->password != NULL);
    int withconstraints = ((pieces&DAPURLCONSTRAINTS)
	                   && durl->constraint != NULL);

    if(prefix != NULL) len += NILLEN(prefix);
    if(withparams) {
	len += NILLEN("[]");
	len += NILLEN(durl->params);
    }
    len += (NILLEN(durl->protocol)+NILLEN("://"));
    if(withuserpwd) {
	len += (NILLEN(durl->user)+NILLEN(durl->password)+NILLEN(":@"));
    }
    len += (NILLEN(durl->host));
    if(durl->port != NULL) {
	len += (NILLEN(":")+NILLEN(durl->port));
    }
    len += (NILLEN(durl->file));
    if(suffix != NULL) len += NILLEN(suffix);
    if(withconstraints) {
	len += (NILLEN("?")+NILLEN(durl->constraint));
    }
    len += 1; /* null terminator */
    
    newurl = (char*)malloc(len);
    if(!newurl) return NULL;

    newurl[0] = '\0';
    if(prefix != NULL) strcat(newurl,prefix);
    if(withparams) {
	strcat(newurl,"[");
	strcat(newurl,durl->params);
	strcat(newurl,"]");
    }
    strcat(newurl,durl->protocol);
    strcat(newurl,"://");
    if(withuserpwd) {
        strcat(newurl,durl->user);
        strcat(newurl,":");
        strcat(newurl,durl->password);	
        strcat(newurl,"@");
    }
    if(durl->host != NULL) { /* may be null if using file: protocol */
        strcat(newurl,durl->host);	
    }
    if(durl->port != NULL) {
        strcat(newurl,":");
        strcat(newurl,durl->port);
    }
    strcat(newurl,durl->file);
    if(suffix != NULL) strcat(newurl,suffix);
    if(withconstraints) {
	strcat(newurl,"?");
	strcat(newurl,durl->constraint);
    }
    return newurl;
}

int
dapurldecodeparams(DAPURL* dapurl)
{
    int ok = 0;
    if(dapurl->paramlist == NULL && dapurl->params != NULL) {
	char** list = dapparamdecode(dapurl->params);
	dapurl->paramlist = list;
	ok = 1;
    }
    return ok;
}

/*! NULL result => entry not found.
    Empty value should be represented as a zero length string */
const char*
dapurllookup(DAPURL* durl, const char* clientparam)
{
    /* make sure that durl->paramlist exists */
    if(durl->paramlist == NULL) dapurldecodeparams(durl);
    return dapparamlookup(durl->paramlist,clientparam);    
}

/**************************************************/
/* Parameter support */

/*
Client parameters are assumed to be
one or more instances of bracketed pairs:
e.g "[...][...]...".
The bracket content in turn is assumed to be a
comma separated list of <name>=<value> pairs.
e.g. x=y,z=,a=b.
If the same parameter is specifed more than once,
then the first occurrence is used; this is so that
is possible to forcibly override user specified
parameters by prefixing.
IMPORTANT: client parameter string is assumed to
have blanks compress out.
*/

char**
dapparamdecode(char* params0)
{
    char* cp;
    char* cq;
    int c;
    int i;
    int nparams;
    char** plist;
    char* params;
    char* params1;

    if(params0 == NULL) return NULL;

    /* Pass 1 to replace beginning '[' and ending ']' */
    if(params0[0] == '[') 
	params = strdup(params0+1);
    else
	params = strdup(params0);	

    if(params[strlen(params)-1] == ']')
	params[strlen(params)-1] = '\0';

    /* Pass 2 to replace "][" pairs with ','*/
    params1 = strdup(params);
    cp=params; cq = params1;
    while((c=*cp++)) {
	if(c == RBRACKET && *cp == LBRACKET) {cp++; c = ',';}
	*cq++ = c;
    }
    *cq = '\0';
    free(params);
    params = params1;

    /* Pass 3 to break string into pieces and count # of pairs */
    nparams=0;
    for(cp=params;(c=*cp);cp++) {
	if(c == ',') {*cp = '\0'; nparams++;}
    }
    nparams++; /* for last one */

    /* plist is an env style list */
    plist = (char**)calloc(1,sizeof(char*)*(2*nparams+1)); /* +1 for null termination */

    /* Pass 4 to break up each pass into a (name,value) pair*/
    /* and insert into the param list */
    /* parameters of the form name name= are converted to name=""*/
    cp = params;
    for(i=0;i<nparams;i++) {
	char* next = cp+strlen(cp)+1; /* save ptr to next pair*/
	char* vp;
	/*break up the ith param*/
	vp = strchr(cp,'=');
	if(vp != NULL) {*vp = '\0'; vp++;} else {vp = "";}
	plist[2*i] = strdup(cp);	
	plist[2*i+1] = strdup(vp);
	cp = next;
    }
    plist[nparams] = NULL;
    free(params);
    return plist;
}

/* Internal version of lookup; returns the paired index of the key */
static int
dapfind(char** params, const char* key)
{
    int i;
    char** p;
    for(i=0,p=params;*p;p+=2,i++) {
	if(strcmp(key,*p)==0) return i;
    }
    return -1;
}


const char*
dapparamlookup(char** params, const char* key)
{
    int i;
    if(params == NULL || key == NULL) return NULL;
    i = dapfind(params,key);
    if(i >= 0)
	return params[(2*i)+1];
    return NULL;
}

void
dapparamfree(char** params)
{
    char** p;
    if(params == NULL) return;
    for(p=params;*p;p+=2) {
	free(*p);
	if(p[1] != NULL) free(p[1]);
    }
    free(params);
}

/*
Delete the entry.
return value = 1 => found and deleted;
               0 => param not found
*/
int
dapparamdelete(char** params, const char* key)
{
    int i;
    char** p;
    char** q;
    if(params == NULL || key == NULL) return 0;
    i = dapfind(params,key);
    if(i < 0) return 0;
    p = params+(2*i);
    for(q=p+2;*q;) {	
	*p++ = *q++;
    }
    *p = NULL;
    return 1;
}

static int
daplength(char** params)
{
    int i = 0;
    if(params != NULL) {
	while(*params) {params+=2; i++;}
    }
    return i;
}

/*
Insert new client param (name,value);
return value = 1 => not already defined
               0 => param already defined (no change)
*/
char**
dapparaminsert(char** params, const char* key, const char* value)
{
    int i;
    char** newp;
    size_t len;
    if(params == NULL || key == NULL) return 0;
    i = dapfind(params,key);
    if(i >= 0) return 0;
    /* not found, append */
    i = daplength(params);
    len = sizeof(char*)*((2*i)+1);
    newp = realloc(params,len+2*sizeof(char*));
    memcpy(newp,params,len);
    newp[2*i] = strdup(key);
    newp[2*i+1] = (value==NULL?NULL:strdup(value));
    return newp;
}

/*
Replace new client param (name,value);
return value = 1 => replacement performed
               0 => key not found (no change)
*/
int
dapparamreplace(char** params, const char* key, const char* value)
{
    int i;
    if(params == NULL || key == NULL) return 0;
    i = dapfind(params,key);
    if(i < 0) return 0;
    if(params[2*i+1] != NULL) free(params[2*i+1]);
    params[2*i+1] = nulldup(value);
    return 1;
}
