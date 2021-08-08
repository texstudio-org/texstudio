#!/usr/bin/env sh

# Exit on errors
set -e

. .github/scripts/get-version.sh
 
echo "package build into zip for win"
# workaround for botched qt6 installation
cp /mingw64/bin/qmake-qt6.exe /mingw64/bin/qmake.exe
echo "copy dlls and qt5 plugins"
mkdir -p package-zip
cp texstudio.exe package-zip/
cd package-zip
cp /mingw64/bin/libicudt68.dll /mingw64/bin/icudt68.dll
windeployqt texstudio.exe
ldd texstudio.exe | awk '{print $3}'| grep ming | xargs -I{} cp -u {} .
# force ssl/crypto copy
ldd texstudio.exe | awk '{print $3}'| grep libcrypto | xargs -I{} cp -u {} .
ldd texstudio.exe | awk '{print $3}'| grep libssl | xargs -I{} cp -u {} .
# check copied dlls
ldd texstudio.exe
cd ..
echo "copy directories"
cp -r ./translation ./package-zip/translations
cp -r ./templates package-zip
cp -r ./utilities/manual package-zip/help
cp ./utilities/latex2e.css package-zip/help
cp ./utilities/latex2e.html package-zip/help
cp -r ./utilities/dictionaries package-zip/dictionaries
cp -r ./utilities/TexTablet package-zip/TexTablet
cp -r ./travis-ci/mxe/fonts package-zip/share/
# poppler data
cd package-zip
cp -r $MSYSTEM_PREFIX/share/poppler share
cd ..
echo "make installer"
cp ./utilities/texstudio-msys.nsi .
cp ./utilities/FileAssociation.nsh .
makensis texstudio-msys.nsi
# zip package
cd package-zip
zip -r ./texstudio-win-qt6-${VERSION_NAME}.zip *

cd ..
sha256sum ./texstudio_installer.exe
sha256sum ./texstudio.exe
sha256sum ./package-zip/texstudio-win-qt6-${VERSION_NAME}.zip
cp ./package-zip/texstudio-win-qt6-${VERSION_NAME}.zip ./texstudio-${GIT_VERSION}-win-portable-qt6.zip
cp ./texstudio_installer.exe ./texstudio-${GIT_VERSION}-win-qt6.exe
cp ./texstudio_installer.exe ./texstudio-win-qt6-${VERSION_NAME}.exe
