/* This is part of the netCDF package.
   Copyright 2005 University Corporation for Atmospheric Research/Unidata
   See COPYRIGHT file for conditions of use.

   Test HDF5 file code. These are not intended to be exhaustive tests,
   but they use HDF5 the same way that netCDF-4 does, so if these
   tests don't work, than netCDF-4 won't work either.

   $Id$
*/
#include <config.h>
#include <nc_tests.h>
#include "netcdf.h"
#include <nc4internal.h>
#include <H5DSpublic.h>

/*#define FILE_NAME "tst_h_files4.h5"*/
/* Heavy duty test file...*/
#define FILE_NAME "/machine/downloads/SVI-NPP.h5"

struct nc_hdf5_link_info 
{
   char name[NC_MAX_NAME + 1];
   H5I_type_t obj_type;   
};   

/* This is a callback function for H5Literate().  */
herr_t
op_func (hid_t g_id, const char *name, const H5L_info_t *info, 
	 void *op_data)  
{
   hid_t id;

   strncpy(((struct nc_hdf5_link_info *)op_data)->name, name, 
	   NC_MAX_NAME);
   if ((id = H5Oopen_by_addr(g_id, info->u.address)) < 0) ERR;
   if ((((struct nc_hdf5_link_info *)op_data)->obj_type = H5Iget_type(id)) < 0) ERR;
   if (H5Oclose(id) < 0) ERR;

   /*Turn this on to learn what type of object you've opened.*/
   switch (((struct nc_hdf5_link_info *)op_data)->obj_type)
   {
      case H5I_GROUP:
	 printf("group %s\n", name);
	 break;
      case H5I_DATATYPE:
	 printf("type %s\n", name);
	 break;
      case H5I_DATASET:
	 printf("data %s\n", name);
	 break;
      case H5I_DATASPACE:
	 printf("data space %s\n", name);
	 break;
      case H5I_BADID:
	 printf("bad idea %s\n", name);
	 break;
      default:
	 printf("unknown class\n");
   }
   return 1;
}

int
rec_read(hid_t grpid) 
{
   hsize_t idx = 0;
   hsize_t num_obj;
   hid_t new_grpid;
   int natts, a, att_ndims, att_npoints;
   char att_name[NC_MAX_HDF5_NAME + 1];
   hid_t attid, datasetid, spaceid;
   int i;
   struct nc_hdf5_link_info link_info;

   if ((natts = H5Aget_num_attrs(grpid)) < 0) ERR;
   printf("\tfound %d atts\n", natts);
   for (a = 0; a < natts; a++)
   {
      if ((attid = H5Aopen_idx(grpid, (unsigned int)a)) < 0) ERR;
      if (H5Aget_name(attid, NC_MAX_HDF5_NAME, att_name) < 0) ERR;
      if ((spaceid = H5Aget_space(attid)) < 0) ERR;
      if ((att_ndims = H5Sget_simple_extent_ndims(spaceid)) < 0) ERR;
      printf("att %s has %d dimensions\n", att_name, att_ndims);
   }
   
   if (H5Gget_num_objs(grpid, &num_obj) < 0) ERR;
   for (i = 0; i < num_obj; i++)
   {
      if (H5Literate(grpid, H5_INDEX_NAME, H5_ITER_INC, &idx, op_func, 
		     (void *)&link_info) != 1) ERR;
      if (((struct nc_hdf5_link_info)link_info).obj_type == H5I_GROUP)
      {
	 if ((new_grpid = H5Gopen2(grpid, ((struct nc_hdf5_link_info)link_info).name,
				   H5P_DEFAULT)) < 0) ERR;
	 if (rec_read(new_grpid)) ERR;
      } 
      if (((struct nc_hdf5_link_info)link_info).obj_type == H5I_DATASET)      
      {
	 if ((datasetid = H5Dopen2(grpid, ((struct nc_hdf5_link_info)link_info).name, 
				   H5P_DEFAULT)) < 0) ERR;
	 if ((natts = H5Aget_num_attrs(datasetid)) < 0) ERR;
	 if (natts) 
	    printf("\tfound %d atts\n", natts);
	 for (a = 0; a < natts; a++)
	 {
	    if ((attid = H5Aopen_idx(datasetid, (unsigned int)a)) < 0) ERR;
	    if (H5Aget_name(attid, NC_MAX_HDF5_NAME, att_name) < 0) ERR;
	    if ((spaceid = H5Aget_space(attid)) < 0) ERR;
	    if ((att_ndims = H5Sget_simple_extent_ndims(spaceid)) < 0) ERR;
	    if ((att_npoints = H5Sget_simple_extent_npoints(spaceid)) < 0) ERR;
	    printf("att %s has %d dimensions %d points\n", att_name, att_ndims, att_npoints);
	 }
      }
   }
   return 0;
}

int
main()
{
   printf("\n*** Checking HDF5 file functions.\n");
   printf("*** Opening a HDF5 file with H5Literate ...");
   {
      hid_t fileid, grpid;

      if ((fileid = H5Fopen(FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT)) < 0) ERR;
      if ((grpid = H5Gopen2(fileid, "/", H5P_DEFAULT)) < 0) ERR;

      if (rec_read(grpid)) ERR;


      if (H5Gclose(grpid) < 0) ERR;
      if (H5Fclose(fileid) < 0) ERR;
   }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}
