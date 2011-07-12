/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

/* $Id$ */
/* $Header$ */

#include "config.h"
#include <string.h>
#include "netcdf.h"


size_t NC_coord_zero[NC_MAX_VAR_DIMS];

/* initialized int put/get_var1 below */
size_t NC_coord_one[NC_MAX_VAR_DIMS];

int
NC_initialize(void)
{
    int i;
    for(i=0;i<NC_MAX_VAR_DIMS;i++) {
	coord_one[i] = 1;
	coord_zero[i] = 0;
    }
    return NC_NOERR;
}
