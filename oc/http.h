/* Copyright 2009, UCAR/Unidata and OPeNDAP, Inc.
   See the COPYRIGHT file for more information. */

#ifndef HTTP_H
#define HTTP_H 1

#ifdef IGNORE
extern int curlopen(CURL** curlp);
extern void curlclose(CURL*);
#endif

extern CURLcode ocfetchurl(CURL*, char*, OCbytes*, long*);
extern CURLcode ocfetchurl_file(CURL*, char*, FILE*, unsigned long*, long*);

extern long ocfetchhttpcode(CURL* curl);

extern CURLcode ocfetchlastmodified(CURL* curl, char* url, long* filetime);

extern CURLcode occurlopen(CURL** curlp);
extern void occurlclose(CURL* curlp);

#endif /*HTTP_H*/
