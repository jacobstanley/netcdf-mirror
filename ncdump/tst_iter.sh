#!/bin/sh
# This shell script runs an ncdump bug test for netcdf
# Test if the nciter code is working.

set -e
echo ""
echo "*** Running ncdump nc_iter test."

echo "*** create tst_iter.nc "
../ncgen/ncgen -k1 -B2 -o tst_iter.nc $srcdir/ref_tst_iter.cdl
echo "*** dumping tst_iter.nc to tst_iter.cdl..."
./ncdump tst_iter.nc > tst_iter.cdl
echo "*** comparing tst_iter.cdl with ref_tst_iter.cdl..."
diff tst_iter.cdl $srcdir/ref_tst_iter.cdl

echo
echo "*** All ncdump iter tests passed"
exit 0
