#!/bin/sh
# this script is executed as part of the build process. Call specified in texstudio.pro
QMAKE_CXX=$1
BUILD_DIR=$2
PRO_DIR=$3
export PATH=$PATH:/usr/local/bin  # standard path for hg installation on OSX. May not be on PATH when called from a GUI application (e.g. QtCreator)
version=$(git describe --tags --always)
# write new file if we have version information or if the file does not exist at all.
# ensures a file exists and that it is updated if new version information is available.
# We don't overwrite an existing file with missing version information. This is the
# case e.g. when compiling from the tar ball.
if [ -n "$version" ]; then
    echo "create git_revision.cpp"
    echo "const char * TEXSTUDIO_GIT_REVISION = \"$version\";" > git_revision.cpp
else
    echo "empty git revision"
    echo "const char * TEXSTUDIO_GIT_REVISION = \"N/A\";" > git_revision.cpp
fi
