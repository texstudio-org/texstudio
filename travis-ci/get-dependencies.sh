#!/usr/bin/env sh

# Exit on errors
set -e

cd "${TRAVIS_BUILD_DIR}"

. travis-ci/defs.sh

print_headline "Getting dependencies for building for ${QT} on ${TRAVIS_OS_NAME}"

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
	if [ $QT = "qt5win" ]; then
		MXEDIR="/usr/lib/mxe"
		MXETARGET="i686-w64-mingw32.static"

		echo "MXEDIR=\"${MXEDIR}\"" >> travis-ci/defs.sh
		echo "MXETARGET=\"${MXETARGET}\"" >> travis-ci/defs.sh

		print_info "Exporting CC = ${MXETARGET}-gcc"
		CC="${MXETARGET}-gcc"
		print_info "Exporting CXX = ${MXETARGET}-g++"
		CXX="${MXETARGET}-g++"

		JOBS=$(grep '^processor' /proc/cpuinfo | wc -l)

		print_info "Adding pkg.mxe.cc apt repo"
		echo "deb http://pkg.mxe.cc/repos/apt/debian wheezy main" | sudo tee /etc/apt/sources.list.d/mxeapt.list > /dev/null
		sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D43A795B73B16ABE9643FE1AFD8FFF16DB45C6AB
		print_info "Updating apt cache"
		echo_and_run "sudo apt-get -qq update"

		print_info "Installing packages: curl freetype gcc jpeg lcms libpng lua pkg-config qtbase qtscript qttools tiff"
		sudo apt-get install -y mxe-i686-w64-mingw32.static-curl mxe-i686-w64-mingw32.static-freetype mxe-i686-w64-mingw32.static-gcc mxe-i686-w64-mingw32.static-jpeg mxe-i686-w64-mingw32.static-lcms mxe-i686-w64-mingw32.static-libpng mxe-i686-w64-mingw32.static-lua mxe-i686-w64-mingw32.static-pkgconf mxe-i686-w64-mingw32.static-qtbase mxe-i686-w64-mingw32.static-qtscript mxe-i686-w64-mingw32.static-qttools mxe-i686-w64-mingw32.static-tiff mxe-i686-w64-mingw32.static-nsis

		print_info "Make MXE writable"
		sudo chmod -R a+w "${MXEDIR}"

		print_info "Fixing libharfbuzz.la"
		echo_and_run "sed -ie 's#libfreetype.la#libfreetype.la -lharfbuzz_too#g' \"${MXEDIR}/usr/i686-w64-mingw32.static/lib/libharfbuzz.la\""

		cd travis-ci/mxe

		print_info "Building poppler (using ${JOBS} jobs)"
		env PATH="${MXEDIR}/usr/bin:${MXEDIR}/usr/${MXETARGET}/qt5/bin:$PATH" PREFIX="${MXEDIR}/usr" TARGET="${MXETARGET}" JOBS="$JOBS" MXE_CONFIGURE_OPTS="--host='${MXETARGET}' --build='`${MXEDIR}/ext/config.guess`' --prefix='${MXEDIR}/usr/${MXETARGET}' --enable-static --disable-shared ac_cv_prog_HAVE_DOXYGEN='false' --disable-doxygen --enable-poppler-qt5 --disable-poppler-qt4" TEST_FILE="poppler-test.cxx" make -f build-poppler-mxe.mk
	else
		print_info "Updating apt cache"
		sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
		sudo apt-get -qq update
		sudo apt-get install gdb
		if [ $QT = "qt4" ]; then
			print_info "Installing packages: QT4"
			sudo apt-get install qt4-qmake  libpoppler-qt4-dev zlib1g-dev pkg-config libx11-dev
		elif [ $QT = "qt5" ] || [ $QT = "qt5Release" ] ; then
			print_info "Installing packages: QT5"
			sudo apt-get install qtbase5-dev qt5-default qt5-qmake  libqt5svg5-dev qtscript5-dev qttools5-dev libpoppler-qt5-dev zlib1g-dev pkg-config
		elif [ $QT = "qt5NoPoppler" ]; then
			sudo apt-get install qtbase5-dev qt5-default qt5-qmake  libqt5svg5-dev qtscript5-dev qttools5-dev zlib1g-dev pkg-config
		else
			print_error "Unsupported Qt version '${QT}'"
			exit 1
		fi
	fi
elif [ "${TRAVIS_OS_NAME}" = "osx" ]; then
	print_info "Updating homebrew"
	brew update > brew_update.log || { print_error "Updating homebrew failed"; cat brew_update.log; exit 1; }
	print_info "Brewing packages: qt5 poppler"
	brew install qt5
	brew install "${TRAVIS_BUILD_DIR}/travis-ci/mac/poppler.rb" --with-qt --enable-xpdf-headers
else
	print_error "Unsupported host/target combination '${TRAVIS_OS_NAME}'"
	exit 1
fi

cd "${TRAVIS_BUILD_DIR}"

print_info "Successfully set up dependencies"
