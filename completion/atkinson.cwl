# atkinson package
# Matthew Bertucci 1/11/2022

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:textcomp
#include:fontenc
#include:fontaxes
#include:mweights

#keyvals:\usepackage/atkinson#c
scale=%<factor%>
scaled=%<factor%>
default
sfdefault
type1
t
proportional
p
#endkeyvals

\atkinsonfamily#*
\atkinson#*
\atkinsonlf#*
\atkinsontlf#*

\atkinsonLF{text}
\atkinsonTLF{text}

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