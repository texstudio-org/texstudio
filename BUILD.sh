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

# Autodetect operating system
if (uname -s | grep Darwin); then SYSTEM=2; else SYSTEM=1; fi

#ask
readvalue "Enter SYSTEM (1: UNIX ; 2: MACOSX)" $SYSTEM;
SYSTEM=$NEWVALUE

#pass parameters to cmake
TXSCOMPILEOPTIONS=$*

if [ "$SYSTEM" = 1 ]; then
	readvalue "Enter PREFIX (/usr , /usr/local or /opt)" /usr/local;
	PREFIX=$NEWVALUE
	TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS -DCMAKE_INSTALL_PREFIX=$PREFIX"
fi

readoption "Do you want to use the video player in pdf files (requires the qtmulitmedia library)?" no;
OPTION_MEDIAPLAYER=$NEWVALUE


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

if [ "$SYSTEM" = 1 ]; then
	readoption "Do you want to install TexStudio after building it?" yes;
	DO_INSTALL=$NEWVALUE
else
	DO_INSTALL=no
fi

#compile

if [ "$OPTION_MEDIAPLAYER" = yes ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS -DTEXSTUDIO_ENABLE_MEDIAPLAYER=on"; fi
if [ "$OPTION_TESTS" = no ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS -DTEXSTUDIO_ENABLE_TESTS=on"; fi
if [ "$OPTION_DEBUG_BUILD" = yes ]; then
	TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS -DCMAKE_BUILD_TYPE=Debug"
fi
if [ "$OPTION_DEBUG_LOGGER" = yes ]; then TXSCOMPILEOPTIONS="$TXSCOMPILEOPTIONS -DTEXSTUDIO_ENABLE_DEBUG_LOGGER=on"; fi

echo "Starting compilation"
if (test -d "./build") then echo "remove previous build folder";rm -rf ./build; fi
mkdir build
cmake -Wno-dev PREFIX=$PREFIX $TXSCOMPILEOPTIONS . -B ./build
cmake --build ./build --parallel
echo "Compilation done"
if [ "$DO_INSTALL" = yes ]; then
	cmake --build ./build -t install
	echo "Installation done"
	echo "Icons and desktop file can be found in the $PREFIX/share/texstudio directory"
fi
# set the -spec option, if necessary. Ex : qmake -spec linux-g++ PREFIX=$PREFIX texstudio.pro
exit 0

