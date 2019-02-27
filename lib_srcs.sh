#!/bin/sh

export DYLD_INSERT_LIBRARIES="/Absolut/path/to/.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
