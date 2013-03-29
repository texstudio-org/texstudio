#!/bin/bash
# provide the path to the gesym-ng binary as first argument

GESYMBNG=$1
SYMBOLS="arrows cyrillic delimiters greek misc-math misc-text operators relation special"
#SYMBOLS="test"

echo "Deleting old files..."

for i in $SYMBOLS; do
  if [ -a $i ]; then
    cd $i
    rm -f *.svg
    cd ..
  fi

done

for i in $SYMBOLS; do

  echo "Generating image files in $i..."
  mkdir -p generate
  if [ ! -a $i ]; then
    mkdir $i
  fi
  cd generate
  $GESYMBNG "../$i.xml" &> /dev/null
  mv *.svg "../$i"
  cd ..
  rm -rf generate

done