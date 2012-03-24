#!/bin/sh

set -e

echo ""
echo "Testing in-memory (diskless) files with and without persistence"

HASNC4=`../nc-config --has-nc4`

echo ""
echo "Test diskless netCDF classic file without persistence"
cmd="tst_diskless";
echo "cmd=$cmd"
$cmd
echo "*** PASS: diskless netCDF classic file without persistence"

if test "x$HASNC4" = "xyes" ; then
echo ""
echo "Test diskless netCDF enhanced file without persistence"
cmd="tst_diskless netcdf4";
echo "cmd=$cmd"
$cmd
echo "*** PASS: diskless netCDF enhanced file without persistence"
fi #HASNC4

echo ""
echo "Test diskless netCDF classic file with persistence"
cmd="tst_diskless persist";
echo "cmd=$cmd"
rm -f diskless.nc
$cmd
if test -e diskless.nc ; then
echo "diskless.nc created"
../ncdump/ncdump diskless.nc
echo "***PASS: diskless netCDF classic file with persistence"
else
echo "diskless.nc not created"
echo "***FAIL: diskless netCDF classic file with persistence"
fi

if test "x$HASNC4" = "xyes" ; then
echo ""
echo "Test diskless netCDF enhanced file with persistence"
cmd="tst_diskless netcdf4 persist";
echo "cmd=$cmd"
rm -f diskless.nc
$cmd
if test -e diskless.nc ; then
echo "diskless.nc created"
../ncdump/ncdump diskless.nc
echo "***PASS: diskless netCDF enhanced file with persistence"
else
echo "diskless.nc not created"
echo "***FAIL: diskless netCDF enhanced file with persistence"
fi

fi #HASNC4
