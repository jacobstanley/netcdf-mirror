/* Copyright 2009, UCAR/Unidata and OPeNDAP, Inc.
   See the COPYRIGHT file for more information. */

#ifndef PARSEURL_H
#define PARSEURL_H

/* Forward */
struct NClist;

/*! This is an open structure meaning
	it is ok to directly access its fields*/
typedef struct NC_URL {
    char* url;        /* as passed by the caller */
    char* base;	      /*!< without constraints*/
    char* protocol;
    char* constraint;
    char* projection; /*!< without leading '?'*/
    char* selection;  /*!< with leading '&'*/
    char* params;
    struct NClist* paramlist;
} NC_URL;

extern int nc_urlparse(const char* s, NC_URL* nc_url);
extern void nc_urlfree(NC_URL* nc_url);

/* Replace the constraints */
extern void nc_urlsetconstraints(NC_URL*,const char* constraints);

/* Construct a complete URL; caller frees returned string */
extern char* nc_urlgeturl(NC_URL*,const char* prefix, const char* suffix, int withconstraints);

extern int nc_urldecodeparams(NC_URL* nc_url);

/*! NULL result => entry not found.
    Empty value should be represented as a zero length string */
extern const char* nc_urllookup(NC_URL*, const char* clientparam);

#endif /*PARSEURL_H*/
