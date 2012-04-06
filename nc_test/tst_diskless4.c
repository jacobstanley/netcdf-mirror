/*
  Copyright 2008, UCAR/Unidata
  See COPYRIGHT file for copying and redistribution conditions.

  This program tests the large file bug in netCDF 3.6.2,
  creating byte and short variables larger than 4 GiB.

  $Id: tst_big_var.c,v 1.9 2010/05/15 00:50:10 russ Exp $
*/

#include <nc_tests.h>
#include <netcdf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
 * Depending on argv, do one of the following:
1. create a file with var of size 0x40000000 (~ 1 gig)
2. create a file with var of size 0x40000000 (~ 1 gig) but using NC_DISKLESS
3. open a file with var of size 0x40000000 (~ 1 gig) and read it 4096 bytes
   at a time
4. open a file with var of size 0x40000000 (~ 1 gig) and read it 4096 bytes
   at a time using NC_DISKLESS
 */

#define FILE_NAME "tst_diskless4.nc"
#define CHUNKSIZE 4096
#define GIG1 (1024*1024*1024)
#define DATASIZE (CHUNKSIZE/sizeof(int))

typedef enum Tag {Create,CreateDiskless,Open,OpenDiskless} Tag;

static size_t varsize;
static size_t pieces;
static float gigsize;

int
main(int argc, char **argv) {
    int i,j;
    unsigned int data[DATASIZE];
    size_t start[1];
    size_t count[1];
    Tag tag = Create; 
    int cmode = 0;
    int ncid,varid;
    int dimids[1];

    /* First, determine a reasonable file size that malloc will actually allocate
       on this machine
     */

    for(varsize=GIG1;;varsize/=2) {
	void* memory = malloc(varsize);
	if(memory != NULL) {free(memory); break;}
	free(memory);
    }

    /* Compute other values relative to varsize */
    pieces = varsize/CHUNKSIZE;
    gigsize = (varsize/GIG1);

    if(argc > 1) {
        if(strcmp(argv[1],"create")==0) tag = Create;
        else if(strcmp(argv[1],"creatediskless")==0) tag = CreateDiskless;
        else if(strcmp(argv[1],"open")==0) tag = Open;
        else if(strcmp(argv[1],"opendiskless")==0) tag = OpenDiskless;
	else {
	    fprintf(stderr,"illegal tag: %s",argv[1]);
	    exit(1);
	}
    }
    
    switch (tag) {
    case Create: printf("\n*** Create %0.2gG file\n",gigsize); break;
    case CreateDiskless: printf("\n*** Create %0.2gG diskless\n",gigsize); break;
    case Open: printf("\n*** Open %0.2gG file\n",gigsize); break;
    case OpenDiskless: printf("\n*** Open %0.2gG file diskless\n",gigsize); break;
    }

    switch (tag) {
    case Create:	  cmode = NC_CLOBBER; break;
    case CreateDiskless:  cmode = NC_CLOBBER|NC_DISKLESS|NC_WRITE; break;
    case Open:		  cmode = 0; break;
    case OpenDiskless:	  cmode = NC_DISKLESS; break;
    }

    switch (tag) {
    case Create:
    case CreateDiskless:
        if(nc_create(FILE_NAME, cmode, &ncid)) ERR;
        if(nc_set_fill(ncid, NC_NOFILL, NULL)) ERR;
	break;
    case Open:
    case OpenDiskless:
        if(nc_open(FILE_NAME, cmode, &ncid)) ERR;
	break;
    }

    switch (tag) {
    case Create:
    case CreateDiskless:
        if(nc_def_dim(ncid, "dim", varsize, &dimids[0])) ERR;
        if(nc_def_var(ncid, "var", NC_BYTE, 1, dimids, &varid)) ERR;
        if(nc_enddef(ncid)) ERR;
	break;
    case Open:
    case OpenDiskless:
        if(nc_inq_dimid(ncid, "dim", &dimids[0])) ERR;
        if(nc_inq_varid(ncid, "var", &varid)) ERR;
	break;
    }

    switch (tag) {
    case Create:
    case CreateDiskless:
	/* Fill and put as integers */
	for(i=0;i<pieces;i++) {
	   start[0] = i*CHUNKSIZE;
	   count[0] = CHUNKSIZE;
	   for(j=0;j<DATASIZE;j++) data[j] = (i*CHUNKSIZE)+j;
	   if(nc_put_vara(ncid,varid,start,count,(void*)data)) ERR;
	}
	break;
    case Open:
    case OpenDiskless:
	/* Read the var contents and validate */
	for(i=0;i<pieces;i++) {
	   int status = 0;
	   start[0] = i*CHUNKSIZE;
	   count[0] = CHUNKSIZE;
	   if((status=nc_get_vara(ncid,varid,start,count,(void*)data)))
		ERR;
	   for(j=0;j<DATASIZE;j++) {
		unsigned int expected = (i*CHUNKSIZE)+j;
		if(data[j] != expected) {
		    printf("mismatch: i=%u j=%u data=%u; should be %u\n",
				i,j,data[j],expected);
		    err++;
		}
	    }
	}
	break;
    }

    if(nc_close(ncid)) ERR;

    SUMMARIZE_ERR;
    exit(0);
    return 0;
}
