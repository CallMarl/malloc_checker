#!/bin/sh

root=`pwd`

make -j -C $root
$root/lib_srcs.sh $root/malloc_checker
