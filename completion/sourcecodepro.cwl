# sourcecodepro package
# Matthew Bertucci 1/11/2022 for v2.7

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:fontenc
#include:mweights

#keyvals:\usepackage/sourcecodepro#c
lining
nf
lf
oldstyle
osf
tabular
proportional
black
semibold
bold
light
extralight
regular
scale=%<factor%>
scaled=%<factor%>
default
ttdefault
nottdefault
type1
t1
opentype
otf
ligatures=#Required,Common,Contextual,Rare,Discretionary,Historic,TeX
#endkeyvals

\sourcecodepro#*
\sourcecodepromedium#*
\sourcecodeprolight#*
\sourcecodeproextreme#*
\sourcecodeprolf#*
\nativeoldstylenums{text}#*

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
