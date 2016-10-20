#!/bin/sh
# this script is executed as part of the build process. Call specified in texstudio.pro
QMAKE_CXX=$1
BUILD_DIR=$2
export PATH=$PATH:/usr/local/bin  # standard path for hg installation on OSX. May not be on PATH when called from a GUI application (e.g. QtCreator)
version=$(hg identify -n)
revision=$(hg identify -i)
# write new file if we have version information or if the file does not exist at all.
# ensures a file exists and that it is updated if new version information is available.
# We don't overwrite an existing file with missing version information. This is the
# case e.g. when compiling from the tar ball.
if [ -n "$version" ] || [ ! -f hg_revision.cpp ]; then
    echo "const char * TEXSTUDIO_HG_REVISION = \"$version:$revision\";" > hg_revision.cpp
fi
$QMAKE_CXX -c hg_revision.cpp -o $BUILD_DIR/hg_revision.o
