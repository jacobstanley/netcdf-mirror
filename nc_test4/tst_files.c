/* This is part of the netCDF package.
   Copyright 2010 University Corporation for Atmospheric Research/Unidata
   See COPYRIGHT file for conditions of use.

   Test netcdf files a bit. 
*/

#include <nc_tests.h>
#include "netcdf.h"

#define FILE_NAME "tst_files.nc"
#define URL "http://test.opendap.org:8080/dods/dts/test.01"

int
main(int argc, char **argv)
{
   printf("\n*** Testing netcdf file functions.\n");
   printf("*** Checking the new inq_path function...");
   {
      int ncid;
      size_t path_len;
      char path_in[NC_MAX_NAME + 1] = "";

      /* Test with classic file create. */
      if (nc_create(FILE_NAME, 0, &ncid)) ERR;
      if (nc_inq_path(ncid, &path_len, path_in)) ERR;
      if (path_len != strlen(FILE_NAME) || strcmp(path_in, FILE_NAME)) ERR;
      if (nc_close(ncid)) ERR;
      strcpy(path_in, "");
      path_len = 0;

      /* Test with classic file open. */
      if (nc_open(FILE_NAME, 0, &ncid)) ERR;
      if (nc_inq_path(ncid, &path_len, path_in)) ERR;
      if (path_len != strlen(FILE_NAME) || strcmp(path_in, FILE_NAME)) ERR;
      if (nc_close(ncid)) ERR;
      strcpy(path_in, "");

      /* Test with netCDF-4 create. */
      if (nc_create(FILE_NAME, NC_NETCDF4, &ncid)) ERR;
      if (nc_inq_path(ncid, &path_len, path_in)) ERR;
      if (path_len != strlen(FILE_NAME) || strcmp(path_in, FILE_NAME)) ERR;
      if (nc_close(ncid)) ERR;
      strcpy(path_in, "");
      path_len = 0;

      /* Test with classic file open. */
      if (nc_open(FILE_NAME, 0, &ncid)) ERR;
      if (nc_inq_path(ncid, &path_len, path_in)) ERR;
      if (path_len != strlen(FILE_NAME) || strcmp(path_in, FILE_NAME)) ERR;
      if (nc_close(ncid)) ERR;
      strcpy(path_in, "");
      path_len = 0;

/* #ifdef USE_DAP */
/*       /\* Test with URL. *\/ */
/*       if (nc_open(URL, 0, &ncid)) ERR; */
/*       if (nc_inq_path(ncid, &path_len, path_in)) ERR; */
/*       /\*if (path_len != strlen(URL) || strcmp(path_in, URL)) ERR;*\/ */
/*       if (nc_close(ncid)) ERR; */
/* #endif /\* USE_DAP *\/ */
   }
   SUMMARIZE_ERR;
   printf("*** Checking format setting...");
   {
#define NUM_FORMAT 4
      int ncid, varid, dimid, format, i;
      int form[NUM_FORMAT] = {NC_FORMAT_CLASSIC, NC_FORMAT_64BIT, 
			      NC_FORMAT_NETCDF4, NC_FORMAT_NETCDF4_CLASSIC};

      for (i = 0; i < NUM_FORMAT; i++)
      {
	 if (nc_set_default_format(form[i], NULL)) ERR;
	 if (nc_create(FILE_NAME, NC_CLOBBER,&ncid)) ERR;
	 if (nc_def_dim(ncid, "x", 1,&dimid)) ERR;
	 if (nc_def_var(ncid, "y", NC_FLOAT, 1, &dimid, &varid)) ERR;
	 if (nc_close(ncid)) ERR;

	 if (nc_open(FILE_NAME, NC_NOWRITE, &ncid)) ERR;
	 if (nc_inq_format(ncid, &format)) ERR;
	 if (format != form[i]) ERR;
	 if (nc_close(ncid)) ERR;
      }
   }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}


