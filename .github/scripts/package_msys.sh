#!/usr/bin/env sh

# Exit on errors
set -e

. .github/scripts/get-version.sh
 
echo "package build into zip for win"

echo "copy dlls and qt5 plugins"
mkdir -p package-zip
cp texstudio.exe package-zip/
cd package-zip
windeployqt texstudio.exe
ldd texstudio.exe | awk '{print $3}'| grep ming | xargs -I{} cp -u {} .
ldd texstudio.exe
cd ..
echo "make installer"
cp -r ./translation ./package-zip
cp -r ./templates package-zip
cp -r ./utilities/manual package-zip/help
cp ./utilities/latex2e.css package-zip/help
cp ./utilities/latex2e.html package-zip/help
cp -r ./utilities/TexTablet package-zip/TexTablet
cp -r ./travis-ci/mxe/fonts package-zip/share/
# poppler data
cd package-zip
cp -r $MSYSTEM_PREFIX/share/poppler share

archivegen txs.7z *
## manage sub-packages languages
charexists() {
  char="$1"; shift
  case "$*" in *"$char"*) return;; esac; return 1
}

cp -r ../utilities/dictionaries dictionaries
for i in `ls dictionaries/*.dic`
do
	zw=$(echo $i| cut -f 2 -d / |cut -f 1 -d .);
	mkdir -p ../packages/dictionaries.$zw/data
	mkdir -p ../packages/dictionaries.$zw/meta
	archivegen dict.7z dictionaries/$zw.*
	mv dict.7z ../packages/dictionaries.$zw/data
	cp ../utilities/package_dict.xml ../packages/dictionaries.$zw/meta/package.xml
	sed -i "s/lang/${zw}/g" ../packages/dictionaries.$zw/meta/package.xml
	charexists "-" $zw &&  sed -i "s/true/false/g" ../packages/dictionaries.$zw/meta/package.xml
done

cd ..
mkdir -p packages/dictionaries/data
mkdir -p packages/dictionaries/meta
cp utilities/package_dictionaries.xml packages/dictionaries/meta/package.xml
mkdir -p packages/texstudio/data
mkdir -p packages/texstudio/meta
cp utilities/license.txt packages/texstudio/meta
mv package-zip/txs.7z packages/texstudio/data
cp utilities/installscript.qs packages/texstudio/meta
cp utilities/package.xml packages/texstudio/meta



