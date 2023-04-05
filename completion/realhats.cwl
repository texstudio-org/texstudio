# realhats package
# Matthew Bertucci 2023/04/05 for v7.0

#include:amsmath
#include:calc
#include:graphicx
#include:ifthen
#include:lcg
#include:stackengine

\hat{arg}#m
\hat[type%keyvals]{arg}#m

#keyvals:\hat,\usepackage/realhats#c,\hatn,\hatnoptions
beret
santa
sombrero
witch
tophat
ash
fez
cowboy
crown
dunce
policeman
scottish
birthday
mortarboard
tile-white
tile-gray
tile-light-blue
tile-blue
#endkeyvals

\myhat#S
\hatwidth#*
\hshif#*
\vshif#*
\hatused#*
\gethat#*
\hatn{arg}{type%keyvals}#*
\hatnoptions{arg}{type%keyvals}{hshift%l}{vshift%l}#*
