#!/bin/bash
# provide the path to the gesym-ng binary as first argument

#GESYMBNG=$1
GESYMBNG="../gesymb-ng"
BATIK="/home/sdm/Dokumente/Programmieren/texstudio/symbols-ng/batikConvert.sh"
SYMBOLS_all="arrows cyrillic delimiters greek misc-math misc-text operators relation special wasysym icons fontawesome5"
#SYMBOLS="arrows cyrillic delimiters greek misc-math misc-text operators relation special wasysym icons fontawesome5"
#SYMBOLS="cyrillic misc-text special"
SYMBOLS="misc-text"

echo "Deleting old files..."

for i in $SYMBOLS; do
  if [ -d $i ]; then
    cd $i
    rm -f *
    cd ..
  fi

done

for i in $SYMBOLS; do

  echo "Generating image files in $i..."
  mkdir -p generate
  if [ ! -d $i ]; then
    mkdir $i
  fi
  cd generate
  $GESYMBNG "../$i.xml" $BATIK &> log.txt
  mv *.svg "../$i"
  mv *.png "../$i"
  cd ..
  #rm -rf generate

done

#generate symbols.qrc
echo "Generate symbols.qrc"
rm ../symbols.qrc
echo "<RCC>">../symbols.qrc
echo "<qresource prefix=\"/\">">>../symbols.qrc
for i in $SYMBOLS_all; do
  ls -1 $i|xargs -i echo "<file>"symbols-ng/$i/{}"</file>" >> ../symbols.qrc
done
echo "</qresource>">>../symbols.qrc
echo "</RCC>">>../symbols.qrc
