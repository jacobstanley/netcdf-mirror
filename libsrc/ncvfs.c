/*
 *	Copyright 2012, University Corporation for Atmospheric Research
 *	See netcdf/COPYRIGHT file for copying and redistribution conditions.
 */

#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include "netcdf.h"
#include "ncvfs.h"

/* Wrappers for ncvfs dispatch methods */

int
ncvfs_uid(ncvfs* iop, int* idp)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->uid(iop,idp);
}

int
ncvfs_sync(ncvfs* iop)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->sync(iop);
}

int
ncvfs_flush(ncvfs* iop)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->flush(iop);
}

int
ncvfs_free(ncvfs* iop)
{
    if(iop == NULL) return NC_NOERR;
    return iop->ops->free(iop);
}

int
ncvfs_close(ncvfs* iop, int delfile)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->close(iop,delfile);
}

int
ncvfs_seek(ncvfs* iop, off_t pos, int whence, off_t* oldpos)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->seek(iop,pos,whence,oldpos);
}

int
ncvfs_read(ncvfs* iop, void* memory, const off_t offset, const size_t size, size_t* actual)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->read(iop,memory,offset,size,actual);
}

int
ncvfs_write(ncvfs* iop, const void* memory, const off_t offset, const size_t size, size_t* actual)
{
    if(iop == NULL) return NC_EINVAL;
    return iop->ops->write(iop,memory,offset,size,actual);
}
