# baskervillef package
# Matthew Bertucci 9/13/2021 for v1.051

#include:fontenc
#include:textcomp
#include:mweights
#include:etoolbox
#include:xstring
#include:ifthen
#include:fontaxes
#include:xkeyval

#keyvals:\usepackage/baskervillef#c
scale=%<factor%>
scaled=%<factor%>
spacing=##L
stretch=##L
shrink=##L
theoremfont
lining
lf
oldstyle
osf
tabular
t
proportional
p
sups
scosf
#endkeyvals

\lfstyle
\osfstyle
\sufigures
\textfrac{numerator}{denominator}
\textfrac[whole part]{numerator}{denominator}
\textlf{text}
\textosf{text}
\textsu{text}
\textsuperior{text}#*
\textde{text}
\textdenominators{text}#*
\defigures
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
