# realhats package
# Matthew Bertucci 8/22/2021 for v5.0

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
#endkeyvals

\myhat#S
\hatwidth#*
\hshif#*
\vshif#*
\hatused#*
\gethat#*
\hatn{arg}{type%keyvals}#*
\hatnoptions{arg}{type%keyvals}{hshift%l}{vshift%l}#*
