#!/bin/sh
# this script is executed as part of the build process. Call specified in texstudio.pro
QMAKE_CXX=$1
BUILD_DIR=$2
PRO_DIR=$3
export PATH=$PATH:/usr/local/bin  # standard path for hg installation on OSX. May not be on PATH when called from a GUI application (e.g. QtCreator)
version=$(git describe --tags)
# write new file if we have version information or if the file does not exist at all.
# ensures a file exists and that it is updated if new version information is available.
# We don't overwrite an existing file with missing version information. This is the
# case e.g. when compiling from the tar ball.
if [ -n "$version" ] || [ ! -f git_revision.cpp ]; then
    echo "const char * TEXSTUDIO_GIT_REVISION = \"$version\";" > $PRO_DIR/src/git_revision.cpp
fi
$QMAKE_CXX -c "$PRO_DIR/src/git_revision.cpp" -o "$BUILD_DIR/git_revision.o"
