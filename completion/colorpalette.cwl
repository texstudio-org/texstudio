# colorpalette package
# Matthew Bertucci 8/19/2021 for v1.1.0

#include:xcolor
#include:macrolist

\newpalettetheme{theme}
\addcolortotheme{theme}{color}
\newpalette{theme}{palette}
\setpalettecolor{theme}{palette}{color}[encoding]{value}
\activepalette{theme}{palette}
\getcolor{theme}{color}
\applycolor{theme}{color}