# InriaSerif package
# Matthew Bertucci 7/27/2021

#include:fontaxes
#include:fontenc
#include:mweights
#include:textcomp
#include:xkeyval

#keyvals:\usepackage/InriaSerif#c
scale=%<factor%>
scaled=%<factor%>
lining
oldstyle
tabular
proportional
bold
light
regular
#endkeyvals

\tlshape
\texttl{text}
\texttitling{text}#*
\sufigures
\textsu{text}
\textsuperior{text}#*
\tldefault#*

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
