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

#include "nc_url.h"

#define NC_URLDEBUG

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

/* Do a simple url parse*/
int
nc_urlparse(const char* url0, NC_URL** nc_urlp)
{
    NC_URL* nc_url = NULL;
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

    nc_url = (NC_URL*)calloc(1,sizeof(NC_URL));
    if(nc_url == NULL) return 0;    

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
        nc_url->url = strdup(url0);
    if(protocol && strlen(protocol) > 0) {
        nc_url->protocol = strdup(protocol);
        /* remove trailing ':' */
        nc_url->protocol[strlen(protocol)-1] = '\0';
    }
    if(user && strlen(user) > 0)
        nc_url->user = strdup(user);
    if(pwd && strlen(pwd) > 0)
        nc_url->password = strdup(pwd);
    if(host && strlen(host) > 0)
        nc_url->host = strdup(host);
    if(port && strlen(port) > 0)
        nc_url->port = strdup(port);
    if(file && strlen(file) > 0) {
	/* Add back the leading / */
        nc_url->file = malloc(strlen(file)+2);
	strcpy(nc_url->file,"/");
        strcat(nc_url->file,file);
    }
    if(constraint && strlen(constraint) > 0)
        nc_url->constraint = strdup(constraint);
    nc_urlsetconstraints(nc_url,constraint);
    if(params != NULL && strlen(params) > 0) {
        nc_url->params = (char*)malloc(1+2+strlen(params));
        strcpy(nc_url->params,"[");
        strcat(nc_url->params,params);
        strcat(nc_url->params,"]");
    }

#ifdef NC_XDEBUG
	{
        fprintf(stderr,"nc_url:");
        fprintf(stderr," params=|%s|",FIX(nc_url->params));
        fprintf(stderr," protocol=|%s|",FIX(nc_url->protocol));
        fprintf(stderr," host=|%s|",FIX(nc_url->host));
        fprintf(stderr," port=|%s|",FIX(nc_url->port));
        fprintf(stderr," file=|%s|",FIX(nc_url->file));
        fprintf(stderr," constraint=|%s|",FIX(nc_url->constraint));
        fprintf(stderr,"\n");
    }
#endif
    free(url);
    if(nc_urlp != NULL) *nc_urlp = nc_url;
    return 1;

fail:
    if(url != NULL) free(url);
    return 0;
}

void
nc_urlfree(NC_URL* nc_url)
{
    if(nc_url == NULL) return;
    if(nc_url->url != NULL) {free(nc_url->url);}
    if(nc_url->protocol != NULL) {free(nc_url->protocol);}
    if(nc_url->user != NULL) {free(nc_url->user);}
    if(nc_url->password != NULL) {free(nc_url->password);}
    if(nc_url->host != NULL) {free(nc_url->host);}
    if(nc_url->port != NULL) {free(nc_url->port);}
    if(nc_url->file != NULL) {free(nc_url->file);}
    if(nc_url->constraint != NULL) {free(nc_url->constraint);}
    if(nc_url->projection != NULL) {free(nc_url->projection);}
    if(nc_url->selection != NULL) {free(nc_url->selection);}
    if(nc_url->params != NULL) {free(nc_url->params);}
    if(nc_url->paramlist != NULL) nc_paramfree(nc_url->paramlist);
    free(nc_url);
}

/* Replace the constraints */
void
nc_urlsetconstraints(NC_URL* durl,const char* constraints)
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


/* Construct a complete NC_ URL without the client params
   and optionally with the constraints;
   caller frees returned string
*/

char*
nc_urlgeturl(NC_URL* durl, const char* prefix, const char* suffix, int pieces)
{
    size_t len = 0;
    char* newurl;
    int withparams = ((pieces&NC_URLPARAMS)
			&& durl->params != NULL);
    int withuserpwd = ((pieces&NC_URLUSERPWD)
	               && durl->user != NULL && durl->password != NULL);
    int withconstraints = ((pieces&NC_URLCONSTRAINTS)
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
nc_urldecodeparams(NC_URL* nc_url)
{
    int ok = 0;
    if(nc_url->paramlist == NULL && nc_url->params != NULL) {
	char** list = nc_paramdecode(nc_url->params);
	nc_url->paramlist = list;
	ok = 1;
    }
    return ok;
}

/*! NULL result => entry not found.
    Empty value should be represented as a zero length string */
const char*
nc_urllookup(NC_URL* durl, const char* clientparam)
{
    /* make sure that durl->paramlist exists */
    if(durl->paramlist == NULL) nc_urldecodeparams(durl);
    return nc_paramlookup(durl->paramlist,clientparam);    
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
nc_paramdecode(char* params0)
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
nc_find(char** params, const char* key)
{
    int i;
    char** p;
    for(i=0,p=params;*p;p+=2,i++) {
	if(strcmp(key,*p)==0) return i;
    }
    return -1;
}


const char*
nc_paramlookup(char** params, const char* key)
{
    int i;
    if(params == NULL || key == NULL) return NULL;
    i = nc_find(params,key);
    if(i >= 0)
	return params[(2*i)+1];
    return NULL;
}

void
nc_paramfree(char** params)
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
nc_paramdelete(char** params, const char* key)
{
    int i;
    char** p;
    char** q;
    if(params == NULL || key == NULL) return 0;
    i = nc_find(params,key);
    if(i < 0) return 0;
    p = params+(2*i);
    for(q=p+2;*q;) {	
	*p++ = *q++;
    }
    *p = NULL;
    return 1;
}

static int
nc_length(char** params)
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
nc_paraminsert(char** params, const char* key, const char* value)
{
    int i;
    char** newp;
    size_t len;
    if(params == NULL || key == NULL) return 0;
    i = nc_find(params,key);
    if(i >= 0) return 0;
    /* not found, append */
    i = nc_length(params);
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
nc_paramreplace(char** params, const char* key, const char* value)
{
    int i;
    if(params == NULL || key == NULL) return 0;
    i = nc_find(params,key);
    if(i < 0) return 0;
    if(params[2*i+1] != NULL) free(params[2*i+1]);
    params[2*i+1] = nulldup(value);
    return 1;
}
