/*********************************************************************
 *   Copyright 2010, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Id$
 *   $Header$
 *********************************************************************/

#ifndef CRUTIL_H
#define CRUTIL_H

extern int crstrindex(char* s, char* match);

extern int nccr_createtempfile(char* tmppath, char** tmpnamep);
extern void nccr_unlinktempfile(int fd, char* tmpname);

#endif /*CRUTIL_H*/
