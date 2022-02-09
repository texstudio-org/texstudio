# ETbb package
# Matthew Bertucci 2/7/2022 for v1.056

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

#keyvals:\usepackage/ETbb#c
scale=%<factor%>
scaled=%<factor%>
foresolidus=##L
aftsolidus=##L
raisefrac=##L
altP
lining
lf
oldstyle
osf
useosf
tabular
t
proportional
p
sharpS
swashQ
mainfont
bold
regular
sups
scosf
#endkeyvals

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
\nustyle#*
\textsu{text}
\textsup{text}#*
\textsuperior{text}#*
\infigures
\inffigures#*
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textin{text}
\textinf{text}#*
\textinferior{text}#*
\defigures
\destyle#*
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
