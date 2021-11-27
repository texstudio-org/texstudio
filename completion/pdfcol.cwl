# pdfcol package
# Matthew Bertucci 11/24/2021 for v1.6

#include:ltxcmds
#include:infwarerr
#include:iftex
#include:color

\ifpdfcolAvailable#*
\pdfcolAvailabletrue#*
\pdfcolAvailablefalse#*
\pdfcolErrorNoStacks#*
\pdfcolInitStack{name}#*
\pdfcolIfStackExists{name}{then}{else}#*
\pdfcolSwitchStack{name}#*
\pdfcolSetCurrentColor#*
\pdfcolSetCurrent{name}#*