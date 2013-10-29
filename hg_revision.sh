#!/bin/sh
version=$(hg identify -n)
echo "const char * TEXSTUDIO_HG_REVISION = \"$version\";" > hg_revision.cpp
$1 -c hg_revision.cpp -o $2/hg_revision.o