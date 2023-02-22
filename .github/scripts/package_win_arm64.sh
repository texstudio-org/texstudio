#!/usr/bin/env sh

# Exit on errors
set -e

work_dir=$PWD
qt_dir=$work_dir/Qt/$qt_ver/msvc2019_arm64
poppler_dir=$work_dir/poppler
vcpkg_bin_dir=$work_dir/vcpkg/installed/arm64-windows/bin

mkdir ./package-zip
cp build/texstudio.exe package-zip
cd package-zip

cp $poppler_dir/bin/poppler-qt6.dll .
cp $poppler_dir/bin/poppler.dll .
cp $vcpkg_bin_dir/zlib*.dll .
cp $vcpkg_bin_dir/lcms*.dll .
cp $vcpkg_bin_dir/freetype.dll .
cp $vcpkg_bin_dir/tiff.dll .
cp $vcpkg_bin_dir/jpeg*.dll .
cp $vcpkg_bin_dir/libpng*.dll .
cp $vcpkg_bin_dir/openjp*.dll .
cp $vcpkg_bin_dir/bz2.dll .
cp $vcpkg_bin_dir/brotlidec.dll .
cp $vcpkg_bin_dir/brotlicommon.dll .
cp $vcpkg_bin_dir/liblzma.dll .

cp $qt_dir/bin/Qt6Core.dll .
cp $qt_dir/bin/Qt6Core5Compat.dll .
cp $qt_dir/bin/Qt6Concurrent.dll .
cp $qt_dir/bin/Qt6DBus.dll .
cp $qt_dir/bin/Qt6Gui.dll .
cp $qt_dir/bin/Qt6Network.dll .
cp $qt_dir/bin/Qt6PrintSupport.dll .
cp $qt_dir/bin/Qt6Qml.dll .
cp $qt_dir/bin/Qt6Svg.dll .
cp $qt_dir/bin/Qt6Widgets.dll .
cp $qt_dir/bin/Qt6Xml.dll .

mkdir ./iconengines
cp $qt_dir/plugins/iconengines/qsvgicon.dll ./iconengines
mkdir ./networkinformation
cp $qt_dir/plugins/networkinformation/qnetworklistmanager.dll ./networkinformation
mkdir ./platforms
cp $qt_dir/plugins/platforms/qwindows.dll ./platforms
mkdir ./styles
cp $qt_dir/plugins/styles/qwindowsvistastyle.dll ./styles
cp -r $qt_dir/plugins/imageformats .
rm ./imageformats/*d.dll
cp -r $qt_dir/plugins/tls .
rm ./tls/*dd.dll

mkdir ./config
cp -r ../utilities/dictionaries .
cp -r ../utilities/manual ./help
cp ../utilities/latex2e.css ./help
cp ../utilities/latex2e.html ./help
mkdir ./share
cp -r ../travis-ci/mxe/fonts ./share
cp -r $poppler_dir/share/poppler ./share
cp -r ../templates .
cp -r ../translation ./translations
mkdir ./TexTablet
cp ../utilities/TexTablet/license.txt ./TexTablet
cp ../utilities/TexTablet/*.xsl ./TexTablet
cp ../TexTablet/LatexTablet.net/bin/ARM64/Release/Interop.micautLib.dll ./TexTablet
cp ../TexTablet/LatexTablet.net/bin/ARM64/Release/TeXTablet.exe ./TexTablet

zip -r ./texstudio-win-arm64-qt6-${VERSION_NAME}.zip *
cp ./texstudio-win-arm64-qt6-${VERSION_NAME}.zip ../texstudio-${GIT_VERSION}-win-arm64-portable-qt6.zip
