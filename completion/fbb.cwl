# fbb package
# Matthew Bertucci 9/7/2021 for v1.16

#include:fontaxes
#include:fontenc
#include:textcomp
#include:ifetex
#include:etoolbox
#include:xstring
#include:ifthen
#include:mweights
#include:xkeyval

\defigures
\infigures
\inffigures#*
\lfstyle
\nufigures
\osfstyle
\Qswash
\sufigures
\swshape
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textin{text}
\textinf{text}#*
\textinferior{text}#*
\textlf{text}
\textosf{text}
\textsu{text}
\textsup{text}#*
\textsuperior{text}#*
\textde{text}
\textnu{text}
\texttlf{text}
\texttosf{text}
\tlfstyle
\tosfstyle
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
