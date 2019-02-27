#!/bin/sh

export DYLD_INSERT_LIBRARIES="/Users/pprikazs/Documents/Project/libft_malloc/libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
