#!/usr/bin/env sh

# Exit on errors
set -e

. ../.github/scripts/get-version.sh

echo "Running linuxdeployqt"

#wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
#chmod a+x linuxdeployqt-continuous-x86_64.AppImage
wget -c https://github.com/$(wget -q https://github.com/probonopd/go-appimage/releases/expanded_assets/continuous -O - | grep "appimagetool-.*-x86_64.AppImage" | head -n 1 | cut -d '"' -f 2)
chmod +x appimagetool-*.AppImage
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
export VERSION=linux-${VERSION_NAME}
cp ../utilities/texstudio.svg appdir
./appimagetool-*.AppImage deploy appdir/usr/share/applications/*.desktop
# ./appimagetool-*.AppImage -s deploy appdir/usr/share/applications/*.desktop # Bundle EVERYTHING
# ./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -extra-plugins=iconengines/libqsvgicon.so -appimage
# ./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage
./appimagetool-*.AppImage ./appdir # create actual appimage
cp TeXstudio-${VERSION}-x86_64.AppImage ../texstudio-${VERSION}-x86_64.AppImage
cp TeXstudio-${VERSION}-x86_64.AppImage ../texstudio-${GIT_VERSION}-x86_64.AppImage
sha256sum appdir/usr/bin/texstudio 
sha256sum ../texstudio-${VERSION}-x86_64.AppImage 


