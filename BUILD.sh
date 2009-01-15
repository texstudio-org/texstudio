#!/bin/sh
echo "Texmaker compilation :"
echo "----------------------------------------"
echo "Enter path to QT4 (/usr/lib/qt4 or ...):"
read QTDIR
echo "Enter SYSTEM (1: UNIX ; 2: MACOSX) :"
read SYSTEM
PATH=$QTDIR/bin:$PATH
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$QTDIR/lib:$DYLD_LIBRARY_PATH
export QTDIR PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH
if [ "$SYSTEM" = 1 ] 
then
echo "Enter PREFIX (/usr , /usr/local or /opt) :"
read PREFIX
qmake -unix PREFIX=$PREFIX texmaker.pro
make
make install
echo "Compilation and installation done"
echo "Icons and desktop file can be found in the $PREFIX/share/texmaker directory"
# set the -spec option, if necessary. Ex : qmake -unix -spec linux-g++ PREFIX=$PREFIX texmaker.pro
exit 0
fi

if [ "$SYSTEM" = 2 ] 
then
qmake -macx -spec macx-g++ texmaker.pro
make
make install
echo "Compilation and installation done"
exit 0
fi

exit 0

