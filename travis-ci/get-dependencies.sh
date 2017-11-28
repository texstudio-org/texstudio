#!/usr/bin/env sh

# Exit on errors
set -e

cd "${TRAVIS_BUILD_DIR}"

. travis-ci/defs.sh

print_headline "Getting dependencies for building for ${QT} on ${TRAVIS_OS_NAME}"

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
	print_info "Updating apt cache"
	sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
	sudo apt-get -qq update
	sudo apt-get install gdb
	if [ $QT = "qt4" ]; then
		print_info "Installing packages: QT4"
		sudo apt-get install qt4-qmake  libpoppler-qt4-dev zlib1g-dev pkg-config libx11-dev
	elif [ $QT = "qt5" ]; then
		print_info "Installing packages: QT5"
		sudo apt-get install qtbase5-dev qt5-default qt5-qmake  libqt5svg5-dev qtscript5-dev qttools5-dev libpoppler-qt5-dev zlib1g-dev pkg-config
	elif [ $QT = "qt5NoPoppler" ]; then
		sudo apt-get install qtbase5-dev qt5-default qt5-qmake  libqt5svg5-dev qtscript5-dev qttools5-dev zlib1g-dev pkg-config
	else
		print_error "Unsupported Qt version '${QT}'"
		exit 1
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
