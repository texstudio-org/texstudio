#!/bin/bash
# please set path to batik-rasterizer.jar correctly (part of apache batik package)

BATIK="/home/sdm/Dokumente/Programmieren/batik-1.7/batik-rasterizer.jar"

java -jar $BATIK $1 -d $2 -dpi 600
