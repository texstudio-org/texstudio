# geistserif package
# Matthew Bertucci 2026/11/11 for v1.9.2

#include:iftex
#include:xkeyval

#keyvals:\usepackage/geistserif#c
mainfont
scale=#%<factor%>,MatchLowercase
lining
tabular
proportional
bold
semibold
extrabold
black
regular
medium
variant=#regular,square,triangle,heart
#endkeyvals

\geistserifvariant{variant}

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n