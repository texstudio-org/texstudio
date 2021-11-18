# ETbb package
# Matthew Bertucci 9/30/2021 for v1.053

#include:fontenc
#include:textcomp
#include:ifetex
#include:etoolbox
#include:xstring
#include:ifthen
#include:scalefnt
#include:mweights
#include:fontaxes
#include:xkeyval

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

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
