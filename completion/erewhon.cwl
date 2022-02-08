# erewhon package
# Matthew Bertucci 2/7/2022 for v1.119

#include:fontenc
#include:textcomp
#include:mweights
#include:xstring
#include:ifthen
#include:scalefnt
#include:etoolbox
#include:fontaxes
#include:xkeyval

#keyvals:\usepackage/erewhon#c
scale=%<factor%>
scaled=%<factor%>
spacing=##L
stretch=##L
shrink=##L
space=%<factor%>
foresolidus=##L
aftsolidus=##L
lining
lf
oldstyle
osf
tabular
p
proportional
sups
scosf
looser
loosest
#endkeyvals

\defigures
\destyle#*
\infigures
\lfstyle
\nufigures
\nustyle#*
\osfstyle
\sufigures
\swshape
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textin{text}
\textinferior{text}#*
\textlf{text}
\textosf{text}
\textsu{text}
\textsuperior{text}#*
\textde{text}
\textdenominator{text}#*
\textnu{text}
\textnumerator{text}#*
\textruble
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
