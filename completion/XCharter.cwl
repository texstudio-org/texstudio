# XCharter package
# Matthew Bertucci 9/7/2021 for v1.222

#include:fontenc
#include:fontaxes
#include:textcomp
#include:scalefnt
#include:mweights
#include:etoolbox
#include:xstring
#include:ifthen
#include:xkeyval

#keyvals:\usepackage/XCharter#c
scale=%<factor%>
scaled=%<factor%>
foresolidus=##L
aftsolidus=##L
lf
lining
oldstyle
oldstyleI
theoremfont
osf
osfI
sups
scosf
serbianc
#endkeyvals

\defigures
\infigures
\lfstyle
\osfstyle
\nufigures
\sufigures
\textde{text}#*
\textdenominator{text}
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textinf{text}
\textinferior{text}#*
\textlf{text}
\textosf{text}
\textosfI{text}
\textnu{text}#*
\textnumerator{text}
\textruble
\textsu{text}
\textsuperior{text}#*
\textth{text}
\textthit{text}#*
\thdefault#*
\thfamily
\useosf#*
\useosfI#*

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
