/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Header: /upc/share/CVS/netcdf-3/libncdap3/common34.c,v 1.29 2010/05/25 13:53:02 ed Exp $
 *********************************************************************/

#include <stdlib.h>
#include <string.h>

/* Define a local version of strindex */
int
crstrindex(char* s, char* match)
{
    size_t mlen = strlen(match);
    size_t slen = strlen(s);
    int i,j;
    if(slen < mlen) return -1;
    slen -= mlen;
    for(i=0;i<slen;i++) {
	int found = 1;
        for(j=0;j<mlen;j++) {
	    if(s[i+j] != match[j]) {found=0; break;}
	}
	if(found)
	    return i;
    }
    return -1;
}

int
nccr_createtempfile(char* tmppath, char** tmpnamep)
{
    int fd;
    char* tmpname = NULL;
#ifdef HAVE_MKSTEMP
    {
	char* p;
	char c;
	tmpname = (char*)malloc(strlen(tmppath)+strlen("dataddsXXXXXX")+1);
	if(tmpname == NULL) return -1;
	strcpy(tmpname,tmppath);
	strcat(tmpname,"dataddsXXXXXX");
	p = tmpname + strlen("datadds");
	/* \', and '/' to '_' and '.' to '-'*/
	for(;(c=*p);p++) {
	    if(c == '\\' || c == '/') {*p = '_';}
	    else if(c == '.') {*p = '-';}
	}
        /* Note Potential problem: old versions of this function
           leave the file in mode 0666 instead of 0600 */
        fd = mkstemp(tmpname);
    }
# else
    /* Ignore tmppath */
    tmpname = tempnam(); /* Not a good idea */
    if(tmpname == NULL) return -1;
    fd=open(tmpname,O_RDWR|O_BINARY|O_CREAT|O_EXCL|_O_SHORT_LIVED, _S_IREAD|_S_IWRITE);
#endif
    if(tmpnamep) *tmpnamep = tmpname;
    return fd;
}

void
nccr_unlinktempfile(int fd, char* tmpname)
{
    if(fd >= 0) /* free the original fd */
        close(fd);
    /* unlink the temp file so it will automatically be reclaimed */
    if(tmpname != NULL)
        unlink(tmpname);
}
