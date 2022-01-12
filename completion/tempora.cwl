# tempora package
# Matthew Bertucci 9/13/2021 for v1.05

#include:textcomp
#include:fontaxes
#include:fontenc
#include:xkeyval

#keyvals:\usepackage/tempora#c
scale=%<factor%>
scaled=%<factor%>
lining
oldstyle
#endkeyvals

\sufigures
\textsu{text}
\textsuperior{text}#*
\LGCscale#*

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
