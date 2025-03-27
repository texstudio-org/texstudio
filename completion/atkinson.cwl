# atkinson package
# Matthew Bertucci 2025/03/18

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:fontenc
#include:fontaxes
#include:mweights

#keyvals:\usepackage/atkinson#c
scaled=%<factor%>
default
sfdefault
type1
semibold
extrabold
medium
light
extralight
t
nomono
#endkeyvals

\atkinsonfamily#*
\atkinson#*
\atkinsonlf#*
\atkinsontlf#*

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
