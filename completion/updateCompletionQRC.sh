#!/bin/bash

#generate completion.qrc
echo "Generate completion.qrc"
rm ../completion.qrc
echo "<RCC>">../completion.qrc
echo "<qresource prefix=\"/\">">>../completion.qrc
ls -1 *.cwl|xargs -i echo "<file>"completion/{}"</file>" >> ../completion.qrc
ls -1 *.dat|xargs -i echo "<file>"completion/{}"</file>" >> ../completion.qrc
echo "</qresource>">>../completion.qrc
echo "</RCC>">>../completion.qrc