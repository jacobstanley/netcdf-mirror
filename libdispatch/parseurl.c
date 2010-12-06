/*********************************************************************
 *   Copyright 2010, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "ncdispatch.h"
#include "parseurl.h"

#define LBRACKET '['
#define RBRACKET ']'

static NClist* nc_urlparamdecode(char* params0);
static const char* nc_urlparamlookup(NClist* params, const char* clientparam);
static void nc_urlparamfree(NClist* params);


/* Do a simple url parse*/
int
nc_urlparse(const char* url0, NC_URL** ncurlp)
{
    char* url;
    char* p;
    char* p1;
    int c;
    NC_URL* ncurl;

    /* accumulate parse points*/
    char* protocol = NULL;
    char* params = NULL;
    char* baseurl = NULL;
    char* constraint = NULL;
    char* stop;

    /* copy url and remove all whitespace*/
    url = strdup(url0);

    p = url;
    p1 = url;
    while((c=*p1++)) {if(c != ' ' && c != '\t') *p++ = c;}

    p = url;
    stop = p + strlen(p);

    /* break up the url string into pieces*/
    if(*p == LBRACKET) {
	params = p+1;
	/* find end of the clientparams*/
        for(;*p;p++) {if(p[0] == RBRACKET && p[1] != LBRACKET) break;}
	if(*p == 0) goto fail; /* malformed client params*/
	*p = '\0'; /* leave off the trailing rbracket for now */
	p++; /* move past the params*/
    }

    /* Note that we dont care what the protocol is */
    protocol = p;

    baseurl = p;

    /* Look for '?' */
    constraint = strchr(p,'?');
    if(constraint) {
	*constraint++ = '\0';
    }

    /* assemble the component pieces*/
    ncurl = malloc(sizeof(NC_URL));
    if(ncurl == NULL) return NC_ENOMEM;
    memset((void*)ncurl,0,sizeof(NC_URL));

    ncurl->url = nulldup(url0);
    ncurl->base = nulldup(baseurl);
    ncurl->protocol = nulldup(protocol);
    /* remove trailing ':' */
    ncurl->protocol[strlen(protocol)-1] = '\0';
    ncurl->constraint = nulldup(constraint);
    nc_urlsetconstraints(ncurl,constraint);
    if(params != NULL) {
        ncurl->params = (char*)malloc(1+2+strlen(params));
	if(ncurl->params == NULL) return 0;
        strcpy(ncurl->params,"[");
        strcat(ncurl->params,params);
        strcat(ncurl->params,"]");
    }
    if(ncurlp) *ncurlp = ncurl;

#ifdef DEBUG
        fprintf(stderr,"urlparse: params=|%s| base=|%s| projection=|%s| selection=|%s|\n",
		ncurl->params, ncurl->base, ncurl->projection, ncurl->selection);
#endif

    free(url);
    return 1;

fail:
    if(url != NULL) free(url);
    return 0;
}

/* Call must free the actual url instance.*/
void
nc_urlfree(NC_URL* ncurl)
{
    if(ncurl == NULL) return;
    if(ncurl->url != NULL) {free(ncurl->url);}
    if(ncurl->base != NULL) {free(ncurl->base);}
    if(ncurl->protocol != NULL) {free(ncurl->protocol);}
    if(ncurl->constraint != NULL) {free(ncurl->constraint);}
    if(ncurl->projection != NULL) {free(ncurl->projection);}
    if(ncurl->selection != NULL) {free(ncurl->selection);}
    if(ncurl->params != NULL) {free(ncurl->params);}
    if(ncurl->paramlist != NULL) nc_urlparamfree(ncurl->paramlist);
    free(ncurl);
}

/* Replace the constraints */
void
nc_urlsetconstraints(NC_URL* durl,const char* constraints)
{
    char* proj = NULL;
    char* select = NULL;
    const char* p;

    if(durl->projection != NULL) free(durl->projection);
    if(durl->selection != NULL) free(durl->selection);
    durl->projection = NULL;	
    durl->selection = NULL;

    if(constraints == NULL || strlen(constraints)==0) return;

    p = constraints;
    if(p[0] == '?') p++;
    proj = (char*) p;
    select = strchr(proj,'&');
    if(select != NULL) {
        size_t plen = (select - proj);
	if(plen == 0) {
	    proj = NULL;
	} else {
	    proj = (char*)malloc(plen+1);
	    if(proj == NULL) return;
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

int
nc_urldecodeparams(NC_URL* ncurl)
{
    int ok = 0;
    if(ncurl->paramlist == NULL && ncurl->params != NULL) {
	NClist* list = nc_urlparamdecode(ncurl->params);
	ncurl->paramlist = list;
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
    return nc_urlparamlookup(durl->paramlist,clientparam);    
}

/**************************************************/

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

static NClist*
nc_urlparamdecode(char* params0)
{
    char* cp;
    char* cq;
    int c;
    int i;
    int nparams;
    NClist* plist = nclistnew();
    char* params;
    char* params1;

    if(params0 == NULL) return plist;

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
	if(!nclistcontains(plist,(ncelem)cp)) {
	    nclistpush(plist,(ncelem)strdup(cp));
	    nclistpush(plist,(ncelem)strdup(vp));
	}
	cp = next;
    }
    free(params);
    return plist;
}

static const char*
nc_urlparamlookup(NClist* params, const char* clientparam)
{
    int i;
    if(params == NULL || clientparam == NULL) return NULL;
    for(i=0;i<nclistlength(params);i+=2) {
	char* name = (char*)nclistget(params,i);
	if(strcmp(clientparam,name)==0)
	    return (char*)nclistget(params,i+1);
    }
    return NULL;
}

static void
nc_urlparamfree(NClist* params)
{
    int i;
    if(params == NULL) return;
    for(i=0;i<nclistlength(params);i++) {
	char* s = (char*)nclistget(params,i);
	if(s != NULL) free((void*)s);
    }
    nclistfree(params);
}

#ifdef IGNORE
/*
Delete the entry.
return value = 1 => found and deleted;
               0 => param not found
*/
static int
nc_urlparamdelete(NClist* params, const char* clientparam)
{
    int i,found = 0;
    if(params == NULL || clientparam == NULL) return 0;
    for(i=0;i<nclistlength(params);i+=2) {
	char* name = (char*)nclistget(params,i);
	if(strcmp(clientparam,name)==0) {found=1; break;}
    }
    if(found) {
	nclistremove(params,i+1); /* remove value */
	nclistremove(params,i); /* remove name */
    }
    return found;
}

/*
Replace new client param (name,value);
return value = 1 => replacement performed
               0 => insertion performed
*/
static int
nc_urlparamreplace(NClist* params, const char* clientparam, const char* value)
{
    int i;
    if(params == NULL || clientparam == NULL) return 0;
    for(i=0;i<nclistlength(params);i+=2) {
	char* name = (char*)nclistget(params,i);
	if(strcmp(clientparam,name)==0) {
	    nclistinsert(params,i+1,(ncelem)nulldup(value));
	    return 1;
	}
    }
    nc_urlparaminsert(params,clientparam,value);
    return 0;
}

/*
Insert new client param (name,value);
return value = 1 => not already defined
               0 => param already defined (no change)
*/
static int
nc_urlparaminsert(NClist* params, const char* clientparam, const char* value)
{
    int i;
    if(params == NULL || clientparam == NULL) return 0;
    for(i=0;i<nclistlength(params);i+=2) {
	char* name = (char*)nclistget(params,i);
	if(strcmp(clientparam,name)==0) return 0;
    }
    /* not found, append */
    nclistpush(params,(ncelem)strdup(clientparam));
    nclistpush(params,(ncelem)nulldup(value));
    return 1;
}

#endif
