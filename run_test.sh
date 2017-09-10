#!/bin/bash
set verbose -o
cmake -GNinja -DTARGET_GROUP=test .
ninja -v
ctest --verbose
git clean -d -f -X &> /dev/null
