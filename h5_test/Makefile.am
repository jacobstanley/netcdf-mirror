# This is part of the netCDF package.
# Copyright 2011 University Corporation for Atmospheric Research/Unidata
# See COPYRIGHT file for conditions of use.
# 
# This entire directory will be skipped, unless the configure script
# is run with --enable-netcdf-4. This directory contains tests that
# only use HDF5; these tests don't use netCDF at all.
#
# If one of these tests fails, then netCDF-4 will not work correctly.
#

include $(top_srcdir)/lib_flags.am

# tst_h_strings3 core dumps! Ed 11/10/10
H5TESTS = tst_h_files tst_h_files2 tst_h_files4 tst_h_atts		\
tst_h_atts3 tst_h_atts4 tst_h_vars tst_h_vars2 tst_h_vars3 tst_h_grps	\
tst_h_compounds tst_h_compounds2 tst_h_wrt_cmp tst_h_rd_cmp tst_h_vl	\
tst_h_opaques tst_h_strings tst_h_strings1 tst_h_strings2 tst_h_ints	\
tst_h_dimscales tst_h_dimscales1 tst_h_dimscales2 tst_h_dimscales3	\
tst_h_enums

check_PROGRAMS = $(H5TESTS)
TESTS = $(H5TESTS)

# The parallel program is run from a script.
if TEST_PARALLEL
check_PROGRAMS += tst_h_par
endif

# This script will run all the parallel test programs.
if TEST_PARALLEL
TESTS += run_par_tests.sh
endif

# This will run a bunch of the test programs with valgrind, the memory
# checking tool. (Valgrind must be present for this to work.)
if USE_VALGRIND_TESTS
TESTS += run_valgrind_tests.sh 
endif # USE_VALGRIND_TESTS

CLEANFILES = tst_h_*.h5 

EXTRA_DIST = run_par_test.sh run_valgrind_tests.sh

LDADD = -lhdf5_hl -lhdf5 -lz -lm

EXTRA_DIST += ref_tst_h_compounds.h5 ref_tst_h_compounds2.h5	\
run_par_tests.sh run_valgrind_tests.sh ref_tst_compounds.nc




