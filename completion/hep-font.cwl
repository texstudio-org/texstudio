# hep-font package
# Matthew Bertucci 2022/11/02 for v1.1

#include:kvoptions
#include:ifluatex
#include:ifxetex
#include:fontenc
#include:pdftexcmds
#include:fix-cm
#include:microtype
#include:cfr-lm
#include:textcomp
#include:slantsc
#include:inputenc

#keyvals:\usepackage/hep-font#c
size=#8pt,9pt,10pt,11pt,12pt,14pt,17pt,20pt,default
sans
serif
oldstyle
lining
#endkeyvals

#ifOption:oldstyle
#include:units
#include:xpatch
#endif
#ifOption:oldstyle=true
#include:units
#include:xpatch
#endif

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
