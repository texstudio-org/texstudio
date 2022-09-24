# pdfcol package
# Matthew Bertucci 2022/09/24 for v1.7

#include:ltxcmds
#include:infwarerr
#include:iftex
#include:color

\ifpdfcolAvailable#*
\pdfcolAvailabletrue#S
\pdfcolAvailablefalse#S
\pdfcolErrorNoStacks#*
\pdfcolInitStack{name}#*
\pdfcolIfStackExists{name}{then}{else}#*
\pdfcolSwitchStack{name}#*
\pdfcolSetCurrentColor#*
\pdfcolSetCurrent{name}#*
