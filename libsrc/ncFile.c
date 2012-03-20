/*
 *	Copyright 2012, University Corporation for Atmospheric Research
 *	See netcdf/COPYRIGHT file for copying and redistribution conditions.
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "netcdf.h"
#include "nc.h"
#include "ncvfs.h"

/*
Implement the ncvfs.h interface using unix stdio.h
*/

/* Forward */
static int ncFile_read(ncvfs*,void*,const off_t, const size_t,size_t*);
static int ncFile_write(ncvfs*,const void*,const off_t, const size_t,size_t*);
static int ncFile_free(ncvfs*);
static int ncFile_close(ncvfs*,int);
static int ncFile_flush(ncvfs*);
static int ncFile_seek(ncvfs*,off_t,int,off_t*);
static int ncFile_sync(ncvfs*);
static int ncFile_uid(ncvfs*,int*);

/* Define the stdio.h base operators */


struct ncvfs_ops ncFile_ops = {
ncFile_read,
ncFile_write,
ncFile_free,
ncFile_close,
ncFile_flush,
ncFile_seek,
ncFile_sync,
ncFile_uid
};

/* In order to implement the close with delete, we
   need the file path.
*/
struct ncFileState {
    char* path;
    FILE* file;
};

static struct ncFileState*
getstate(ncvfs* iop)
{
    if(iop != NULL) {
	if(iop->state != NULL) {
	    return (struct ncFileState*)iop->state;
	}	
    }
    return NULL;
}

int
ncFile_create(const char *path, int ioflags, ncvfs** filepp)
{
    ncvfs* filep;
    FILE* f;
    struct ncFileState* state;

    if(path == NULL || strlen(path) == 0)
	return NC_EINVAL;
    f = fopen(path,"w+");
    if(f == NULL)
	return errno;
    filep = (ncvfs*)calloc(sizeof(ncvfs),1);
    if(filep == NULL) {fclose(f); return NC_ENOMEM;}
    state = (struct ncFileState*)calloc(sizeof(struct ncFileState),1);
    if(state == NULL) {fclose(f); free(filep); return NC_ENOMEM;}
    filep->ops = &ncFile_ops;
    filep->ioflags = (ioflags|NC_WRITE);
    filep->state = (void*)state;
	state->path = strdup(path);
	state->file = f;
    if(filepp) *filepp = filep;
    return NC_NOERR;
}

int
ncFile_open(const char *path, int ioflags, ncvfs** filepp)
{
    ncvfs* filep;
    FILE* f;
    struct ncFileState* state;

    if(fIsSet(ioflags,NC_WRITE))
        f = fopen(path,"w+");
    else
        f = fopen(path,"r");
    if(f == NULL)
	return errno;

    filep = (ncvfs*)calloc(sizeof(ncvfs),1);
    if(filep == NULL) {fclose(f); return NC_ENOMEM;}
    state = (struct ncFileState*)calloc(sizeof(struct ncFileState),1);
    if(state == NULL) {fclose(f); free(filep); return NC_ENOMEM;}
    filep->ops = &ncFile_ops;
    filep->ioflags = ioflags;
    filep->state = (void*)state;
	state->path = strdup(path);
	state->file = f;
    if(filepp) *filepp = filep;
    return NC_NOERR;
}

static int 
ncFile_close(ncvfs* filep, int delfile)
{
    struct ncFileState* state;
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL || state->file == NULL) return NC_NOERR;
    fclose(state->file);
    state->file = NULL;
    if(delfile)
	unlink(state->path);
    return NC_NOERR;          
}

static int 
ncFile_free(ncvfs* filep)
{
    struct ncFileState* state;
    if(filep == NULL) return NC_NOERR;
    state = getstate(filep);
    if(state != NULL) {
	if(state->file != NULL) return NC_EINVAL;
	if(state->path != NULL)
	    free(state->path);
	free(state);
    }
    free(filep);
    return NC_NOERR;          
}

static int
ncFile_flush(ncvfs* filep)
{
    struct ncFileState* state;
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL) return NC_EINVAL;
    if(state->file == NULL) return NC_EINVAL;
    fflush(state->file);	
    return NC_NOERR;
}

static int
ncFile_sync(ncvfs* filep)
{
    struct ncFileState* state;
#ifdef USE_FSYNC
    int fd;
#endif
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL) return NC_EINVAL;
    if(state->file == NULL) return NC_EINVAL;
#ifdef HAVE_FSYNC
#ifdef USE_FSYNC
    fd = fileno(state->file);
#ifndef WIN32
    fsync(fd);
#else
    _commit(fd);
#endif	/* WIN32 */
#endif
#endif
    return NC_NOERR;
}

static int
ncFile_seek(ncvfs* filep, off_t pos, int whence, off_t* oldpos)
{
    struct ncFileState* state;
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL) return NC_EINVAL;
    if(state->file == NULL) return NC_EINVAL;
#ifdef HAVE_FTELLO
    if(oldpos) *oldpos = (off_t)ftello(state->file);
#else
    if(oldpos) *oldpos = (off_t)ftell(state->file);
#endif
    if(!fseek(state->file,pos,whence))
	return errno;
    return NC_NOERR;
}

static int
ncFile_read(ncvfs* filep, void* memory, const off_t offset, const size_t size, size_t* actualp)
{
    struct ncFileState* state;
    size_t actual;    
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL || state->file == NULL) return NC_EINVAL;
    if(fseek(state->file,offset,SEEK_SET) < 0)
	return errno;
    actual = fread(memory,1,size,state->file);
    if(actualp) *actualp = actual;    
    return (actual < size ? NC_EIO : NC_NOERR);
}

static int
ncFile_write(ncvfs* filep, const void* memory, const off_t offset, const size_t size, size_t* actualp)
{
    struct ncFileState* state;
    size_t actual;    
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL || state->file == NULL) return NC_EINVAL;
    if(fseek(state->file,offset,SEEK_SET) < 0)
	return errno;
    actual = fwrite(memory,1,size,state->file);
    if(actualp) *actualp = actual;    
    return (actual < size ? NC_EIO : NC_NOERR);
}

static int 
ncFile_uid(ncvfs* filep, int* idp)
{
    struct ncFileState* state;
    if(filep == NULL) return NC_EINVAL;
    state = getstate(filep);
    if(state == NULL || state->file == NULL) return NC_EINVAL;
    if(idp) *idp = fileno(state->file);
    return NC_NOERR;
}

