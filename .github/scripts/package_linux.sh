#!/usr/bin/env sh

# Exit on errors
set -e

. ../.github/scripts/get-version.sh

echo "Running linuxdeployqt"

wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt-continuous-x86_64.AppImage
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
export VERSION=linux-${VERSION_NAME}
cp ../utilities/texstudio.svg appdir
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -extra-plugins=iconengines/libqsvgicon.so -appimage
# ./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage
cp TeXstudio-${VERSION}-x86_64.AppImage ../texstudio-${VERSION}-x86_64.AppImage
cp TeXstudio-${VERSION}-x86_64.AppImage ../texstudio-${GIT_VERSION}-x86_64.AppImage
sha256sum appdir/usr/bin/texstudio 
sha256sum ../texstudio-${VERSION}-x86_64.AppImage 


