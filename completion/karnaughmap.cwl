# karnaughmap package
# Matthew Bertucci 12/22/2021 for v2.0

#include:tikz
#include:xkeyval
#include:ifthen
#include:xstring

\karnaughmap{entries}
\karnaughmap[options%keyvals]{entries}

\karnaughmapcolorfield{map size}{field string}{color}
\karnaughmapcolorfield[TikZ keys]{map size}{field string}{color}

\setkarnaughmap[options%keyvals]

#keyvals:\karnaughmap,\setkarnaughmap
omitzeros#true,false
omitones#true,false
omitdontcares#true,false
omitbinaries#true,false
omitvariables#true,false
omitidx#true,false
binaryidx#true,false
omitnegated#true,false
outline#true,false
fill#true,false
opacity=%<factor%>
defaultmap=%<number%>
function=%<function label%>
variables=%<variables%>
dontcare=%<character%>
color=#%color
draw=#%color
labelcolor=#%color
xshift=##L
yshift=##L
#endkeyvals

\karnaughmapCellEntries#*
\karnaughmapHighlightField{coordinates}{color}#*
\karnaughmapHighlightField[options]{coordinates}{color}#*
\karnaughmapNumCol#*
\karnaughmapNumRow#*
\karnaughmapNumVar#*
\karnaughmapPCCColumnSpecifier#*
\karnaughmapPrintCellContents{xoffset}{yoffset}{size}{rowsize}{function}#*
\karnaughmapPrintCellContents[node pos]{xoffset}{yoffset}{size}{rowsize}{function}#*
\karnaughmapPrintIndex#*
\karnaughmapPrintIndex[numBits]#*
\karnaughmapPrintValue{input string}#*
\karnaughmapPrintValue[value]{input string}#*
\karnaughmapShadeMapfieldFOUR{decimal number}{color}#*
\karnaughmapShadeMapfieldFOUR[options]{decimal number}{color}#*
\karnaughmapShadeMapfieldTHREE{decimal number}{color}#*
\karnaughmapShadeMapfieldTHREE[options]{decimal number}{color}#*
\karnaughmapShadeMapfieldTWO{decimal number}{color}#*
\karnaughmapShadeMapfieldTWO[options]{decimal number}{color}#*
\karnaughmapSize#*
\karnaughmapVarLabelB#*
\karnaughmapVarLabelD#*
\karnaughmapVariableBaseBias#*
\karnaughmapVariableLeftBias#*
\karnaughmapVariableTopBias#*
\thekarnaughmapIdxCounter#*
\thekarnaughmapStrCounter#*