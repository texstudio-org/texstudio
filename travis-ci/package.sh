#!/usr/bin/env sh

# Exit on errors
set -e

cd "${TRAVIS_BUILD_DIR}"

. travis-ci/defs.sh

if [ "${TRAVIS_PULL_REQUEST}" != "false" ]; then
	print_warning "Not packaging pull-requests for deployment"
	exit 0
fi

print_headline "Packaging ${QT} for deployment"

POPPLERDATA_VERSION="0.4.8"
POPPLERDATA_SUBDIR="poppler-data-${POPPLERDATA_VERSION}"
POPPLERDATA_FILE="poppler-data-${POPPLERDATA_VERSION}.tar.gz"
POPPLERDATA_URL="https://poppler.freedesktop.org/${POPPLERDATA_FILE}"
POPPLERDATA_SHA256="1096a18161f263cccdc6d8a2eb5548c41ff8fcf9a3609243f1b6296abdf72872"

# Gather information

. travis-ci/get-version.sh


if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
	print_info "Running macdeployqt"
	/usr/local/opt/qt/bin/macdeployqt texstudio.app -dmg	

	echo_and_run "sha256sum ${TRAVIS_BUILD_DIR}/texstudio.dmg "
	
	print_info "Renaming .dmg"
	cp "${TRAVIS_BUILD_DIR}/texstudio.dmg" "${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_TAG}-${TRAVIS_OS_NAME}.dmg"
	mv "${TRAVIS_BUILD_DIR}/texstudio.dmg" "${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_OS_NAME}-${VERSION_NAME}.dmg"

	print_info "Preparing bintray.json"
	cat > "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json" <<EOF
	{
		"package": {
			"name": "texstudio-osx",
			"repo": "texstudio",
			"subject": "sunderme"
		},

		"version": {
			"name": "${VERSION_NAME}",
			"released": "${RELEASE_DATE}",
			"gpgSign": false
		},
		"files":
		[
			{"includePattern": "${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_OS_NAME}-${VERSION_NAME}.dmg", "uploadPattern": "texstudio-${TRAVIS_OS_NAME}-${VERSION_NAME}.dmg"}
		],
		"publish": true
	}
EOF

cat "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json"
fi


if [ "${QT}" = "qt5Release" ]; then
	print_info "Running linuxdeployqt"

	make INSTALL_ROOT=appdir -j$(nproc) install ; find appdir/
	wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
	chmod a+x linuxdeployqt-continuous-x86_64.AppImage
	unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
	export VERSION=${TRAVIS_OS_NAME}-${VERSION_NAME}
	./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -extra-plugins=iconengines/libqsvgicon.so
	./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage
	echo_and_run "sha256sum appdir/usr/bin/texstudio "
	echo_and_run "sha256sum ${TRAVIS_BUILD_DIR}/TeXstudio-${VERSION}-x86_64.AppImage "
	cp "${TRAVIS_BUILD_DIR}/TeXstudio-${VERSION}-x86_64.AppImage" "texstudio-${VERSION}-x86_64.AppImage"
	cp "${TRAVIS_BUILD_DIR}/TeXstudio-${VERSION}-x86_64.AppImage" "texstudio-${TRAVIS_TAG}-x86_64.AppImage"


	print_info "Preparing bintray.json"
	cat > "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json" <<EOF
	{
		"package": {
			"name": "texstudio-linux",
			"repo": "texstudio",
			"subject": "sunderme"
		},

		"version": {
			"name": "${VERSION_NAME}",
			"released": "${RELEASE_DATE}",
			"gpgSign": false
		},
		"files":
		[
			{"includePattern": "${TRAVIS_BUILD_DIR}/texstudio-${VERSION}-x86_64.AppImage", "uploadPattern": "texstudio-${VERSION}-x86_64.AppImage"}
		],
		"publish": true
	}
EOF

cat "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json"
fi

if [ "${QT}" = "qt5win" ]; then
	print_info "package build into zip for win"
	print_info "copy dlls and qt5 plugins"
	/usr/lib/mxe/usr/bin/x86_64-w64-mingw32.shared-peldd texstudio.exe -a -w d3d11.dll -w dxgi.dll|grep dll|xargs cp -t "${TRAVIS_BUILD_DIR}"
	echo_and_run "cp -r /usr/lib/mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/platforms \"${TRAVIS_BUILD_DIR}/\""
	echo_and_run "cp -r /usr/lib/mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/imageformats/ \"${TRAVIS_BUILD_DIR}/\""
	print_info "make installer"
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/utilities/texstudio.nsi\" \"${TRAVIS_BUILD_DIR}/\""
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/utilities/FileAssociation.nsh\" \"${TRAVIS_BUILD_DIR}/\""
	echo_and_run "${MXEDIR}/usr/bin/x86_64-w64-mingw32.static-makensis texstudio.nsi"
	print_info "Assembling package"
	echo_and_run "mkdir -p \"package-zip/share\""
	echo_and_run "mkdir -p \"package-zip/config\""
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/texstudio.exe\" \"package-zip/\""
	cp "${TRAVIS_BUILD_DIR}/*.dll" package-zip
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/platforms\" \"package-zip/\""
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/imageformats\" \"package-zip/\""
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/translation\" \"package-zip/translations\""
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/templates\" \"package-zip\""
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/utilities/manual\" \"package-zip/help\""
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/utilities/latex2e.css\" \"package-zip/help\""
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/utilities/latex2e.html\" \"package-zip/help\""
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/utilities/dictionaries\" \"package-zip/dictionaries\""
	echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/utilities/TexTablet\" \"package-zip/TexTablet\""
    echo_and_run "cp -r \"${TRAVIS_BUILD_DIR}/travis-ci/mxe/fonts\" \"package-zip/share/\""

	
	print_info "Fetching poppler data"
	wget --no-check-certificate "${POPPLERDATA_URL}"
	CHKSUM=$(openssl dgst -sha256 "${POPPLERDATA_FILE}" 2> /dev/null)
	if [ "${CHKSUM}" != "SHA256(${POPPLERDATA_FILE})= ${POPPLERDATA_SHA256}" ]; then
		print_error "Wrong checksum"
		print_error "${CHKSUM}"
		print_error "(expected: ${POPPLERDATA_SHA256})"
		exit 1
	fi
	echo_and_run "tar -x -C \"package-zip/share/\" -f \"${TRAVIS_BUILD_DIR}/${POPPLERDATA_FILE}\" && mv \"package-zip/share/${POPPLERDATA_SUBDIR}\" \"package-zip/share/poppler\""

	print_info "zipping '${TRAVIS_BUILD_DIR}/texstudio-${TARGET_OS}-${VERSION_NAME}.zip'"
	
	echo_and_run "cd package-zip && zip -r \"${TRAVIS_BUILD_DIR}/texstudio-win-${VERSION_NAME}.zip\" *"
	echo_and_run "sha256sum \"${TRAVIS_BUILD_DIR}/texstudio_installer.exe\" "
	echo_and_run "sha256sum \"${TRAVIS_BUILD_DIR}/texstudio.exe\" "
	echo_and_run "sha256sum \"${TRAVIS_BUILD_DIR}/texstudio-win-${VERSION_NAME}.zip\" "
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/texstudio-win-${VERSION_NAME}.zip\" \"${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_TAG}-win-portable-qt5.zip\" "
	echo_and_run "cp \"${TRAVIS_BUILD_DIR}/texstudio_installer.exe\" \"${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_TAG}-win-qt5.exe\" "

	print_info "Preparing bintray.json"
	cat > "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json" <<EOF
	{
		"package": {
			"name": "texstudio-win",
			"repo": "texstudio",
			"subject": "sunderme"
		},

		"version": {
			"name": "${VERSION_NAME}",
			"released": "${RELEASE_DATE}",
			"gpgSign": false
		},
		"files":
		[
			{"includePattern": "${TRAVIS_BUILD_DIR}/texstudio-win-${VERSION_NAME}.zip", "uploadPattern": "texstudio-win-${VERSION_NAME}.zip"},
			{"includePattern": "${TRAVIS_BUILD_DIR}/texstudio_installer.exe", "uploadPattern": "texstudio-win-${VERSION_NAME}.exe"}
		],
		"publish": true
	}
EOF

cat "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json"

fi

cd "${TRAVIS_BUILD_DIR}"

print_info "Deployment preparation successful"
