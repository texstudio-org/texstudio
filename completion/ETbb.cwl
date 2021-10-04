# ETbb package
# Matthew Bertucci 9/30/2021 for v1.053

#include:textcomp
#include:ifetex
#include:etoolbox
#include:xstring
#include:ifthen
#include:scalefnt
#include:mweights
#include:fontaxes

\swshape
\lfstyle
\textlf{text}
\tlfstyle
\texttlf{text}
\osfstyle
\textosf{text}
\tosfstyle
\texttosf{text}
\sufigures
\supfigures#*
\textsu{text}
\textsup{text}#*
\textsuperior{text}#*
\infigures
\inffigures#*
\textin{text}
\textinf{text}#*
\textinferior{text}#*
\defigures
\denomfigures#*
\textde{text}
\textdenom{text}#*
\textdenominator{text}#*
\Qswash
\useosf
\useproportional

#ifOption:swashQ
\Qnoswash
#endif