/*
 *	Copyright 2012, University Corporation for Atmospheric Research
 *	See netcdf/COPYRIGHT file for copying and redistribution conditions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "ncstdio.h"

int
ncstdio_filesize(ncstdio* iop, off_t* filesizep)
{
    return iop->ops.filesize(iop,filesizep);
}

int
ncstdio_pad_length(ncstdio* iop, off_t length)
{
    return iop->ops.pad(iop,length);
}

int
ncstdio_flush(ncstdio* iop)
{
    return iop->ops.flush(iop);
}

int
ncstdio_seek(ncstdio* iop, off_t pos)
{
    return iop->ops.seek(iop,pos);
}

int
ncstdio_read(ncstdio* iop, void* memory, const size_t size, size_t* actual)
{
    return iop->ops.read(iop,memory,size,actual);
}

int
ncstdio_write(ncstdio* iop, const void* memory, const size_t size, size_t* actual)
{
    return iop->ops.write(iop,memory,size,actual);
}
