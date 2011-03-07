## This is a automake file, part of Unidata's netCDF package.
# Copyright 2005, see the COPYRIGHT file for more information.

# This automake file generates the Makefile to build netCDF-4. The
# generated makefile is not run unless the user selected to build
# netCDF-4.

include $(top_srcdir)/lib_flags.am

# Initialize
LDADD =
libnetcdf4_la_CPPFLAGS = ${AM_CPPFLAGS}

# Netcdf-4 source.
NC4SOURCES = nc4internal.h error4.c nc4dispatch.c nc4dispatch.h		\
nc4attr.c nc4dim.c nc4file.c nc4grp.c nc4type.c nc4var.c ncfunc.c	\
nc4internal.c nc4hdf.c

# This is our output. The big enchilada.
noinst_LTLIBRARIES = libnetcdf4.la
libnetcdf4_la_SOURCES = ${NC4SOURCES}
libnetcdf4_la_LIBADD = -lhdf5_hl -lhdf5 -lz

# This turns on declspec magic in netcdf.h for windows DLLs.
if BUILD_DLL
libnetcdf4_la_CPPFLAGS += -DDLL_EXPORT
endif






