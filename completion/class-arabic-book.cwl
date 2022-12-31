# arabic-book class
# Matthew Bertucci 4/9/2022 for v1.0

#include:class-book
#include:polyglossia
#include:hyperref
#include:geometry
#include:amsmath
#include:enumitem
#include:tikz
#include:tikzlibrarymatrix
#include:tikzlibrarydecorations.pathmorphing
#include:setspace
#include:titling
#include:ifthen
#include:titlesec
#include:indentfirst
#include:tocloft
#include:etoolbox
#include:totalcount
#include:tocbibind
#include:newfloat
#include:caption
#include:collcell
#include:float
#include:xwatermark

# passes all options to book class
#keyvals:\documentclass/arabic-book#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\arabicfont
\arabicfonttt
\begin{appendixfigure}
\end{appendixfigure}
\theappendixfigure#*
\listofappendixfigures#*
\begin{appendixtable}
\end{appendixtable}
\theappendixtable#*
\listofappendixtables#*
\abstract{text}
\makeabstract#*
\namedappendix{title}
\SepMark{mark}
