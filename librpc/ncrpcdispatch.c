/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Header: /upc/share/CVS/netcdf-3/libncdap4/ncd4dispatch.c,v 1.8 2010/05/27 21:34:10 dmh Exp $
 *********************************************************************/

#include "config.h"
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "nclog.h"

#include "netcdf.h"
#include "nc.h"
#include "ncdispatch.h"
#include "nc4internal.h"

#include "ncrpc.h"
#include "ncrpcdispatch.h"

int
NCRPC_create(const char *path, int cmode,
           size_t initialsz, int basepe, size_t *chunksizehintp,
	   int useparallel, void* parameters,
	   NC_Dispatch*, NC**)
{
}

int
NCRPC_open(const char *path, int mode,
         int basepe, size_t *chunksizehintp, 
	 int use_parallel, void* parameters,
	 NC_Dispatch*, NC**)
{
}

int
NCRPC_new_nc(NC**)
{
}

int
NCRPC_free_nc(NC*)
{
}



int
NCRPC_redef(int ncid)
{
}

int
NCRPC__enddef(int ncid, size_t h_minfree, size_t v_align,
	size_t v_minfree, size_t r_align)
{
}

int
NCRPC_sync(int ncid)
{
}

int
NCRPC_abort(int ncid)
{
}

int
NCRPC_close(int ncid)
{
}

int
NCRPC_set_fill(int ncid, int fillmode, int *old_modep)
{
}

int
NCRPC_set_base_pe(int ncid, int pe)
{
}

int
NCRPC_inq_base_pe(int ncid, int *pe)
{
}

int
NCRPC_inq_format(int ncid, int *formatp)
{
}

int
NCRPC_inq(int ncid, int *ndimsp, int *nvarsp, int *nattsp, int *unlimdimidp)
{
}

int
NCRPC_inq_type(int, nc_type, char *, size_t *)
{
}

/* Begin _dim */

int
NCRPC_def_dim(int ncid, const char *name, size_t len, int *idp)
{
}

int
NCRPC_inq_dimid(int ncid, const char *name, int *idp)
{
}

int
NCRPC_inq_dim(int ncid, int dimid, char *name, size_t *lenp)
{
}

int
NCRPC_inq_unlimdim(int ncid, int *unlimdimidp)
{
}

int
NCRPC_rename_dim(int ncid, int dimid, const char *name)
{
}

/* End _dim */
/* Begin _att */

int
NCRPC_inq_att(int ncid, int varid, const char *name,
	    nc_type *xtypep, size_t *lenp)
{
}

int 
NCRPC_inq_attid(int ncid, int varid, const char *name, int *idp)
{
}

int
NCRPC_inq_attname(int ncid, int varid, int attnum, char *name)
{
}

int
NCRPC_rename_att(int ncid, int varid, const char *name, const char *newname)
{
}

int
NCRPC_del_att(int ncid, int varid, const char*)
{
}

/* End _att */
/* Begin {put,get}_att */

int
NCRPC_get_att(int ncid, int varid, const char *name, void *value, nc_type)
{
}

int
NCRPC_put_att(int ncid, int varid, const char *name, nc_type datatype,
	   size_t len, const void *value, nc_type)
{
}

/* End {put,get}_att */
/* Begin _var */

int
NCRPC_def_var(int ncid, const char *name,
	 nc_type xtype, int ndims, const int *dimidsp, int *varidp)
{
}

int
NCRPC_inq_var_all(int ncid, int varid, char *name, nc_type *xtypep, 
               int *ndimsp, int *dimidsp, int *nattsp, 
               int *shufflep, int *deflatep, int *deflate_levelp,
               int *fletcher32p, int *contiguousp, size_t *chunksizesp, 
               int *no_fill, void *fill_valuep, int *endiannessp, 
	       int *options_maskp, int *pixels_per_blockp)
{
}

int
NCRPC_inq_varid(int ncid, const char *name, int *varidp)
{
}

int
NCRPC_rename_var(int ncid, int varid, const char *name)
{
}

int
NCRPC_put_vara(int ncid, int varid,
   	     const size_t *start, const size_t *count,
             const void *value, nc_type)
{
}

int
NCRPC_get_vara(int ncid, int varid,
	     const size_t *start, const size_t *count,
             void *value, nc_type)
{
}

/* End _var */

/* netCDF4 API only */
int
NCRPC_var_par_access(int, int, int)
{
}

int
NCRPC_inq_ncid(int, const char *, int *)
{
}

int
NCRPC_inq_grps(int, int *, int *)
{
}

int
NCRPC_inq_grpname(int, char *)
{
}

int
NCRPC_inq_grpname_full(int, size_t *, char *)
{
}

int
NCRPC_inq_grp_parent(int, int *)
{
}

int
NCRPC_inq_grp_full_ncid(int, const char *, int *)
{
}

int
NCRPC_inq_varids(int, int * nvars, int *)
{
}

int
NCRPC_inq_dimids(int, int * ndims, int *, int)
{
}

int
NCRPC_inq_typeids(int, int * ntypes, int *)
{
}
   
int
NCRPC_inq_type_equal(int, nc_type, int, nc_type, int *)
{
}

int
NCRPC_def_grp(int, const char *, int *)
{
}

int
NCRPC_inq_user_type(int, nc_type, char *, size_t *, nc_type *, 
		  size_t *, int *)
{
}

int
NCRPC_def_compound(int, size_t, const char *, nc_type *)
{
}

int
NCRPC_insert_compound(int, nc_type, const char *, size_t, nc_type)
{
}

int
NCRPC_insert_array_compound(int, nc_type, const char *, size_t, 
			  nc_type, int, const int *)
{
}

int
NCRPC_inq_typeid(int, const char *, nc_type *)
{
}

int
NCRPC_inq_compound_field(int, nc_type, int, char *, size_t *, 
		       nc_type *, int *, int *)
{
}

int
NCRPC_inq_compound_fieldindex(int, nc_type, const char *, int *)
{
}

int
NCRPC_def_vlen(int, const char *, nc_type base_typeid, nc_type *)
{
}

int
NCRPC_put_vlen_element(int, int, void *, size_t, const void *)
{
}

int
NCRPC_get_vlen_element(int, int, const void *, size_t *, void *)
{
}

int
NCRPC_def_enum(int, nc_type, const char *, nc_type *)
{
}

int
NCRPC_insert_enum(int, nc_type, const char *, const void *)
{
}

int
NCRPC_inq_enum_member(int, nc_type, int, char *, void *)
{
}

int
NCRPC_inq_enum_ident(int, nc_type, long long, char *)
{
}

int
NCRPC_def_opaque(int, size_t, const char *, nc_type *)
{
}

int
NCRPC_def_var_deflate(int, int, int, int, int)
{
}

int
NCRPC_def_var_fletcher32(int, int, int)
{
}

int
NCRPC_def_var_chunking(int, int, int, const size_t *)
{
}

int
NCRPC_def_var_fill(int, int, int, const void *)
{
}

int
NCRPC_def_var_endian(int, int, int)
{
}

int
NCRPC_set_var_chunk_cache(int, int, size_t, size_t, float)
{
}

int
NCRPC_get_var_chunk_cache(int, int, size_t *, size_t *, float *)
{
}

int
NCRPC_inq_unlimdims(int, int *, int *)
{
}

int
NCRPC_show_metadata(int)
{
}

int 
NCRPC_initialize(void)
{
}
