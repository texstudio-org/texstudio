#!/bin/bash

#generate completion.qrc
echo "Generate completion.qrc"
rm ../completion.qrc
echo "<RCC>">../completion.qrc
echo "<qresource prefix=\"/\">">>../completion.qrc
ls -1 *.cwl|xargs -I '{}' echo "<file>"completion/{}"</file>" >> ../completion.qrc
ls -1 *.dat|xargs -I '{}' echo "<file>"completion/{}"</file>" >> ../completion.qrc
echo "</qresource>">>../completion.qrc
echo "</RCC>">>../completion.qrc