# stickstootext package
# Matthew Bertucci 9/7/2021 for v1.035

#include:fontenc
#include:textcomp
#include:mweights
#include:etoolbox
#include:fontaxes
#include:xkeyval

#keyvals:\usepackage/stickstootext#c
scale=%<factor%>
scaled=%<factor%>
lining
lf
oldstyle
osf
p
proportional
t
tabular
theoremfont
sups
scosf
foresolidus=##L
aftsolidus=##L
#endkeyvals

\defigures
\infigures
\lfstyle
\nufigures
\osfstyle
\sufigures
\textde{text}
\textdenominators{text}#*
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textinf{text}
\textinferior{text}#*
\textlf{text}
\textnu{text}
\textnumerators{text}#*
\textosf{text}
\textsu{text}
\textsuperior{text}#*
\texttlf{text}
\texttosf{text}
\tlfstyle
\tosfstyle
\useosf#*
\useproportional#*

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
