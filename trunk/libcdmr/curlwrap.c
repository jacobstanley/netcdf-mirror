/*
 * Copyright 1993-1996 University Corporation for Atmospheric Research/Unidata
 * 
 * Portions of this software were developed by the Unidata Program at the 
 * University Corporation for Atmospheric Research.
 * 
 * Access and use of this software shall impose the following obligations
 * and understandings on the user. The user is granted the right, without
 * any fee or cost, to use, copy, modify, alter, enhance and distribute
 * this software, and any derivative works thereof, and its supporting
 * documentation for any purpose whatsoever, provided that this entire
 * notice appears in all copies of the software, derivative works and
 * supporting documentation.  Further, UCAR requests that the user credit
 * UCAR/Unidata in any publications that result from the use of this
 * software or in any product that includes this software. The names UCAR
 * and/or Unidata, however, may not be used in any advertising or publicity
 * to endorse or promote any products or commercial entity unless specific
 * written permission is obtained from UCAR/Unidata. The user also
 * understands that UCAR/Unidata is not obligated to provide the user with
 * any support, consulting, training or assistance of any kind with regard
 * to the use, operation and performance of this software nor to provide
 * the user with any updates, revisions, new versions or "bug fixes."
 * 
 * THIS SOFTWARE IS PROVIDED BY UCAR/UNIDATA "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL UCAR/UNIDATA BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE ACCESS, USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/* "$Id$" */

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "nccr.h"
#include "curlwrap.h"

static size_t WriteFileCallback(void*, size_t, size_t, void*);
static size_t WriteMemoryCallback(void*, size_t, size_t, void*);

static char* combinecredentials(const char* user, const char* pwd);

struct Fetchdata {
    FILE* stream;
    size_t size;
};

/* Condition on libcurl version */
#ifndef HAVE_CURLOPT_KEYPASSWD
/* Set up an alias */
#define CURLOPT_KEYPASSWD CURLOPT_SSLKEYPASSWD
#endif

/**************************************************/

long
nc_fetchhttpcode(CURL* curl)
{
    long httpcode;
    CURLcode cstat = CURLE_OK;
    /* Extract the http code */
    cstat = curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&httpcode);
    if(cstat != CURLE_OK) httpcode = 0;
    return httpcode;
}

int
nc_fetchurl_file(CURL* curl, char* url, FILE* stream,
        unsigned long* sizep, long* filetime)
{
    int stat = NC_NOERR;
    CURLcode cstat = CURLE_OK;
    struct Fetchdata fetchdata;

    /* Set the URL */
    cstat = curl_easy_setopt(curl, CURLOPT_URL, (void*)url);
    if (cstat != CURLE_OK) goto fail;

    /* send all data to this function  */
    cstat = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
    if (cstat != CURLE_OK) goto fail;

    /* we pass our file to the callback function */
    cstat = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&fetchdata);
    if (cstat != CURLE_OK) goto fail;

    /* One last thing; always try to get the last modified time */
    cstat = curl_easy_setopt(curl, CURLOPT_FILETIME, (long)1);

    fetchdata.stream = stream;
    fetchdata.size = 0;
    cstat = curl_easy_perform(curl);
    if (cstat != CURLE_OK) goto fail;

    if (stat == NC_NOERR) {
        /* return the file size*/
        if (sizep != NULL)
            *sizep = fetchdata.size;
        /* Get the last modified time */
        if(filetime != NULL)
	    cstat = curl_easy_getinfo(curl,CURLINFO_FILETIME,filetime);
        if(cstat != CURLE_OK) goto fail;
    }
    return THROW(stat);

fail:
    LOG((LOGERR, "curl error: %s", curl_easy_strerror(cstat)));
    return THROW(NC_ECURL);
}

int
nc_fetchurl(CURL* curl, char* url, NCbytes* buf, long* filetime)
{
    int stat = NC_NOERR;
    CURLcode cstat = CURLE_OK;

    /* Set the URL */
    cstat = curl_easy_setopt(curl, CURLOPT_URL, (void*)url);
    if (cstat != CURLE_OK) goto fail;

    /* send all data to this function  */
    cstat = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    if (cstat != CURLE_OK) goto fail;

    /* we pass our file to the callback function */
    cstat = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buf);
    if (cstat != CURLE_OK) goto fail;

    /* One last thing; always try to get the last modified time */
    cstat = curl_easy_setopt(curl, CURLOPT_FILETIME, (long)1);

    cstat = curl_easy_perform(curl);
    if(cstat == CURLE_PARTIAL_FILE) {
        /* Log it but otherwise ignore */
        LOG((LOGWARN, "curl error: %s; ignored",
           curl_easy_strerror(cstat)));
        cstat = CURLE_OK;
    }
    if(cstat != CURLE_OK) goto fail;

    /* Get the last modified time */
    if(filetime != NULL)
        cstat = curl_easy_getinfo(curl,CURLINFO_FILETIME,filetime);
    if(cstat != CURLE_OK) goto fail;

    /* Null terminate the buffer*/
    ncbytesnull(buf);

    return THROW(stat);

fail:
    LOG((LOGERR, "curl error: %s", curl_easy_strerror(cstat)));
    return THROW(NC_ECURL);
}

static size_t
WriteFileCallback(void* ptr, size_t size, size_t nmemb,    void* data)
{
    size_t count;
    struct Fetchdata* fetchdata;
    fetchdata = (struct Fetchdata*) data;
    count = fwrite(ptr, size, nmemb, fetchdata->stream);
    if (count > 0) {
        fetchdata->size += (count * size);
    }
#ifdef DEBUG
    LOG((LOGNOTE,"callback: %lu bytes",(unsigned long)(size*nmemb))));
#endif
    return count;
}

static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    NCbytes* buf = (NCbytes*) data;
    if(realsize == 0)
        LOG((LOGWARN,"WriteMemoryCallback: zero sized chunk"));
    /* Optimize for reading potentially large dods datasets */
    if(!ncbytesavail(buf,realsize)) {
        /* double the size of the packet */
        ncbytessetalloc(buf,2*ncbytesalloc(buf));
    }
    ncbytesappendn(buf, ptr, realsize);
    return realsize;
}

int
nc_curlopen(CURL** curlp)
{
    int stat = NC_NOERR;
    CURLcode cstat;
    CURL* curl;
    /* initialize curl*/
    curl = curl_easy_init();
    if (curl == NULL) stat = NC_ECURL;
    else {
        cstat = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
        if (cstat != CURLE_OK) stat = NC_ECURL;
        /* some servers don't like requests that are made without a user-agent */
        cstat = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        if (cstat != CURLE_OK) stat = NC_ECURL;
    }
    if (curlp) *curlp = curl;
    return THROW(stat);
}

void
nc_curlclose(CURL* curl)
{
    if (curl != NULL)
        curl_easy_cleanup(curl);
}

int
nc_fetchlastmodified(CURL* curl, char* url, long* filetime)
{
    int stat = NC_NOERR;
    CURLcode cstat = CURLE_OK;

    /* Set the URL */
    cstat = curl_easy_setopt(curl, CURLOPT_URL, (void*)url);
    if (cstat != CURLE_OK) goto fail;

    /* Ask for head */
    cstat = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30); /* 30sec timeout*/
    cstat = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2);
    cstat = curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    cstat = curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    cstat = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
    cstat = curl_easy_setopt(curl, CURLOPT_FILETIME, (long)1);

    cstat = curl_easy_perform(curl);
    if(cstat != CURLE_OK) goto fail;
    if(filetime != NULL)
        cstat = curl_easy_getinfo(curl,CURLINFO_FILETIME,filetime);
    if(cstat != CURLE_OK) goto fail;

    return THROW(stat);

fail:
    LOG((LOGERR, "curl error: %s", curl_easy_strerror(cstat)));
    return THROW(NC_ECURL);
}

/**************************************************/

/* Set various general curl flags */
int
nc_set_curl_flags(CURL* curl,  NCCDMR* nccr)
{
    CURLcode cstat = CURLE_OK;
    NCCURLSTATE* state = &nccr->curl;

#ifdef CURLOPT_ENCODING
    if (state->compress) {
        cstat = curl_easy_setopt(curl, CURLOPT_ENCODING, 'deflate, gzip');
        if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOP_ENCODING=deflat, gzip"));
#endif
    }
#endif

    if (state->cookiejar || state->cookiefile) {
        cstat = curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        if (cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOP_COOKIESESSION=1"));
#endif
    }
    if (state->cookiejar) {
        cstat = curl_easy_setopt(curl, CURLOPT_COOKIEJAR, state->cookiejar);
        if (cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOP_COOKIEJAR=%s",state->cookiejar);
#endif
    }
    if (state->cookiefile) {
        cstat = curl_easy_setopt(curl, CURLOPT_COOKIEFILE, state->cookiefile);
        if (cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_COOKIEFILE=%s",state->cookiefile);
#endif
    }
    if (state->verbose) {
        cstat = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        if (cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_VERBOSE=%ld",1L);
#endif
    }

    /* Following are always set */
    cstat = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_FOLLOWLOCATION=%ld",1L);
#endif
    return NC_NOERR;

fail:
    return NC_ECURL;
}

int
nc_set_proxy(CURL* curl, NCCDMR* nccr)
{
    CURLcode cstat;
    struct NCCURLSTATE* state = &nccr->curl;

    cstat = curl_easy_setopt(curl, CURLOPT_PROXY, state->host);
    if (cstat != CURLE_OK) return NC_ECURL;
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_PROXY=%s",state->host);
#endif

    cstat = curl_easy_setopt(curl, CURLOPT_PROXYPORT, state->port);
    if (cstat != CURLE_OK) return NC_ECURL;
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_PROXYPORT=%d",state->port);
#endif

    if (state->username) {
        char *combined = combinecredentials(state->username,state->password);
        if (!combined) return NC_ENOMEM;
        cstat = curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, combined);
        free(combined);
        if (cstat != CURLE_OK) return NC_ECURL;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_PROXYUSERPWD=%s",combined);
#endif
#ifdef CURLOPT_PROXYAUTH
        cstat = curl_easy_setopt(curl, CURLOPT_PROXYAUTH, (long)CURLAUTH_ANY);
        if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
       LOG((LOGNOTE,"CURLOPT_PROXYAUTH=%ld",(long)CURLAUTH_ANY);
#endif
#endif
    }
    return NC_NOERR;
}

int
nc_set_ssl(CURL* curl, NCCDMR* nccr)
{
    CURLcode cstat = CURLE_OK;
    struct NCCURLSTATE* state = &nccr->curl;
    long verify = (state->validate?1L:0L);
    cstat=curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, verify);
    if (cstat != CURLE_OK) goto fail;
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_SSL_VERIFYPEER=%ld",verify);
#endif
    cstat=curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, (verify?2L:0L));
    if (cstat != CURLE_OK) goto fail;
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_SSL_VERIFYHOST=%ld",(verify?2L:0L));
#endif
    {
        if(state->certificate) {
            cstat = curl_easy_setopt(curl, CURLOPT_SSLCERT, state->certificate);
            if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_SSLCERT=%s",state->certificate);
#endif
        }
        if(state->key) {
            cstat = curl_easy_setopt(curl, CURLOPT_SSLKEY, state->key);
            if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_SSLKEY=%s",state->key);
#endif
        }
        if(state->keypasswd) {
            cstat = curl_easy_setopt(curl, CURLOPT_KEYPASSWD, state->keypasswd);
            if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_SSLKEY=%s",state->key);
#endif
        }
        if(state->cainfo) {
            cstat = curl_easy_setopt(curl, CURLOPT_CAINFO, state->cainfo);
            if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_CAINFO=%s",state->cainfo);
#endif
        }
        if(state->capath) {
            cstat = curl_easy_setopt(curl, CURLOPT_CAPATH, state->capath);
            if(cstat != CURLE_OK) goto fail;
#ifdef DEBUG
        LOG((LOGNOTE,"CURLOPT_CAPATH=%s",state->capath);
#endif
        }
    }    
    return NC_NOERR;

fail:
    return NC_ECURL;
}

/* This is called with arguments while the other functions in this file are
 * used with global values read from the.dodsrc file. The reason is that
 * we may have multiple password sources.
 */
int
nc_set_user_password(CURL* curl, const char *userC, const char *passwordC)
{
    CURLcode cstat;
    char* combined = NULL;

    if(userC == NULL && passwordC == NULL) return NC_NOERR;
    if(userC == NULL) userC = "";
    if(passwordC == NULL) passwordC = "";

    combined = combinecredentials(userC,passwordC);
    if (!combined) return NC_ENOMEM;
    cstat = curl_easy_setopt(curl, CURLOPT_USERPWD, combined);
    if (cstat != CURLE_OK) goto done;
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_USERPWD=%s",combined);
#endif
    cstat = curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long) CURLAUTH_ANY);
    if (cstat != CURLE_OK) goto done;
#ifdef DEBUG
    LOG((LOGNOTE,"CURLOPT_HTTPAUTH=%ld",(long)CURLAUTH_ANY);
#endif

done:
    if(combined != NULL) free(combined);
    return (cstat == CURLE_OK?NC_NOERR:NC_ECURL);
}


static char*
combinecredentials(const char* user, const char* pwd)
{
    int userPassSize = strlen(user) + strlen(pwd) + 2;
    char *userPassword = malloc(sizeof(char) * userPassSize);
    if (!userPassword) {
        LOG((LOGERR,"Out of Memory\n"));
        return NULL;
    }
    strcpy(userPassword, user);
    strcat(userPassword, ":");
    strcat(userPassword, pwd);
    return userPassword;
}
