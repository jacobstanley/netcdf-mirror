/* Copyright 2009, UCAR/Unidata and OPeNDAP, Inc.
   See the COPYRIGHT file for more information. */

#ifndef DAPURL_H
#define DAPURL_H

/*! This is an open structure meaning
	it is ok to directly access its fields*/
typedef struct DAPURL {
    char* url;        /* as passed by the caller */
    char* protocol;
    char* user; /* from user:password@ */
    char* password; /* from user:password@ */
    char* host;	      /*!< host*/
    char* port;	      /*!< host */
    char* file;	      /*!< file */
    char* constraint; /*!< projection+selection */
    char* projection; /*!< without leading '?'*/
    char* selection;  /*!< with leading '&'*/
    char* params;     /* all params */
    char** paramlist;    /*!<null terminated list */
} DAPURL;

extern int dapurlparse(const char* s, DAPURL** dapurl);
extern void dapurlfree(DAPURL* dapurl);

/* Replace the constraints */
extern void dapurlsetconstraints(DAPURL*,const char* constraints);

/* Construct a complete DAP URL; caller frees returned string */

/* Define flags to control what is included */
#define DAPURLCONSTRAINTS 1
#define DAPURLUSERPWD	  2
#define DAPURLPARAMS	  4

extern char* dapurlgeturl(DAPURL*,const char* prefix, const char* suffix, int flags);

extern int dapurldecodeparams(DAPURL* dapurl);

/*! NULL result => entry not found.
    Empty value should be represented as a zero length string */
extern const char* dapurllookup(DAPURL*, const char* param);


extern char** dapparamdecode(char* params0);
extern const char* dapparamlookup(char** params, const char* key);
extern void dapparamfree(char** params);
extern int dapparamdelete(char** params, const char* key);
extern char** dapparaminsert(char** params, const char* key, const char* value);
extern int dapparamreplace(char** params, const char* key, const char* value);


#endif /*DAPURL_H*/
