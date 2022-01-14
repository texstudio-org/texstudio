# heuristica package
# Matthew Bertucci 9/13/2021 for v1.092

#include:fontenc
#include:textcomp
#include:ifthen
#include:fontaxes
#include:mweights
#include:etoolbox
#include:xkeyval

#keyvals:\usepackage/heuristica#c
scale=%<factor%>
scaled=%<factor%>
spacing=##L
stretch=##L
shrink=##L
space=%<factor%>
lining
lf
oldstyle
osf
tabular
sups
looser
loosest
#endkeyvals

\infigures
\Qswash
\sufigures
\swshape
\textfrac{numerator}{denominator}
\textin{text}
\textinferior{text}#*
\textlf{text}
\textosf{text}
\textsu{text}
\textsuperior{text}#*
\texttlf{text}
\texttosf{text}
\useosf#*

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
