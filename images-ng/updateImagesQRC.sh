#!/bin/bash

#generate completion.qrc
echo "Generate images.qrc"
rm ../images.qrc
echo "<RCC>">../images.qrc
echo "<qresource prefix=\"/\">">>../images.qrc
ls -1 *.svg*|xargs -i echo "<file>"images-ng/{}"</file>" >> ../images.qrc
ls -1 classic/*.svg*|xargs -i echo "<file>"images-ng/{}"</file>" >> ../images.qrc
ls -1 modern/*.svg*|xargs -i echo "<file>"images-ng/{}"</file>" >> ../images.qrc
ls -1 colibre/*.svg*|xargs -i echo "<file>"images-ng/{}"</file>" >> ../images.qrc
echo "</qresource>">>../images.qrc
echo "</RCC>">>../images.qrc