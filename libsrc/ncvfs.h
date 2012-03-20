/*
 *	Copyright 2012, University Corporation for Atmospheric Research
 *	See netcdf/COPYRIGHT file for copying and redistribution conditions.
 */

#ifndef _NCVFS_H_
#define _NCVFS_H_

typedef struct ncvfs ncvfs;	/* forward reference */

/*
 * netcdf i/o abstraction
 */
struct ncvfs {
    int ioflags; /* make visible for fIsSet macro access*/
    /* Internal state of the stdio dispatcher */
    void* state;
    /* dispatch functions; never called directly by any higher-level code */
    struct ncvfs_ops {
        int (*read)(ncvfs*,void*,const off_t,const size_t,size_t*);
        int (*write)(ncvfs*,const void*,const off_t,const size_t,size_t*);
        int (*free)(ncvfs*);
        int (*close)(ncvfs*,int);
        int (*flush)(ncvfs*);
	int (*seek)(ncvfs*,off_t,int,off_t*);
	int (*sync)(ncvfs*);
	int (*uid)(ncvfs*,int*);
    } *ops;
};

extern int 
ncvfs_close(ncvfs* ncvfsp, int deletefile);

extern int
ncvfs_flush(ncvfs* ncvfsp);

extern int
ncvfs_seek(ncvfs* ncvfsp, off_t pos, int whence, off_t* oldpos);

extern int
ncvfs_sync(ncvfs* ncvfsp);

extern int
ncvfs_read(ncvfs* ncvfsp, void* memory, const off_t offset, const size_t size, size_t* actual);

extern int
ncvfs_write(ncvfs* ncvfsp, const void* memory, const off_t offset, const size_t size, size_t* actual);

/* Return some form of short term unique identifier for this file;
   canonical example is the unix file descriptor */
extern int
ncvfs_uid(ncvfs* ncvfsp,int*);

/**************************************************/
/* export all known ncvfs implementation create/open procedures */
extern int ncFile_create(const char *path, int ioflags, ncvfs** filepp);
extern int ncFile_open(const char *path, int ioflags, ncvfs** filepp);

#ifdef USE_DISKLESS
extern int ncMemory_create(const char *path, int ioflags, ncvfs** filepp);
extern int ncMemory_open(const char *path, int ioflags, ncvfs** filepp);
#endif

#endif /* _NCVFS_H_ */
