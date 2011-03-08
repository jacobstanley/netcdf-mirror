/*
 * Copyright 1993-2011 University Corporation for Atmospheric Research/Unidata
 * 
 * This header contains prototypes for functions only called by fortran 77.
 */
#ifndef _NETCDF_F_
#define _NETCDF_F_

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
nc_inq_var_chunking_ints(int ncid, int varid, int *contiguousp, int *chunksizesp);

EXTERNL int
nc_def_var_chunking_ints(int ncid, int varid, int contiguous, int *chunksizesp);

EXTERNL int
nc_open_par_fortran(const char *path, int mode, int comm, 
		    int info, int *ncidp);

EXTERNL int
nc_create_par_fortran(const char *path, int cmode, int comm, 
		      int info, int *ncidp);

EXTERNL int
nc_set_chunk_cache_ints(int size, int nelems, int preemption);

EXTERNL int
nc_get_chunk_cache_ints(int *sizep, int *nelemsp, int *preemptionp);

EXTERNL int
nc_set_var_chunk_cache_ints(int ncid, int varid, int size, int nelems, 
			    int preemption);
EXTERNL int
nc_get_var_chunk_cache_ints(int ncid, int varid, int *sizep, 
			    int *nelemsp, int *preemptionp);

#endif
