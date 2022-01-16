# hep-font package
# Matthew Bertucci 11/13/2021 for v1.0

#include:kvoptions
#include:ifluatex
#include:ifxetex
#include:fontenc
#include:fix-cm
#include:microtype
#include:cfr-lm
#include:textcomp
#include:slantsc
#include:inputenc

#keyvals:\usepackage/hep-font#c
oldstyle
lining#true,false
#endkeyvals

\ifxetexorluatex#*
\xetexorluatextrue#*
\xetexorluatexfalse#*

\textui{text}

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