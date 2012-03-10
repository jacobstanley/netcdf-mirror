/*
 *	Copyright 2012, University Corporation for Atmospheric Research
 *	See netcdf/COPYRIGHT file for copying and redistribution conditions.
 */

#ifndef _NCSTDIO_H_
#define _NCSTDIO_H_

typedef struct ncstdio ncstdio;	/* forward reference */
/*
 * netcdf i/o abstraction
 */
struct ncstdio {
    int ioflags; /* make visible */
    /* Internal state of the stdio dispatcher */
    void* state;
    /* dispatch functions; never called directly by any higher-level code */
    struct ncstdio_ops {
        int (*read)(ncstdio*,void*,const size_t,size_t*);
        int (*write)(ncstdio*,const void*,const size_t,size_t*);
        int (*free)(ncstdio*);
        int (*close)(ncstdio*,int);
        int (*flush)(ncstdio*)
        int (*filesize)(ncstdio*,off_t*);
        int (*pad)(ncstdio*,off_t);
	int (*seek)(ncstdio*,off_t);
    } ops;
};

extern int 
ncstdio_close(ncstdio* ncstdiop, int unlink);

extern int
ncstdio_filesize(ncstdio* ncstdiop, off_t* filesizep);

extern int
ncstdio_pad_length(ncstdio* ncstdiop, off_t length);

extern int
ncstdio_flush(ncstdio* ncstdiop);

extern int
ncstdio_seek(ncstdio* ncstdiop, off_t pos);

extern int
ncstdio_read(ncstdio* ncstdiop, void* memory, const size_t size, size_t* actual);

extern int
ncstdio_write(ncstdio* ncstdiop, const void* memory, const size_t size, size_t* actual);

#define ncio_flagset(iop, flags) (iop->ioflags & flags)

/* export all known ncstdio implementation create/open procedures */
extern int ncFile_create(const char *path, int ioflags, ncstdio** filepp);
extern int ncFile_open(const char *path, int ioflags, ncstdio** filepp);

#ifdef USE_DISKLESS
extern int ncMemory_create(const char *path, int ioflags, ncstdio** filepp);
extern int ncMemory_open(const char *path, int ioflags, ncstdio** filepp);
#endif

#endif /* _NCSTDIO_H_* /
