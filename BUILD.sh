#!/bin/sh
echo "TeXstudio compilation :"
echo "----------------------------------------"

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

check_qt_pathname() {
	if [ ! -x "$1" ]; then
		return 1
	fi
	QMAKE="$(basename -- "$1")"
	QTDIR="$(dirname -- "$1")"
	QTDIR="$(dirname -- "$QTDIR")"
	return 0
}

# Autodetect operating system
if (uname -s | grep Darwin); then SYSTEM=2; else SYSTEM=1; fi

# Autodetect QTDIR and QTDIR using a fixed list of locations
for PATHNAME in                                 	\
	/bin/qmake					\
	/usr/bin/qmake					\
	/usr/bin/qmake-qt5				\
	/usr/local/bin/qmake				\
	/usr/lib/qt5/bin/qmake				\
	/usr/lib/qt4/bin/qmake				\
	/usr/local/Trolltech/Qt-4.7.2/bin/qmake		\
	/usr/local/Trolltech/Qt-4.7.3/bin/qmake		\
	/usr/local/Trolltech/Qt-4.8.0/bin/qmake;	\
do
	if check_qt_pathname "$PATHNAME"; then
		break
	fi
done

# If autodtection of QTDIR and QTDIR failed, then assume default values
if [ "$QMAKE" = "" ]; then
	QTDIR=""
	QMAKE="qmake"
fi

#ask
readvalue "Enter SYSTEM (1: UNIX ; 2: MACOSX)" $SYSTEM;
SYSTEM=$NEWVALUE

if [ "$SYSTEM" = 1 ]; then
	readvalue "Enter PREFIX (/usr , /usr/local or /opt)" /usr/local;
	PREFIX=$NEWVALUE
fi
readvalue "Enter path to QT4/5 base directory (e.g. /usr/lib/qt4, you can leave it empty if qmake is in PATH)" $QTDIR;
QTDIR=$NEWVALUE
readvalue "Enter path to QT4/5 executable file (e.g. qmake or qmake-qt5)" $QMAKE;
QMAKE=$NEWVALUE

readoption "Do you want to use the internal pdf viewer (requires the Poppler library)?" yes;
OPTION_PDFVIEWER=$NEWVALUE
if [ "$OPTION_PDFVIEWER" = yes ]; then
	readoption "Do you want to use the video player in pdf files (requires the Phonon library)?" no;
	OPTION_PHONON=$NEWVALUE
else
	OPTION_PHONON=no
fi

if [ "$SYSTEM" = 1 ]; then
	readoption "Do you want an internal terminal widget (requires the qtermwidget5 library)?" yes;
	OPTION_INTERNAL_TERMINAL=$NEWVALUE
fi

readswitchy "Do you want to build a debug or release version?" "debug release d r deb rel" debug;
case "$NEWVALUE" in
	d|deb|debug) OPTION_DEBUG_BUILD=yes;;
	r|rel|release) OPTION_DEBUG_BUILD=no;;
esac
if [ "$OPTION_DEBUG_BUILD" = yes ]; then
	readoption "Do you want to include tests in the debug build?" yes
	OPTION_TESTS=$NEWVALUE
else
	OPTION_TESTS=yes
fi
readoption "Do you want to enable the debug logger?" no
OPTION_DEBUG_LOGGER=$NEWVALUE

readoption "Do you want to install TexStudio after building it?" yes;
DO_INSTALL=$NEWVALUE

if [ ! -x "$QTDIR/bin/$QMAKE" ]; then
	echo "Warning, QT path may be invalid"
fi

#compile
#pass parameters to qmake
TXSCOMPILEOPTIONS=$*
if [ "$OPTION_PDFVIEWER" = no ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS NO_POPPLER_PREVIEW=true"; fi
if [ "$OPTION_INTERNAL_TERMINAL" = yes ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS INTERNAL_TERMINAL=true"; fi
if [ "$OPTION_PHONON" = yes ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS PHONON=true"; fi
if [ "$OPTION_TESTS" = no ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS NO_TESTS=true"; fi
if [ "$OPTION_DEBUG_BUILD" = yes ]; then
	TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS CONFIG+=debug CONFIG-=debug_and_release CONFIG-=release"
else
	TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS CONFIG-=debug CONFIG-=debug_and_release CONFIG+=release"
fi
if [ "$OPTION_DEBUG_LOGGER" = yes ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS DEBUG_LOGGER=true"; fi

PATH=$QTDIR/bin:$PATH
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$QTDIR/lib:$DYLD_LIBRARY_PATH
export QTDIR PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH

if [ "$SYSTEM" = 1 ]; then
	echo "Starting compilation"
	$QMAKE PREFIX=$PREFIX $TXSCOMPILEOPTIONS texstudio.pro
	make -j 4
	echo "Compilation done"
	if [ "$DO_INSTALL" = yes ]; then
		make install
		echo "Installation done"
		echo "Icons and desktop file can be found in the $PREFIX/share/texstudio directory"
	fi
	# set the -spec option, if necessary. Ex : qmake -spec linux-g++ PREFIX=$PREFIX texstudio.pro
	exit 0
fi

if [ "$SYSTEM" = 2 ]; then
	echo "Starting compilation"
	$QMAKE -spec macx-clang $TXSCOMPILEOPTIONS texstudio.pro
	make
	echo "Compilation done"
	if [ "$DO_INSTALL" = yes ]; then
		make install
		echo "Installation done"
	fi
	exit 0
fi

exit 0
