#!/bin/bash
set -x
./configure --disable-doxygen --disable-shared --enable-dap --enable-netcdf-4 --enable-diskless CFLAGS="-ggdb -O0 -I/c/Users/wfisher/Desktop/hdf5-1.8.8/src -I/c/Users/wfisher/Desktop/hdf5-1.8.8/hl/src -I/c/Users/wfisher/Desktop/curl-7.25.0/include/ -DCURL_STATICLIB" LDFLAGS="-ggdb -O0 -L/c/MinGW/lib/libmsvcrt.a -L/c/MinGW/lib/libmsvcr90.a -L/c/Users/wfisher/Desktop/curl-7.25.0/lib/.libs -L/c/GnuWin32/lib/libz.a -L/c/Users/wfisher/Desktop/hdf5-1.8.8/build_win/bin"

#-L/c/Users/wfisher/Desktop/curl-7.25.0/lib/.libs/libcurl.a"