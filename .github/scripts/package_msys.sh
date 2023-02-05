#!/usr/bin/env sh

# Exit on errors
#set -e

echo "package build into zip for win"
# workaround for botched qt6 installation
if [ -f /mingw64/bin/qmake-qt6.exe ]; then 
cp /mingw64/bin/qmake-qt6.exe /mingw64/bin/qmake.exe
fi
if [ -f /ucrt64/bin/qmake-qt6.exe ]; then 
cp /ucrt64/bin/qmake-qt6.exe /ucrt64/bin/qmake.exe 
fi
echo "copy qt dlls and plugins"
mkdir -p package-zip
cp texstudio.exe package-zip/
cd package-zip
#cp /mingw64/bin/libicudt68.dll /mingw64/bin/icudt68.dll
windeployqt-qt6 texstudio.exe
echo "copy dlls"
#ldd texstudio.exe | awk '{print $3}'| grep ming | xargs -I{} cp -u {} .
ldd texstudio.exe | awk '{print $3}'| grep ucrt64 | xargs -I{} cp -u {} .
# force ssl/crypto copy
#ldd texstudio.exe | awk '{print $3}'| grep libcrypto | xargs -I{} cp -u {} .
#ldd texstudio.exe | awk '{print $3}'| grep libssl | xargs -I{} cp -u {} .
# check copied dlls
echo "check dlls"
ldd texstudio.exe
cd ..
echo "copy directories"
mkdir -p ./package-zip/translations
cp -r ../translation/* ./package-zip/translations
cp -r ../templates package-zip
mkdir -p ./package-zip/help
cp -r ../utilities/manual/build package-zip/help
cp ../utilities/manual/source/CHANGELOG.md package-zip/help
cp ../utilities/latex2e.css package-zip/help
cp ../utilities/list.png package-zip/help
cp ../utilities/latex2e.html package-zip/help
cp -r ../utilities/dictionaries package-zip/dictionaries
cp -r ../utilities/TexTablet package-zip/TexTablet
mkdir -p package-zip/share
cp -r package-zip/tls .
cp -r ../travis-ci/mxe/fonts package-zip/share/fonts
# poppler data
cd package-zip
cp -r $MSYSTEM_PREFIX/share/poppler share
cd ..
echo "make installer"
cp ../utilities/texstudio-msys.nsi .
cp ../utilities/FileAssociation.nsh .
makensis texstudio-msys.nsi
# zip package
cd package-zip
mkdir config
zip -r ./texstudio-win-qt6-${VERSION_NAME}.zip *

cd ..
sha256sum ./texstudio_installer.exe
sha256sum ./texstudio.exe
sha256sum ./package-zip/texstudio-win-qt6-${VERSION_NAME}.zip
cp ./package-zip/texstudio-win-qt6-${VERSION_NAME}.zip ../texstudio-${GIT_VERSION}-win-portable-qt6.zip
cp ./texstudio_installer.exe ../texstudio-${GIT_VERSION}-win-qt6.exe
cp ./texstudio_installer.exe ../texstudio-win-qt6-${VERSION_NAME}.exe
