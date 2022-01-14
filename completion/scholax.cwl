# scholax package
# Matthew Bertucci 9/13/2021 for v1.030

#include:textcomp
#include:xstring
#include:fontenc
#include:mweights
#include:fontaxes
#include:etoolbox
#include:xkeyval
#include:ifthen

#keyvals:\usepackage/scholax#c
scale=%<factor%>
scaled=%<factor%>
spacing=##L
stretch=##L
shrink=##L
foresolidus=##L
aftsolidus=##L
raisefrac=##L
theoremfont
scosf
sups
lining
lf
oldstyle
osf
tabular
p
proportional
mainfont
tighter
looser
loosest
#endkeyvals

\infigures
\lfstyle
\osfstyle
\sufigures
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textin{text}
\textinferior{text}#*
\textlf{text}
\textosf{text}
\textsu{text}
\textsuperior{text}#*
\texttlf{text}
\texttosf{text}
\thfamily
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
