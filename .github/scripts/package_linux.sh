#!/usr/bin/env sh

# Exit on errors
set -e

. .github/scripts/get-version.sh

echo "Running linuxdeployqt"

make INSTALL_ROOT=appdir -j$(nproc) install ; find appdir/
wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt-continuous-x86_64.AppImage
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
export VERSION=linux-${VERSION_NAME}
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -extra-plugins=iconengines/libqsvgicon.so
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage
sha256sum appdir/usr/bin/texstudio 
sha256sum TeXstudio-${VERSION}-x86_64.AppImage 


