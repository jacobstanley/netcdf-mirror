#!/bin/sh
set -e

echo "*** TEST: xxxxx"

rm -f /tmp/dump.txt
/bin/df -h >/tmp/dump.txt

echo "*** PASS: x.sh"

exit
