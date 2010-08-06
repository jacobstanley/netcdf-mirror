/*
  This file is part of netcdf-4, a netCDF-like interface for HDF5, or
  a HDF5 backend for netCDF, depending on your point of view.

  This file handles the nc4 file functions.

  Copyright 2003, University Corporation for Atmospheric Research. See
  COPYRIGHT file for copying and redistribution conditions.
*/

#include "nc.h"

extern NC_Dispatch* NC3_dispatch_table;

#ifdef USE_DAP
NC_Dispatch NC3DAP_dispatch_table = NULL;
#endif

#ifdef USE_NETCDF4

NC_Dispatch NC4_dispatch_table = NULL;

#ifdef USE_DAP
NC_Dispatch NC4DAP_dispatch_table = NULL
#endif
#endif

NC_Dispatch*
NC_getdefaultdispatch(void)
{
    return NC3_dispatch_table;
}
