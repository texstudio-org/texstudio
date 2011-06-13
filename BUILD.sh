#!/bin/sh
echo "TeXstudio compilation :"
echo "----------------------------------------"
echo "Enter SYSTEM (1: UNIX ; 2: MACOSX) :"
read SYSTEM
echo "Enter path to QT4 (e.g. /usr/lib/qt4, you can leave it empty):"
read QTDIR
PATH=$QTDIR/bin:$PATH
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$QTDIR/lib:$DYLD_LIBRARY_PATH
export QTDIR PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH
if [ "$SYSTEM" = 1 ] 
then
echo "Enter PREFIX (/usr , /usr/local or /opt) :"
read PREFIX
qmake -unix PREFIX=$PREFIX texmakerx.pro
make
make install
echo "Compilation and installation done"
echo "Icons and desktop file can be found in the $PREFIX/share/texmakerx directory"
# set the -spec option, if necessary. Ex : qmake -unix -spec linux-g++ PREFIX=$PREFIX texmaker.pro
exit 0
fi

if [ "$SYSTEM" = 2 ] 
then
qmake -macx -spec macx-g++ texmakerx.pro
make
make install
echo "Compilation and installation done"
exit 0
fi

exit 0

