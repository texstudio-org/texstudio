#!/bin/bash
# please set path to batik-rasterizer.jar correctly (part of apache batik package)

BATIK="/home/sdm/Dokumente/Programmieren/texstudio/symbols-ng/batik-1.19/batik-rasterizer-1.19.jar"

java -jar $BATIK $1 -d $2 -dpi 600
