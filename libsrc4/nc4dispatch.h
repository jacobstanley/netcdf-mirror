/*
 * Copyright 1993-1996 University Corporation for Atmospheric Research/Unidata
 * 
 * Portions of this software were developed by the Unidata Program at the 
 * University Corporation for Atmospheric Research.
 * 
 * Access and use of this software shall impose the following obligations
 * and understandings on the user. The user is granted the right, without
 * any fee or cost, to use, copy, modify, alter, enhance and distribute
 * this software, and any derivative works thereof, and its supporting
 * documentation for any purpose whatsoever, provided that this entire
 * notice appears in all copies of the software, derivative works and
 * supporting documentation.  Further, UCAR requests that the user credit
 * UCAR/Unidata in any publications that result from the use of this
 * software or in any product that includes this software. The names UCAR
 * and/or Unidata, however, may not be used in any advertising or publicity
 * to endorse or promote any products or commercial entity unless specific
 * written permission is obtained from UCAR/Unidata. The user also
 * understands that UCAR/Unidata is not obligated to provide the user with
 * any support, consulting, training or assistance of any kind with regard
 * to the use, operation and performance of this software nor to provide
 * the user with any updates, revisions, new versions or "bug fixes."
 * 
 * THIS SOFTWARE IS PROVIDED BY UCAR/UNIDATA "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL UCAR/UNIDATA BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE ACCESS, USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/* "$Id: nc4dispatch.h,v 1.3 2010/05/25 03:48:31 dmh Exp $" */

#ifndef _NC4DISPATCH_H
#define _NC4DISPATCH_H

#include <stddef.h> /* size_t, ptrdiff_t */
#include <errno.h>  /* netcdf functions sometimes return system errors */

#if defined(__cplusplus)
extern "C" {
#endif
/*
 * The Interface
 */

/* Declaration modifiers for DLL support (MSC et al) */

#if defined(DLL_NETCDF) /* define when library is a DLL */
#  if defined(DLL_EXPORT) /* define when building the library */
#   define MSC_EXTRA __declspec(dllexport)
#  else
#   define MSC_EXTRA __declspec(dllimport)
#  endif
#else
#define MSC_EXTRA
#endif	/* defined(DLL_NETCDF) */

# define EXTERNL extern MSC_EXTRA

EXTERNL int
NC4_create(const char *path, int cmode,
           size_t initialsz, int basepe, size_t *chunksizehintp,
	   int useparallel, void* parameters,
	   NC_Dispatch*, NC**);

EXTERNL int
NC4_open(const char *path, int mode,
         int basepe, size_t *chunksizehintp, 
	 int use_parallel, void* parameters,
	 NC_Dispatch*, NC**);

EXTERNL int
NC4_redef(int ncid);

EXTERNL int
NC4__enddef(int ncid, size_t h_minfree, size_t v_align,
	size_t v_minfree, size_t r_align);

EXTERNL int
NC4_sync(int ncid);

EXTERNL int
NC4_abort(int ncid);

EXTERNL int
NC4_close(int ncid);

EXTERNL int
NC4_set_fill(int ncid, int fillmode, int *old_modep);

EXTERNL int
NC4_set_base_pe(int ncid, int pe);

EXTERNL int
NC4_inq_base_pe(int ncid, int *pe);

EXTERNL int
NC4_inq_format(int ncid, int *formatp);

EXTERNL int
NC4_inq(int ncid, int *ndimsp, int *nvarsp, int *nattsp, int *unlimdimidp);

EXTERNL int
NC4_inq_type(int,nc_type,char*,size_t*);

/* Begin _dim */

EXTERNL int
NC4_def_dim(int ncid, const char *name, size_t len, int *idp);

EXTERNL int
NC4_inq_dimid(int ncid, const char *name, int *idp);

EXTERNL int
NC4_inq_dim(int ncid, int dimid, char *name, size_t *lenp);

EXTERNL int
NC4_inq_unlimdim(int ncid, int *unlimdimidp);

EXTERNL int
NC4_rename_dim(int ncid, int dimid, const char *name);

/* End _dim */
/* Begin _att */

EXTERNL int
NC4_inq_att(int ncid, int varid, const char *name,
	 nc_type *xtypep, size_t *lenp);

EXTERNL int 
NC4_inq_attid(int ncid, int varid, const char *name, int *idp);

EXTERNL int
NC4_inq_attname(int ncid, int varid, int attnum, char *name);

EXTERNL int
NC4_rename_att(int ncid, int varid, const char *name, const char *newname);

EXTERNL int
NC4_del_att(int ncid, int varid, const char*);

/* End _att */
/* Begin {put,get}_att */

EXTERNL int
NC4_get_att(int ncid, int varid, const char *name, void *value, nc_type);

EXTERNL int
NC4_put_att(int ncid, int varid, const char *name, nc_type datatype,
	   size_t len, const void *value, nc_type);

/* End {put,get}_att */
/* Begin _var */

EXTERNL int
NC4_def_var(int ncid, const char *name,
	 nc_type xtype, int ndims, const int *dimidsp, int *varidp);

EXTERNL int
NC4_inq_var_all(int ncid, int varid, char *name, nc_type *xtypep, 
               int *ndimsp, int *dimidsp, int *nattsp, 
               int *shufflep, int *deflatep, int *deflate_levelp,
               int *fletcher32p, int *contiguousp, size_t *chunksizesp, 
               int *no_fill, void *fill_valuep, int *endiannessp, 
	       int *options_maskp, int *pixels_per_blockp);

EXTERNL int
NC4_inq_varid(int ncid, const char *name, int *varidp);

EXTERNL int
NC4_rename_var(int ncid, int varid, const char *name);

EXTERNL int
NC4_put_vara(int ncid, int varid,
   	     const size_t *start, const size_t *count,
             const void *value, nc_type);

EXTERNL int
NC4_get_vara(int ncid, int varid,
	     const size_t *start, const size_t *count,
             void *value, nc_type);

/* End _var */

/* netCDF4 API only */
EXTERNL int
NC4_var_par_access(int,int,int);

EXTERNL int
NC4_inq_ncid(int,const char*,int*);

EXTERNL int
NC4_inq_grps(int,int*,int*);

EXTERNL int
NC4_inq_grpname(int,char*);

EXTERNL int
NC4_inq_grpname_full(int,size_t*,char*);

EXTERNL int
NC4_inq_grp_parent(int,int*);

EXTERNL int
NC4_inq_grp_full_ncid(int,const char*,int*);

EXTERNL int
NC4_inq_varids(int,int* nvars,int*);

EXTERNL int
NC4_inq_dimids(int,int* ndims,int*,int);

EXTERNL int
NC4_inq_typeids(int,int* ntypes,int*);

EXTERNL int
NC4_inq_type_equal(int,nc_type,int,nc_type,int*);

EXTERNL int
NC4_def_grp(int,const char*,int*);

EXTERNL int
NC4_inq_user_type(int,nc_type,char*,size_t*,nc_type*,size_t*,int*);


EXTERNL int
NC4_def_compound(int,size_t,const char*,nc_type*);

EXTERNL int
NC4_insert_compound(int,nc_type,const char*,size_t,nc_type);

EXTERNL int
NC4_insert_array_compound(int,nc_type,const char*,size_t,nc_type,int,const int*);

EXTERNL int
NC4_inq_typeid(int,const char*,nc_type*);

EXTERNL int
NC4_inq_compound_field(int,nc_type,int,char*,size_t*,nc_type*,int*,int*);

EXTERNL int
NC4_inq_compound_fieldindex(int,nc_type,const char*,int*);

EXTERNL int
NC4_def_vlen(int,const char*,nc_type base_typeid,nc_type*);

EXTERNL int
NC4_put_vlen_element(int,int,void*,size_t,const void*);

EXTERNL int
NC4_get_vlen_element(int,int,const void*,size_t*,void*);

EXTERNL int
NC4_def_enum(int,nc_type,const char*,nc_type*);

EXTERNL int
NC4_insert_enum(int,nc_type,const char*,const void*);

EXTERNL int
NC4_inq_enum_member(int,nc_type,int,char*,void*);

EXTERNL int
NC4_inq_enum_ident(int,nc_type,long long,char*);

EXTERNL int
NC4_def_opaque(int,size_t,const char*,nc_type*);

EXTERNL int
NC4_def_var_deflate(int,int,int,int,int);

EXTERNL int
NC4_def_var_fletcher32(int,int,int);

EXTERNL int
NC4_def_var_chunking(int,int,int,const size_t*);

EXTERNL int
NC4_def_var_fill(int,int,int,const void*);

EXTERNL int
NC4_def_var_endian(int,int,int);

EXTERNL int
NC4_set_var_chunk_cache(int,int,size_t,size_t,float);

EXTERNL int
NC4_get_var_chunk_cache(int,int,size_t*,size_t*,float*);

EXTERNL int
NC4_inq_unlimdims(int,int*,int*);

EXTERNL int
NC4_show_metadata(int);

extern int NC4_initialize(void);

#if defined(__cplusplus)
}
#endif

#endif /*_NC4DISPATCH_H*/
