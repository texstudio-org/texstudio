#!/bin/sh
export PATH=$PATH:/usr/local/bin  # standard path for hg installation on OSX. May not be on PATH when called from a GUI application (e.g. QtCreator)
version=$(hg identify -n)
revision=$(hg identify -i)
echo "const char * TEXSTUDIO_HG_REVISION = \"$version:$revision\";" > hg_revision.cpp
$1 -c hg_revision.cpp -o $2/hg_revision.o
