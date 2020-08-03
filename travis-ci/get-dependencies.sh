#!/usr/bin/env sh

# Exit on errors
set -e

cd "${TRAVIS_BUILD_DIR}"

. travis-ci/defs.sh

print_headline "Getting dependencies for building for ${QT} on ${TRAVIS_OS_NAME}"

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
	if [ $QT = "qt5win" ]; then
		MXEDIR="/opt/mxe"
		MXETARGET="i686-w64-mingw32.static"

		echo "MXEDIR=\"${MXEDIR}\"" >> travis-ci/defs.sh
		echo "MXETARGET=\"${MXETARGET}\"" >> travis-ci/defs.sh

		print_info "Exporting CC = ${MXETARGET}-gcc"
		CC="${MXETARGET}-gcc"
		print_info "Exporting CXX = ${MXETARGET}-g++"
		CXX="${MXETARGET}-g++"

		JOBS=$(grep '^processor' /proc/cpuinfo | wc -l)

		print_info "Fetching MXE from docker"
		#echo_and_run "docker create --name mxe stloeffler/mxe-tw"
		echo_and_run "docker create --name mxe jsundermeyer/txs_support:v01"
		echo_and_run "docker cp mxe:${MXEDIR} ${MXEDIR}"

		cd travis-ci/mxe

		print_info "Building poppler (using ${JOBS} jobs)"
		env PATH="${MXEDIR}/usr/bin:${MXEDIR}/usr/${MXETARGET}/qt5/bin:$PATH" PREFIX="${MXEDIR}/usr" TARGET="${MXETARGET}" JOBS="$JOBS" MXE_CONFIGURE_OPTS="--host='${MXETARGET}' --build='`${MXEDIR}/ext/config.guess`' --prefix='${MXEDIR}/usr/${MXETARGET}' --enable-static --disable-shared ac_cv_prog_HAVE_DOXYGEN='false' " TEST_FILE="poppler-test.cxx" make -f build-poppler-mxe.mk
	else
		print_info "Updating apt cache"
		sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
		sudo apt-get -qq update
		sudo apt-get install gdb
		if [ $QT = "qt5" ] || [ $QT = "qt5Release" ] ; then
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
#	print_info "Updating homebrew"
#	brew update > brew_update.log || { print_error "Updating homebrew failed"; cat brew_update.log; exit 1; }
# apparently brew comes now with preinstalled qt & poppler
#	print_info "Brewing packages: qt5 poppler"
#	brew install qt5
#	brew uninstall poppler
#	brew unlink python@2
    brew uninstall --ignore-dependencies poppler
	brew install -v "${TRAVIS_BUILD_DIR}/travis-ci/mac/poppler.rb"
	print_info "poppler compiled"
else
	print_error "Unsupported host/target combination '${TRAVIS_OS_NAME}'"
	exit 1
fi

cd "${TRAVIS_BUILD_DIR}"

print_info "Successfully set up dependencies"
