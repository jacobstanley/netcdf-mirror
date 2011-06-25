## This is a automake file, part of Unidata's netCDF package.
# Copyright 2010, see the COPYRIGHT file for more information.

# This builds the netcdf-4 version of the opendap client.

# $Id: Makefile.am,v 1.18 2010/05/29 18:45:47 dmh Exp $

# Put together AM_CPPFLAGS and AM_LDFLAGS.
include $(top_srcdir)/lib_flags.am

DISTCLEANFILES =
CLEANFILES =
EXTRA_DIST =
LDADD=

ASTJAR=ast.jar

# RPC Sources
SRC=

HDRS=

if BUILD_RPC

noinst_LTLIBRARIES = librpcclient.la librcpserver.la

# Build convenience library
librpcclient_la_SOURCES = $(SRC) $(HDRS)
librpcserver_la_SOURCES = $(SRC) $(HDRS)

AM_CPPFLAGS += -I$(top_srcdir)/libsrc4 \
	      -I$(top_srcdir)/libsrc \
	      -I$(top_srcdir)/libdispatch

AM_CPPFLAGS += -I${top_srcdir}/libdispatch

# Define the load libraries 
LDADD += \
         ${top_builddir}/libcdmr/libnccr.la \
         ${top_builddir}/libcdmr/libdap2.la \
	 ${top_builddir}/libsrc4/libnetcdf4.la \
         ${top_builddir}/libsrc/libnetcdf3.la \
         ${top_builddir}/libdispatch/libdispatch.la

if BUILD_V2
LDADD += ${top_builddir}/libdispatch/libnetcdf2.la 
endif # BUILD_V2

##################################################
# Generate the augmented ncstream structures
#
#EXTRA_DIST += ast.jar ncStream.proto ncStream.h ncStream.c extends.sed
#
#ncStreamx.c ncStreamx.h: ncStreamx.proto ast.jar
#	java -jar ast.jar -WdT -I. ncStreamx.proto
#
#ncStreamx.proto: ncStream.proto extends.sed
#	sed -f extends.sed <ncStream.proto |tr -d '\r' >ncStreamx.proto
#
##################################################

endif # BUILD_RPC

