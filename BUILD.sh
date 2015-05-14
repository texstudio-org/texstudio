#!/bin/sh
echo "TeXstudio compilation :"
echo "----------------------------------------"

#autodetection
if (uname -s | grep Darwin); then SYSTEM=2; else SYSTEM=1; fi
if [ -f /bin/qmake ]; then QTDIR=; 
elif [ -f /usr/bin/qmake ]; then QTDIR=/usr; 
elif [ -f /usr/local/bin/qmake ]; then QTDIR=/usr/local; 
elif [ -f /usr/lib/qt4/bin/qmake ]; then QTDIR=/usr/lib/qt4
elif [ -f /usr/local/Trolltech/Qt-4.7.2/bin/qmake ]; then QTDIR=/usr/local/Trolltech/Qt-4.7.2 
elif [ -f /usr/local/Trolltech/Qt-4.7.3/bin/qmake ]; then QTDIR=/usr/local/Trolltech/Qt-4.7.3
elif [ -f /usr/local/Trolltech/Qt-4.8.0/bin/qmake ]; then QTDIR=/usr/local/Trolltech/Qt-4.8.0
fi

#helper functions
readvalue() {
  echo -n $1
  echo " (default is $2) :"
  read NEWVALUE
  if [ ! -n "$NEWVALUE" ]; then NEWVALUE=$2;  fi
}

readswitchy() {
  readvalue "$1" $3;
  OK=0
  for option in $2; do
    if [ "$NEWVALUE" = "$option" ]; then OK=1; fi
  done
  if [ "$OK" = 0 ]; then 
  echo "invalid input, must be a value in \"$2\""
  readswitchy "$1" "$2" "$3"
  fi
}

readoption() {
readswitchy "$1 (yes/no)" "yes no" $2;
}

#ask
readvalue "Enter SYSTEM (1: UNIX ; 2: MACOSX)" $SYSTEM;
SYSTEM=$NEWVALUE

if [ "$SYSTEM" = 1 ]; then
  readvalue "Enter PREFIX (/usr , /usr/local or /opt)" /usr/local;
  PREFIX=$NEWVALUE
fi
readvalue "Enter path to QT4 (e.g. /usr/lib/qt4, you can leave it empty if qmake is in PATH)" $QTDIR;
QTDIR=$NEWVALUE
readoption "Do you want to use the internal pdf viewer (requires the Poppler library)?" yes;
OPTION_PDFVIEWER=$NEWVALUE
if [ "$OPTION_PDFVIEWER" = yes ]; then
readoption "Do you want to use the video player in pdf files (requires the Phonon library)?" no;
OPTION_PHONON=$NEWVALUE
else
OPTION_PHONON=no
fi
readswitchy "Do you want to build a debug or release version?" "debug release d r deb rel" debug; 
OPTION_DEBUG=$NEWVALUE
case "$OPTION_DEBUG" in
  d|deb|debug) readoption "Do you want to include tests in the debug build?" yes; OPTION_TESTS=$NEWVALUE;;
  *) OPTION_TESTS=yes;;
esac

if [ ! -f $QTDIR/bin/qmake ]; then 
echo "Warning, QT path may be invalid"
fi

QMAKE=qmake
if readlink -f /usr/bin/qmake  | grep qt3 ; then 
echo Warning: qmake looks like qt3 qmake, TeXstudio requires qt4
if [ -f $QTDIR/bin/qmake-qt4 ]; then 
echo qmake-qt4 exists, using it instead of qmake
QMAKE=qmake-qt4
fi
fi



#compile
#pass parameters to qmake
TXSCOMPILEOPTIONS=$@
if [ "$OPTION_PDFVIEWER" = no ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS NO_POPPLER_PREVIEW=true"; fi
if [ "$OPTION_PHONON" = yes ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS PHONON=true"; fi
if [ "$OPTION_TESTS" = no ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS NO_TESTS=true"; fi
case "$OPTION_DEBUG" in r|rel|release) TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS  CONFIG-=debug CONFIG-=debug_and_release CONFIG+=release";; esac


PATH=$QTDIR/bin:$PATH
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$QTDIR/lib:$DYLD_LIBRARY_PATH
export QTDIR PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH

if [ "$SYSTEM" = 1 ] 
then
  echo "Starting compilation"
  $QMAKE -unix PREFIX=$PREFIX $TXSCOMPILEOPTIONS texstudio.pro
  make
  echo "Compilation done"
  make install
  echo "Compilation and installation done"
  echo "Icons and desktop file can be found in the $PREFIX/share/texstudio directory"
  # set the -spec option, if necessary. Ex : qmake -unix -spec linux-g++ PREFIX=$PREFIX texstudio.pro
  exit 0
fi

if [ "$SYSTEM" = 2 ] 
then
  echo "Starting compilation"
  $QMAKE -macx -spec macx-g++ $TXSCOMPILEOPTIONS texstudio.pro
  make
  make install
  echo "Compilation and installation done"
  exit 0
fi

exit 0
