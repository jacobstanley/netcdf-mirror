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
#define CLOUD_LEN2 4
#define METEOROLOGY_LEN2 3

      int ncid, varid, dimid[NDIMS2];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[CLOUD_LEN2][METEOROLOGY_LEN2];
      char char_data_in[2][2];
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

      /* Read part of the data. */
      start[0] = 2;
      start[1] = 1;
      count[0] = 2;
      count[1] = 2;
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0])) ERR;
      if (char_data_in[0][0] != char_data[2][1]) ERR;
      if (char_data_in[0][1] != char_data[2][2]) ERR;
      if (char_data_in[1][0] != char_data[3][1]) ERR;
      if (char_data_in[1][1] != char_data[3][2]) ERR;

      /* Check the length of the unlimited dimension. */
      if (nc_inq_dimlen(ncid, dimid[0], &len)) ERR;
      if (len != CLOUD_LEN2) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 1 3D var reading multiple times...");
   {
#define SANDWORMS "sandworms"
#define DUNE "DUNE"
#define HUNTERS "HUNTERS"
#define CHAPTERHOUSE "chapterhouse"
#define NDIMS3 3
#define SANDWORMS_LEN2 2
#define HUNTERS_LEN2 4
#define DUNE_LEN2 3

      int ncid, varid, dimid[NDIMS3];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[SANDWORMS_LEN2][HUNTERS_LEN2][DUNE_LEN2];
      char char_data_in[1][2][2];
      size_t start[NDIMS3] = {0, 0, 0}, count[NDIMS3];
      int p, b, s, i = 0;

      for (s = 0; s < SANDWORMS_LEN2; s++)
	 for (p = 0; p < HUNTERS_LEN2; p++)
	    for (b = 0; b < DUNE_LEN2; b++)
	       char_data[s][p][b] = i++;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, SANDWORMS, SANDWORMS_LEN2, &dimid[0])) ERR;
      if (nc_def_dim(ncid, HUNTERS, HUNTERS_LEN2, &dimid[1])) ERR;
      if (nc_def_dim(ncid, DUNE, DUNE_LEN2, &dimid[2])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, CHAPTERHOUSE, NC_CHAR, NDIMS3, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = SANDWORMS_LEN2;
      count[1] = HUNTERS_LEN2;
      count[2] = DUNE_LEN2;
      if (nc_put_vara_text(ncid, varid, start, count, &char_data[0][0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS3 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != -1) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, CHAPTERHOUSE) || type_in != NC_CHAR || ndims_in != NDIMS3
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || dimids_in[2] != 2 || natts_in) ERR;

      /* Read part of the data. */
      start[0] = 1;
      start[1] = 1;
      start[2] = 1;
      count[0] = 1;
      count[1] = 2;
      count[2] = 2;
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0][0])) ERR;
      if (char_data_in[0][0][0] != char_data[1][1][1]) ERR;
      if (char_data_in[0][0][1] != char_data[1][1][2]) ERR;
      if (char_data_in[0][1][0] != char_data[1][2][1]) ERR;
      if (char_data_in[0][1][1] != char_data[1][2][2]) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 1 3D text var like nc_test...");
   {
#define DIM0 "dim0"
#define DIM2 "DIM2"
#define DIM1 "DIM1"
#define TIRE "tire"
#define NDIMS3 3
#define DIM0_LEN2 1
#define DIM1_LEN2 1
#define DIM2_LEN2 1

      int ncid, varid, dimid[NDIMS3];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[DIM0_LEN2][DIM1_LEN2][DIM2_LEN2];
      char char_data_in[1][1][1];
      size_t start[NDIMS3] = {0, 0, 0}, count[NDIMS3];
      int p, b, s, i = 0;

      for (s = 0; s < DIM0_LEN2; s++)
	 for (p = 0; p < DIM1_LEN2; p++)
	    for (b = 0; b < DIM2_LEN2; b++)
	       char_data[s][p][b] = i++;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, DIM0, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, DIM1, DIM1_LEN2, &dimid[2])) ERR;
      if (nc_def_dim(ncid, DIM2, DIM2_LEN2, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, CHAPTERHOUSE, NC_CHAR, NDIMS3, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = DIM0_LEN2;
      count[1] = DIM1_LEN2;
      count[2] = DIM2_LEN2;
      if (nc_put_vara_text(ncid, varid, start, count, &char_data[0][0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS3 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, CHAPTERHOUSE) || type_in != NC_CHAR || ndims_in != NDIMS3
	  || dimids_in[0] != 0 || dimids_in[1] != 2 || dimids_in[2] != 1 || natts_in) ERR;

      /* Read part of the data. */
      start[0] = 0;
      start[1] = 0;
      start[2] = 0;
      count[0] = 1;
      count[1] = 1;
      count[2] = 1;
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0][0])) ERR;
      if (char_data_in[0][0][0] != char_data[0][0][0]) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with another 1 3D text var like nc_test...");
   {
#define DIM0 "dim0"
#define DIM2 "DIM2"
#define DIM1 "DIM1"
#define TIRE "tire"
#define NDIMS3 3
#define DIM0_LEN 3
#define DIM1_LEN 3
#define DIM2_LEN 3

      int ncid, varid, dimid[NDIMS3];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[DIM0_LEN][DIM1_LEN][DIM2_LEN];
      char char_data_in[1][1][1];
      size_t start[NDIMS3] = {0, 0, 0}, count[NDIMS3];
      int p, b, s, i = 0;

      for (s = 0; s < DIM0_LEN; s++)
	 for (p = 0; p < DIM1_LEN; p++)
	    for (b = 0; b < DIM2_LEN; b++)
	       char_data[s][p][b] = i++;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, DIM0, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, DIM1, DIM1_LEN, &dimid[2])) ERR;
      if (nc_def_dim(ncid, DIM2, DIM2_LEN, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, CHAPTERHOUSE, NC_CHAR, NDIMS3, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = DIM0_LEN;
      count[1] = DIM1_LEN;
      count[2] = DIM2_LEN;
      if (nc_put_vara_text(ncid, varid, start, count, &char_data[0][0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS3 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, CHAPTERHOUSE) || type_in != NC_CHAR || ndims_in != NDIMS3
	  || dimids_in[0] != 0 || dimids_in[1] != 2 || dimids_in[2] != 1 || natts_in) ERR;

      /* Read part of the data. */
      start[0] = 0;
      start[1] = 1;
      start[2] = 0;
      count[0] = 1;
      count[1] = 1;
      count[2] = 1;
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0][0])) ERR;
      if (char_data_in[0][0][0] != char_data[0][1][0]) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with yet another 1 3D text var like nc_test...");
   {
#define DIM0 "dim0"
#define DIM2 "DIM2"
#define DIM1 "DIM1"
#define NDIMS3 3
#define DIM0_LENGTH 2
#define DIM1_LENGTH 1
#define DIM2_LENGTH 2
#define VAR "var"

      int ncid, varid, dimid[NDIMS3];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[DIM0_LENGTH][DIM2_LENGTH][DIM1_LENGTH];
      char char_data_in[DIM0_LENGTH][DIM2_LENGTH][DIM1_LENGTH];
      size_t start[NDIMS3] = {0, 0, 0}, count[NDIMS3];
      int p, b, s, i = 0;

      for (s = 0; s < DIM0_LENGTH; s++)
	 for (b = 0; b < DIM2_LENGTH; b++)
	    for (p = 0; p < DIM1_LENGTH; p++)
	       char_data[s][b][p] = i++;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, DIM0, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, DIM1, DIM1_LENGTH, &dimid[2])) ERR;
      if (nc_def_dim(ncid, DIM2, DIM2_LENGTH, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, VAR, NC_CHAR, NDIMS3, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = DIM0_LENGTH;
      count[1] = DIM2_LENGTH;
      count[2] = DIM1_LENGTH;
      if (nc_put_vara_text(ncid, varid, start, count, &char_data[0][0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS3 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, VAR) || type_in != NC_CHAR || ndims_in != NDIMS3
	  || dimids_in[0] != 0 || dimids_in[1] != 2 || dimids_in[2] != 1 || natts_in) ERR;

      /* Read part of the data. */
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0][0])) ERR;
      for (s = 0; s < DIM0_LENGTH; s++)
	 for (b = 0; b < DIM2_LENGTH; b++)
	    for (p = 0; p < DIM1_LENGTH; p++)
	       if (char_data[s][b][p] != char_data_in[s][b][p]) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with a 2D text var like nc_test...");
   {
#define DIM0 "dim0"
#define DIM1 "DIM1"
#define NDIMS2 2
#define DIM0_LENGTH1 3
#define DIM1_LENGTH1 4
#define VAR "var"

      int ncid, varid, dimid[NDIMS2];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      char char_data[DIM1_LENGTH1][DIM0_LENGTH1];
      char char_data_in[2][1];
      size_t start[NDIMS2] = {0, 0}, count[NDIMS2];
      int p, s, i = 0;

      for (s = 0; s < DIM1_LENGTH1; s++)
	 for (p = 0; p < DIM0_LENGTH1; p++)
	    char_data[s][p] = i++;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, DIM0, DIM0_LENGTH1, &dimid[1])) ERR;
      if (nc_def_dim(ncid, DIM1, DIM1_LENGTH1, &dimid[0])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, VAR, NC_CHAR, NDIMS2, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = DIM1_LENGTH1;
      count[1] = DIM0_LENGTH1;
      if (nc_put_vara_text(ncid, varid, start, count, &char_data[0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS2 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != -1) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, VAR) || type_in != NC_CHAR || ndims_in != NDIMS2
	  || dimids_in[0] != 1 || dimids_in[1] != 0 || natts_in) ERR;

      /* Read part of the data. */
      start[0] = 2;
      start[1] = 0;
      count[0] = 2;
      count[1] = 1;
      if (nc_get_vara_text(ncid, varid, start, count, &char_data_in[0][0])) ERR;
      if (char_data_in[0][0] != char_data[2][0]) ERR;
      if (char_data_in[1][0] != char_data[3][0]) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}
