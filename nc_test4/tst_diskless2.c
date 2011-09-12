/** \file \internal
Basic diskless API tests.
   
Copyright 2011, UCAR/Unidata. See COPYRIGHT file for copying and
redistribution conditions.
*/

#include <config.h>
#include <nc_tests.h>
#include <stdio.h>
#include <stdlib.h>
#include <netcdf.h>

#define FILE_NAME "tst_diskless2.nc"

int
main(int argc, char **argv) 
{
   printf("\n*** Testing the diskless API some more.\n");
   printf("*** testing diskless file with 1 2D var with unlimited dimension reading multiple times...");
   {
#define RADAR "radar"
#define METEOROLOGY "METEOROLOGY"
#define CLOUD "CLOUD"
#define RAIN "rain"
#define NDIMS2 2
#define METEOROLOGY_LEN2 20
#define CLOUD_LEN2 20

      int ncid, varid, dimid[NDIMS2];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[CLOUD_LEN2][METEOROLOGY_LEN2];
      char char_data_in[CLOUD_LEN2][METEOROLOGY_LEN2];
      char char_datum;
      size_t start[NDIMS2] = {0, 0}, count[NDIMS2];
      size_t len;
      int p, b, i = 0;

      for (p = 0; p < CLOUD_LEN2; p++)
	 for (b = 0; b < METEOROLOGY_LEN2; b++)
	    char_data[p][b] = i++;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, CLOUD, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, METEOROLOGY, METEOROLOGY_LEN2, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, RAIN, NC_CHAR, NDIMS2, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = CLOUD_LEN2;
      count[1] = METEOROLOGY_LEN2;
      if (nc_put_vara_text(ncid, varid, start, count, &char_data[0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS2 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, RAIN) || type_in != NC_CHAR || ndims_in != NDIMS2
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Read the data. */
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < CLOUD_LEN2; p++)
	 for (b = 0; b < METEOROLOGY_LEN2; b++)
	       if (char_data_in[p][b] != char_data[p][b]) ERR;

      /* Read just one value. */
      start[0] = CLOUD_LEN2 - 1;
      start[1] = METEOROLOGY_LEN2 - 1;
      count[0] = 1;
      count[1] = 1;
      if (nc_get_vara_text(ncid, varid, start, count, &char_datum)) ERR;
      if (char_datum != char_data[CLOUD_LEN2 - 1][METEOROLOGY_LEN2 - 1]) ERR;

      if (nc_get_var1_text(ncid, varid, start, &char_datum)) ERR;
      if (char_datum != char_data[CLOUD_LEN2 - 1][METEOROLOGY_LEN2 - 1]) ERR;

      /* Check the length of the unlimited dimension. */
      if (nc_inq_dimlen(ncid, dimid[0], &len)) ERR;
      if (len != CLOUD_LEN2) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}
