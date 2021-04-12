#!/usr/bin/env sh

# Exit on errors
set -e

. .github/scripts/get-version.sh
 
echo "package build into zip for win"

echo "copy dlls and qt5 plugins"
/usr/lib/mxe/usr/bin/x86_64-w64-mingw32.shared-peldd texstudio.exe -a -w d3d11.dll -w dxgi.dll|grep dll|xargs cp -t .
pwd
cp -r /usr/lib/mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/platforms .
cp -r /usr/lib/mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/styles .
cp -r /usr/lib/mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/imageformats/ .
echo "make installer"
cp ./utilities/texstudio.nsi .
cp ./utilities/FileAssociation.nsh .
/usr/lib/mxe/usr/bin/x86_64-w64-mingw32.static-makensis texstudio.nsi
echo "Assembling package"
mkdir -p "package-zip/share"
mkdir -p "package-zip/config"
cp texstudio.exe package-zip/
cp *.dll package-zip
cp -r platforms package-zip/
cp -r ./imageformats package-zip/
cp -r ./styles package-zip/
cp -r ./translation package-zip/translations
cp -r ./templates package-zip
cp -r ./utilities/manual package-zip/help
cp ./utilities/latex2e.css package-zip/help
cp ./utilities/latex2e.html package-zip/help
cp -r ./utilities/dictionaries package-zip/dictionaries
cp -r ./utilities/TexTablet package-zip/TexTablet
cp -r ./travis-ci/mxe/fonts package-zip/share/

POPPLERDATA_VERSION="0.4.8"
POPPLERDATA_SUBDIR="poppler-data-${POPPLERDATA_VERSION}"
POPPLERDATA_FILE="poppler-data-${POPPLERDATA_VERSION}.tar.gz"
POPPLERDATA_URL="https://poppler.freedesktop.org/${POPPLERDATA_FILE}"
POPPLERDATA_SHA256="1096a18161f263cccdc6d8a2eb5548c41ff8fcf9a3609243f1b6296abdf72872"

echo "Fetching poppler data"
	wget --no-check-certificate "${POPPLERDATA_URL}"
	CHKSUM=$(openssl dgst -sha256 "${POPPLERDATA_FILE}" 2> /dev/null)
	if [ "${CHKSUM}" != "SHA256(${POPPLERDATA_FILE})= ${POPPLERDATA_SHA256}" ]; then
		echo "Wrong checksum"
		echo "${CHKSUM}"
		echo "(expected: ${POPPLERDATA_SHA256})"
		exit 1
	fi
tar -x -C package-zip/share/ -f ./${POPPLERDATA_FILE} && mv package-zip/share/${POPPLERDATA_SUBDIR} package-zip/share/poppler

	
cd package-zip && zip -r ./texstudio-win-${VERSION_NAME}.zip *
cd ..
sha256sum ./texstudio_installer.exe
sha256sum ./texstudio.exe
sha256sum ./package-zip/texstudio-win-${VERSION_NAME}.zip
cp ./package-zip/texstudio-win-${VERSION_NAME}.zip ./texstudio-${GIT_VERSION}-win-portable-qt5.zip
cp ./texstudio_installer.exe ./texstudio-${GIT_VERSION}-win-qt5.exe
cp ./texstudio_installer.exe ./texstudio-win-${VERSION_NAME}.exe


