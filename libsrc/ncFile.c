/*
 *	Copyright 2012, University Corporation for Atmospheric Research
 *	See netcdf/COPYRIGHT file for copying and redistribution conditions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/*
Implement the ncstdio.h interface using unix stdio.h
*/

/* Forward */
static int NCFile_read(ncstdio*,void*,const size_t,size_t*);
static int NCFile_write(ncstdio*,const void*,const size_t,size_t*);
static int NCFile_free(ncstdio*);
static int NCFile_close(ncstdio*,int);
static int NCFile_flush(ncstdio*)
static int NCFile_filesize(ncstdio*,off_t*);
static int NCFile_pad(ncstdio*,off_t);
static int NCFile_seek(ncstdio*,off_t);

/* Define the stdio.h base operators */


struct NCFile_ops NCFile_ops = {
NCFile_read,
NCFile_write,
NCFile_free,
NCFile_close,
NCFile_flush,
NCFile_filesize,
NCFile_pad,
NCFile_seek,
};

struct NCFile_state {
    File* file;
    char* path;
};

int
ncFile_create(const char *path, int ioflags, ncstdio** filepp)
{
    ncstdio* filep;
    File* f;
    NCFile_State* state;

    f = fopen(path,"w+");
    if(f == NULL)
	return errno;
    state = (NCFile_state*)calloc(sizeof(NCFile_state),1);
    if(state == NULL) {fclose(f); return NC_ENOMEM;}
    filep = (ncstdio*)calloc(sizeof(ncstdio),1);
    if(filep == NULL) {fclose(f); free(state); return NC_ENOMEM;}

    filep->ops = &NCFILE_ops;
    filep->ioflags = ioflags;
    filep->state = (void*)state;
	state->file = f;
	state->path = strdup(path);
    if(filepp) *filepp = filep;
    return NC_NOERR;
}

int
ncFile_open(const char *path, int ioflags, ncstdio** filepp)
{
    ncstdio* filep;
    File* f;
    NCFile_State* state;

    if(fIsSet(ioflags,NC_NOCLOBBER))
        f = fopen(path,"r");
    else
        f = fopen(path,"w+");
    if(f == NULL)
	return errno;

    state = (NCFile_state*)calloc(sizeof(NCFile_state),1);
    if(state == NULL) {fclose(f); return NC_ENOMEM;}
    filep = (ncstdio*)calloc(sizeof(ncstdio),1);
    if(filep == NULL) {fclose(f); free(state); return NC_ENOMEM;}

    filep->ops = &NCFILE_ops;
    filep->ioflags = ioflags;
    filep->state = (void*)state;
	state->file = f;
	state->path = strdup(path);
    if(filepp) *filepp = filep;
    return NC_NOERR;
}

static int 
NCFile_close(ncstdio* filep, int unlink)
{
    NCFile_state* state;
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
    fclose(state->file);
    if(unlink) unlink(state->path);
    return NC_NOERR;          
}

static int
NCFile_filesize(ncstdio* filep, off_t* filesizep)
{
    NCFile_state* state;
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
}

static int
NCFile_pad_length(ncstdio* filep, off_t length);
{
    NCFile_state* state;
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
    return NC_NOERR;
}

static int
NCFile_flush(ncstdio* filep);
{
    NCFile_state* state;
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
    return NC_NOERR;
}

static int
NCFile_seek(ncstdio* filep, off_t pos);
{
    NCFile_state* state;
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
    return NC_NOERR;
}

static int
NCFile_read(ncstdio* filep, void* memory, const size_t size, size_t* actualp);
{
    NCFile_state* state;
    size_t actual;    
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
    actual = fread(memory,size,state->file);
    if(actualp) *actualp = actual;    
    return NC_NOERR;
}

static int
NCFile_write(ncstdio* filep, const void* memory, const size_t size, size_t* actual);
{
    NCFile_state* state;
    size_t actual;    
    if(filep == NULL) return NC_EINVAL;
    state = (NCFile_state*)filep->state;
    actual = fwrite(memory,size,state->file);
    if(actualp) *actualp = actual;    
    return NC_NOERR;
}

#endif /* _NCFILE_H_* /
