#!/usr/bin/env sh

# Exit on errors
set -e

cd "${TRAVIS_BUILD_DIR}"

. travis-ci/defs.sh

print_headline "Getting dependencies for building for ${QT} on ${TRAVIS_OS_NAME}"

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
	if [ $QT = "qt5win" ]; then
		MXEDIR="/usr/lib/mxe"
		MXETARGET="x86_64-w64-mingw32.shared"
		
		print_info "Make MXE directory writable"
        echo_and_run "sudo chmod -R a+w ${MXEDIR}"

		echo "MXEDIR=\"${MXEDIR}\"" >> travis-ci/defs.sh
		echo "MXETARGET=\"${MXETARGET}\"" >> travis-ci/defs.sh

		print_info "Exporting CC = ${MXETARGET}-gcc"
		CC="${MXETARGET}-gcc"
		print_info "Exporting CXX = ${MXETARGET}-g++"
		CXX="${MXETARGET}-g++"

		JOBS=$(grep '^processor' /proc/cpuinfo | wc -l)

		cd travis-ci/mxe

		#print_info "Building poppler (using ${JOBS} jobs)"
		#env PATH="${MXEDIR}/usr/bin:${MXEDIR}/usr/${MXETARGET}/qt5/bin:$PATH" PREFIX="${MXEDIR}/usr" TARGET="${MXETARGET}" JOBS="$JOBS" MXE_CONFIGURE_OPTS="--host='${MXETARGET}' --build='`${MXEDIR}/ext/config.guess`' --prefix='${MXEDIR}/usr/${MXETARGET}' --enable-static --disable-shared ac_cv_prog_HAVE_DOXYGEN='false' " TEST_FILE="poppler-test.cxx" make -f build-poppler-mxe.mk
	else
		print_info "Updating apt cache"
		#sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
		#sudo apt-get -qq update
		#sudo apt-get install gdb
		#if [ $QT = "qt5" ] || [ $QT = "qt5Release" ] ; then
			#print_info "Installing packages: QT5"
			#sudo apt-get install qtbase5-dev qt5-default qt5-qmake  libqt5svg5-dev qtscript5-dev qttools5-dev libpoppler-qt5-dev zlib1g-dev pkg-config
		#elif [ $QT = "qt5NoPoppler" ]; then
			#sudo apt-get install qtbase5-dev qt5-default qt5-qmake  libqt5svg5-dev qtscript5-dev qttools5-dev zlib1g-dev pkg-config
		#else
			#print_error "Unsupported Qt version '${QT}'"
			#exit 1
		#fi
	fi
elif [ "${TRAVIS_OS_NAME}" = "osx" ]; then
	print_info "Updating homebrew"
	brew update > brew_update.log || { print_error "Updating homebrew failed"; cat brew_update.log; exit 1; }
else
	print_error "Unsupported host/target combination '${TRAVIS_OS_NAME}'"
	exit 1
fi

cd "${TRAVIS_BUILD_DIR}"

print_info "Successfully set up dependencies"
