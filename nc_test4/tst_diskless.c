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

#define FILE_NAME "tst_diskless.nc"

int
main(int argc, char **argv) 
{
   printf("\n*** Testing the diskless API.\n");
   printf("*** testing diskless file with scalar vars...");
   {
#define RESISTOR "resistor_value"
#define CAPACITOR "capacitor_value"    
#define NUM555 "number_of_555_timer_chips"

      int ncid, varid0, varid1, varid2;
      int ndims_in, nvars_in, natts_in, unlimdimid_in;
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      float float_data = 3.14, float_data_in;
      int int_data = 42, int_data_in;
      short short_data = 2, short_data_in;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL, 
		    &ncid)) ERR;

      /* Create some variables. */
      if (nc_def_var(ncid, RESISTOR, NC_INT, 0, NULL, &varid0)) ERR;
      if (nc_def_var(ncid, CAPACITOR, NC_FLOAT, 0, NULL, &varid1)) ERR;
      if (nc_def_var(ncid, NUM555, NC_SHORT, 0, NULL, &varid2)) ERR;

      /* Write some data to this file. */
      if (nc_put_vara_int(ncid, varid0, NULL, NULL, &int_data)) ERR;
      if (nc_put_vara_float(ncid, varid1, NULL, NULL, &float_data)) ERR;
      if (nc_put_vara_short(ncid, varid2, NULL, NULL, &short_data)) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != 0 || nvars_in != 3 || natts_in != 0 || unlimdimid_in != -1) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid0, name_in, &type_in, &ndims_in, NULL, &natts_in)) ERR;
      if (strcmp(name_in, RESISTOR) || type_in != NC_INT || ndims_in != 0 ||
      	  natts_in != 0) ERR;
      if (nc_inq_var(ncid, varid1, name_in, &type_in, &ndims_in, NULL, &natts_in)) ERR;
      if (strcmp(name_in, CAPACITOR) || type_in != NC_FLOAT || ndims_in != 0 ||
      	  natts_in != 0) ERR;
      if (nc_inq_var(ncid, varid2, name_in, &type_in, &ndims_in, NULL, &natts_in)) ERR;
      if (strcmp(name_in, NUM555) || type_in != NC_SHORT || natts_in != 0) ERR;

      /* Read my absolutely crucial data. */
      if (nc_get_vara_int(ncid, varid0, NULL, NULL, &int_data_in)) ERR;
      if (int_data_in != int_data) ERR;
      if (nc_get_vara_float(ncid, varid1, NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != float_data) ERR;
      if (nc_get_vara_short(ncid, varid2, NULL, NULL, &short_data_in)) ERR;
      if (short_data_in != short_data) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing creation of simple diskless file...");
   {
#define NDIMS 2
#define DIM0_NAME "Fun"
#define DIM1_NAME "Money"
#define DIM1_LEN 200
#define ATT0_NAME "home"
#define ATT0_TEXT "earthship"
#define VAR0_NAME "nightlife"
#define VAR1_NAME "time"
#define VAR2_NAME "taxi_distance"

      int ncid, dimid[NDIMS], dimid_in[NDIMS], varid0, varid1, varid2;
      int ndims_in, nvars_in, natts_in, unlimdimid_in;
      char name_in[NC_MAX_NAME + 1], att0_in[NC_MAX_NAME + 1];
      nc_type type_in;
      size_t len_in;
      short short_data[DIM1_LEN];
      size_t start[1] = {0};
      size_t count[1] = {DIM1_LEN};
      int i;
      float float_data = 42.22, float_data_in;

      /* This is some really important data that I want to save. */
      for (i = 0; i < DIM1_LEN; i++)
	 short_data[i] = i;
      
      /* Create a netCDF file (which exists only in memory). I am
       * confident that the world-famous netCDF format is the way to
       * store my data! */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL, &ncid)) ERR;

      /* Create some atts. They will help document my data forever. */
      if (nc_put_att_text(ncid, NC_GLOBAL, ATT0_NAME,
			  sizeof(ATT0_TEXT) + 1, ATT0_TEXT)) ERR;

      /* Create dimensions: money is limited, but fun is not! */
      if (nc_def_dim(ncid, DIM0_NAME, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, DIM1_NAME, DIM1_LEN, &dimid[1])) ERR;

      /* Create some variables. The data they hold must persist
       * through the ages. */
      if (nc_def_var(ncid, VAR0_NAME, NC_INT, NDIMS, dimid, &varid0)) ERR;
      if (nc_def_var(ncid, VAR1_NAME, NC_FLOAT, 0, NULL, &varid1)) ERR;
      if (nc_def_var(ncid, VAR2_NAME, NC_SHORT, 1, &dimid[1], &varid2)) ERR;

      /* Write some data to this file. I'm glad I'm saving this
       * important data in such a safe format! */
      if (nc_put_vara_float(ncid, varid1, NULL, NULL, &float_data)) ERR;
      if (nc_put_vara_short(ncid, varid2, start, count, short_data)) ERR;

      /* Now check the phony file. Is my data safe? */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != 2 || nvars_in != 3 || natts_in != 1 || unlimdimid_in != 0) ERR;

      /* Check attributes - they will be needed by future generations
       * of scientists to understand my data. */
      if (nc_get_att_text(ncid, NC_GLOBAL, ATT0_NAME, att0_in)) ERR;
      if (strcmp(att0_in, ATT0_TEXT)) ERR;
      
      /* Check dimensions. */
      if (nc_inq_dim(ncid, dimid[0], name_in, &len_in)) ERR;
      if (strcmp(name_in, DIM0_NAME) || len_in != 0) ERR;
      if (nc_inq_dim(ncid, dimid[1], name_in, &len_in)) ERR;
      if (strcmp(name_in, DIM1_NAME) || len_in != DIM1_LEN) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid0, name_in, &type_in, &ndims_in, dimid_in, &natts_in)) ERR;
      if (strcmp(name_in, VAR0_NAME) || type_in != NC_INT || ndims_in != NDIMS ||
	  dimid_in[0] != 0 || dimid_in[1] != 1 || natts_in != 0) ERR;
      if (nc_inq_var(ncid, varid1, name_in, &type_in, &ndims_in, dimid_in, &natts_in)) ERR;
      if (strcmp(name_in, VAR1_NAME) || type_in != NC_FLOAT || ndims_in != 0 ||
	  natts_in != 0) ERR;
      if (nc_inq_var(ncid, varid2, name_in, &type_in, &ndims_in, dimid_in, &natts_in)) ERR;
      if (strcmp(name_in, VAR2_NAME) || type_in != NC_SHORT || ndims_in != 1 ||
	  dimid_in[0] != 1 || natts_in != 0) ERR;

      /* Read my absolutely crucial data. */
      if (nc_get_vara_float(ncid, varid1, NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != float_data) ERR;

      /* Close the file, losing all information. Hey! What kind of
       * storage format is this, anyway? */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with scalar vars and type conversion while writing...");
   {
#define NVARS 5

      int ncid, varid[NVARS];
      int ndims_in, nvars_in, natts_in, unlimdimid_in;
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      float float_data = 3.14, float_data_in; 
      int int_data_in;
      short short_data_in;
      double double_data_in;
      signed char schar_data_in = 0;
      char var_name[NVARS][NC_MAX_NAME + 1];
      nc_type var_type[NVARS] = {NC_BYTE, NC_SHORT, NC_INT, NC_FLOAT, NC_DOUBLE};
      int i;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      for (i = 0; i < NVARS; i++)
      {
	 sprintf(var_name[i], "name_%d", i);
	 if (nc_def_var(ncid, var_name[i], var_type[i], 0, NULL, &varid[i])) ERR;
      }

      /* Write some data to this file. */
      for(i = 0; i < NVARS; i++)
	 if (nc_put_vara_float(ncid, varid[i], NULL, NULL, &float_data)) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != 0 || nvars_in != NVARS || natts_in != 0 ||
      	  unlimdimid_in != -1) ERR;

      /* Check variables. */
      for(i = 0; i < NVARS; i++)
      {
      	 if (nc_inq_var(ncid, varid[i], name_in, &type_in, &ndims_in,
      			NULL, &natts_in)) ERR;
      	 if (strcmp(name_in, var_name[i]) || type_in != var_type[i] ||
      	     ndims_in || natts_in) ERR;
      }

      /* Read my absolutely crucial data. */
      if (nc_get_vara_schar(ncid, varid[0], NULL, NULL, &schar_data_in)) ERR; 
      if (schar_data_in != (signed char)float_data) ERR; 
      if (nc_get_vara_short(ncid, varid[1], NULL, NULL, &short_data_in)) ERR;
      if (short_data_in != (short)float_data) ERR;
      if (nc_get_vara_int(ncid, varid[2], NULL, NULL, &int_data_in)) ERR;
      if (int_data_in != (int)float_data) ERR;
      if (nc_get_vara_float(ncid, varid[3], NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != float_data) ERR;
      if (nc_get_vara_double(ncid, varid[4], NULL, NULL, &double_data_in)) ERR;
      if (double_data_in != (double)float_data) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with scalar vars and type conversion while reading...");
   {
#define NVARS 5

      int ncid, varid[NVARS];
      int ndims_in, nvars_in, natts_in, unlimdimid_in;
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      float float_data = 3.14, float_data_in = 0;
      int int_data = 3333;
      short short_data =  233;
      double double_data = 3.0;
      signed char schar_data = 3;
      char var_name[NVARS][NC_MAX_NAME + 1];
      nc_type var_type[NVARS] = {NC_BYTE, NC_SHORT, NC_INT, NC_FLOAT, NC_DOUBLE};
      int i;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      for (i = 0; i < NVARS; i++)
      {
	 sprintf(var_name[i], "name_%d", i);
	 if (nc_def_var(ncid, var_name[i], var_type[i], 0, NULL,
			&varid[i])) ERR;
      }

      /* Write some data to this file. */
      if (nc_put_vara_schar(ncid, varid[0], NULL, NULL, &schar_data)) ERR;
      if (nc_put_vara_short(ncid, varid[1], NULL, NULL, &short_data)) ERR;
      if (nc_put_vara_int(ncid, varid[2], NULL, NULL, &int_data)) ERR;
      if (nc_put_vara_float(ncid, varid[3], NULL, NULL, &float_data)) ERR;
      if (nc_put_vara_double(ncid, varid[4], NULL, NULL, &double_data)) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != 0 || nvars_in != NVARS || natts_in != 0 ||
	  unlimdimid_in != -1) ERR;

      /* Check variables. */
      for(i = 0; i < NVARS; i++)
      {
	 if (nc_inq_var(ncid, varid[i], name_in, &type_in, &ndims_in,
			NULL, &natts_in)) ERR;
	 if (strcmp(name_in, var_name[i]) || type_in != var_type[i] ||
	     ndims_in || natts_in) ERR;
      }

      /* Read my absolutely crucial data. */
      if (nc_get_vara_float(ncid, varid[0], NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != (float)schar_data) ERR;
      if (nc_get_vara_float(ncid, varid[1], NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != (float)short_data) ERR;
      if (nc_get_vara_float(ncid, varid[2], NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != (float)int_data) ERR;
      if (nc_get_vara_float(ncid, varid[3], NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != float_data) ERR;
      if (nc_get_vara_float(ncid, varid[4], NULL, NULL, &float_data_in)) ERR;
      if (float_data_in != (float)double_data) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 1D vars with unlimited dimension...");
   {
#define NVARS 5
#define DIM_NAME "a_really_fun_dimension"

      int ncid, varid[NVARS], dimid;
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[1];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      float float_data = 3.14, float_data_in;
      int int_data = 3333;
      short short_data =  233;
      double double_data = 3.0;
      signed char schar_data = 3;
      char var_name[NVARS][NC_MAX_NAME + 1];
      nc_type var_type[NVARS] = {NC_BYTE, NC_SHORT, NC_INT, NC_FLOAT, NC_DOUBLE};
      size_t start[1] = {0}, count[1] = {1};
      int i;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      if (nc_def_dim(ncid, DIM_NAME, NC_UNLIMITED, &dimid)) ERR;

      for (i = 0; i < NVARS; i++)
      {
	 sprintf(var_name[i], "name_%d", i);
	 if (nc_def_var(ncid, var_name[i], var_type[i], 1, &dimid,
			&varid[i])) ERR;
      }

      /* Write some data to this file. */
      if (nc_put_vara_schar(ncid, varid[0], start, count, &schar_data)) ERR;
      if (nc_put_vara_short(ncid, varid[1], start, count, &short_data)) ERR;
      if (nc_put_vara_int(ncid, varid[2], start, count, &int_data)) ERR;
      if (nc_put_vara_float(ncid, varid[3], start, count, &float_data)) ERR;
      if (nc_put_vara_double(ncid, varid[4], start, count, &double_data)) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != 1 || nvars_in != NVARS || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variables. */
      for(i = 0; i < NVARS; i++)
      {
	 if (nc_inq_var(ncid, varid[i], name_in, &type_in, &ndims_in,
			dimids_in, &natts_in)) ERR;
	 if (strcmp(name_in, var_name[i]) || type_in != var_type[i] ||
	     ndims_in != 1 || dimids_in[0] != 0 || natts_in) ERR;
      }

      /* Read my absolutely crucial data. */
      if (nc_get_vara_float(ncid, varid[0], start, count, &float_data_in)) ERR;
      if (float_data_in != (float)schar_data) ERR;
      if (nc_get_vara_float(ncid, varid[1], start, count, &float_data_in)) ERR;
      if (float_data_in != (float)short_data) ERR;
      if (nc_get_vara_float(ncid, varid[2], start, count, &float_data_in)) ERR;
      if (float_data_in != (float)int_data) ERR;
      if (nc_get_vara_float(ncid, varid[3], start, count, &float_data_in)) ERR;
      if (float_data_in != float_data) ERR;
      if (nc_get_vara_float(ncid, varid[4], start, count, &float_data_in)) ERR;
      if (float_data_in != (float)double_data) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 2D var with unlimited dimension...");
   {
#define WETTNESS "wettness"
#define PRICE "price"
#define BEER "beer"
#define NDIMS2 2
#define WETTNESS_LEN 3
#define PRICE_LEN 1

      int ncid, varid, dimid[NDIMS2];
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      int int_data[PRICE_LEN][WETTNESS_LEN];
      int int_data_in[PRICE_LEN][WETTNESS_LEN];
      size_t start[NDIMS2] = {0, 0}, count[NDIMS2];
      int p, w;

      for (p = 0; p < PRICE_LEN; p++)
	 for (w = 0; w < WETTNESS_LEN; w++)
	    int_data[p][w] = p * w;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, PRICE, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, WETTNESS, WETTNESS_LEN, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, BEER, NC_INT, NDIMS2, dimid, &varid)) ERR;

      /* Write some data to the variable. */
      count[0] = PRICE_LEN;
      count[1] = WETTNESS_LEN;
      if (nc_put_vara_int(ncid, varid, start, count, &int_data[0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS2 || nvars_in != 1 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variable. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, BEER) || type_in != NC_INT || ndims_in != NDIMS2
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Read the data. */
      if (nc_get_vara_int(ncid, varid, start, count, &int_data_in[0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < PRICE_LEN; p++)
	 for (w = 0; w < WETTNESS_LEN; w++)
	    if (int_data_in[p][w] != int_data[p][w]) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 2 2D vars with unlimited dimension...");
   {
#define WETTNESS "wettness"
#define PRICE "price"
#define BEER "beer"
#define WINE "wine"
#define NDIMS2 2
#define WETTNESS_LEN 3
#define PRICE_LEN 1

      int ncid, varid, dimid[NDIMS2], varid2;
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      int int_data[PRICE_LEN][WETTNESS_LEN];
      int int_data_in[PRICE_LEN][WETTNESS_LEN];
      size_t start[NDIMS2] = {0, 0}, count[NDIMS2];
      size_t len;
      int p, w;

      for (p = 0; p < PRICE_LEN; p++)
	 for (w = 0; w < WETTNESS_LEN; w++)
	    int_data[p][w] = p * w;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, PRICE, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, WETTNESS, WETTNESS_LEN, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, BEER, NC_INT, NDIMS2, dimid, &varid)) ERR;
      if (nc_def_var(ncid, WINE, NC_INT, NDIMS2, dimid, &varid2)) ERR;

      /* Write some data to the variable. */
      count[0] = PRICE_LEN;
      count[1] = WETTNESS_LEN;
      if (nc_put_vara_int(ncid, varid, start, count, &int_data[0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS2 || nvars_in != 2 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, BEER) || type_in != NC_INT || ndims_in != NDIMS2
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid2, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, WINE) || type_in != NC_INT || ndims_in != NDIMS2
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Read the data. */
      if (nc_get_vara_int(ncid, varid, start, count, &int_data_in[0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < PRICE_LEN; p++)
	 for (w = 0; w < WETTNESS_LEN; w++)
	    if (int_data_in[p][w] != int_data[p][w]) ERR;

      /* Check the length of the unlimited dimension. */
      if (nc_inq_dimlen(ncid, dimid[0], &len)) ERR;
      if (len != PRICE_LEN) ERR;

      /* Get data from the other var - should get fill values. */
      if (nc_get_vara_int(ncid, varid2, start, count, &int_data_in[0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < PRICE_LEN; p++)
	 for (w = 0; w < WETTNESS_LEN; w++)
	    if (int_data_in[p][w] != NC_FILL_INT) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 2 2D vars with unlimited dimension using subsets...");
   {
#define WETTNESS "wettness"
#define PRICE "price"
#define BEER "beer"
#define WINE "wine"
#define NDIMS2 2
#define WETTNESS_LEN2 10
#define PRICE_LEN2 34

      int ncid, varid, dimid[NDIMS2], varid2;
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      int int_data[PRICE_LEN2][WETTNESS_LEN2];
      int int_data_in[PRICE_LEN2][WETTNESS_LEN2];
      size_t start[NDIMS2] = {0, 0}, count[NDIMS2];
      size_t len;
      int p, w;

      for (p = 0; p < PRICE_LEN2; p++)
	 for (w = 0; w < WETTNESS_LEN2; w++)
	    int_data[p][w] = p * w;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, PRICE, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, WETTNESS, WETTNESS_LEN2, &dimid[1])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, BEER, NC_INT, NDIMS2, dimid, &varid)) ERR;
      if (nc_def_var(ncid, WINE, NC_INT, NDIMS2, dimid, &varid2)) ERR;

      /* Write some data to the variable. */
      count[0] = PRICE_LEN2;
      count[1] = WETTNESS_LEN2;
      if (nc_put_vara_int(ncid, varid, start, count, &int_data[0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS2 || nvars_in != 2 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, BEER) || type_in != NC_INT || ndims_in != NDIMS2
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid2, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, WINE) || type_in != NC_INT || ndims_in != NDIMS2
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Read the data. */
      if (nc_get_vara_int(ncid, varid, start, count, &int_data_in[0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < PRICE_LEN2; p++)
	 for (w = 0; w < WETTNESS_LEN2; w++)
	    if (int_data_in[p][w] != int_data[p][w]) ERR;

      /* Check the length of the unlimited dimension. */
      if (nc_inq_dimlen(ncid, dimid[0], &len)) ERR;
      if (len != PRICE_LEN2) ERR;

      /* Get data from the other var - should get fill values. */
      if (nc_get_vara_int(ncid, varid2, start, count, &int_data_in[0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < PRICE_LEN2; p++)
	 for (w = 0; w < WETTNESS_LEN2; w++)
	    if (int_data_in[p][w] != NC_FILL_INT) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   printf("*** testing diskless file with 2 3D vars with unlimited dimension using subsets...");
   {
#define WINSTON "winston"
#define BIRTH "BIRTH"
#define BRITAIN "BRITAIN"
#define SAXON "saxon"
#define ANGLO "anglo"
#define NDIMS3 3
#define BIRTH_LEN2 1
#define BRITAIN_LEN2 1
#define WINSTON_LEN2 1

      int ncid, varid, dimid[NDIMS3], varid2;
      int ndims_in, nvars_in, natts_in, unlimdimid_in, dimids_in[2];
      char name_in[NC_MAX_NAME + 1];
      nc_type type_in;
      int int_data[BRITAIN_LEN2][BIRTH_LEN2][WINSTON_LEN2];
      int int_data_in[BRITAIN_LEN2][BIRTH_LEN2][WINSTON_LEN2];
      size_t start[NDIMS3] = {0, 0, 0}, count[NDIMS3];
      size_t len;
      int p, b, w;

      for (p = 0; p < BRITAIN_LEN2; p++)
	 for (b = 0; b < BIRTH_LEN2; b++)
	    for (w = 0; w < WINSTON_LEN2; w++)
	       int_data[p][b][w] = p * w * b;

      /* Create a netCDF file (which exists only in memory). */
      if (nc_create(FILE_NAME, NC_DISKLESS|NC_NETCDF4|NC_CLASSIC_MODEL,
		    &ncid)) ERR;

      /* Define two dimensions. */
      if (nc_def_dim(ncid, BRITAIN, NC_UNLIMITED, &dimid[0])) ERR;
      if (nc_def_dim(ncid, BIRTH, BIRTH_LEN2, &dimid[1])) ERR;
      if (nc_def_dim(ncid, WINSTON, WINSTON_LEN2, &dimid[2])) ERR;

      /* Define a variable. */
      if (nc_def_var(ncid, SAXON, NC_INT, NDIMS3, dimid, &varid)) ERR;
      if (nc_def_var(ncid, ANGLO, NC_INT, NDIMS3, dimid, &varid2)) ERR;

      /* Write some data to the variable. */
      count[0] = BRITAIN_LEN2;
      count[1] = BIRTH_LEN2;
      count[2] = WINSTON_LEN2;
      if (nc_put_vara_int(ncid, varid, start, count, &int_data[0][0][0])) ERR;

      /* Now check the phony file. */
      if (nc_inq(ncid, &ndims_in, &nvars_in, &natts_in, &unlimdimid_in)) ERR;
      if (ndims_in != NDIMS3 || nvars_in != 2 || natts_in != 0 ||
	  unlimdimid_in != 0) ERR;

      /* Check variables. */
      if (nc_inq_var(ncid, varid, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, SAXON) || type_in != NC_INT || ndims_in != NDIMS3
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;
      if (nc_inq_var(ncid, varid2, name_in, &type_in, &ndims_in,
		     dimids_in, &natts_in)) ERR;
      if (strcmp(name_in, ANGLO) || type_in != NC_INT || ndims_in != NDIMS3
	  || dimids_in[0] != 0 || dimids_in[1] != 1 || natts_in) ERR;

      /* Read the data. */
      if (nc_get_vara_int(ncid, varid, start, count, &int_data_in[0][0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < BRITAIN_LEN2; p++)
	 for (b = 0; b < BIRTH_LEN2; b++)
	    for (w = 0; w < WINSTON_LEN2; w++)
	       if (int_data_in[p][b][w] != int_data[p][b][w]) ERR;

      /* Check the length of the unlimited dimension. */
      if (nc_inq_dimlen(ncid, dimid[0], &len)) ERR;
      if (len != BRITAIN_LEN2) ERR;

      /* Get data from the other var - should get fill values. */
      if (nc_get_vara_int(ncid, varid2, start, count, &int_data_in[0][0][0])) ERR;

      /* Check the result. */
      for (p = 0; p < BRITAIN_LEN2; p++)
	 for (b = 0; b < BIRTH_LEN2; b++)
	    for (w = 0; w < WINSTON_LEN2; w++)
	       if (int_data_in[p][b][w] != NC_FILL_INT) ERR;

      /* Close the file. */
      if (nc_close(ncid)) ERR;
   }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}
