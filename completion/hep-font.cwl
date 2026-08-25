# hep-font package
# Matthew Bertucci 2026/08/19 for v1.5

#include:kvoptions
#include:iftex
#include:fontenc
#include:pdftexcmds
#include:fix-cm
#include:microtype
#include:cfr-lm
#include:slantsc
#include:inputenc
#include:etoolbox
#include:silence
#include:xpatch

#keyvals:\usepackage/hep-font#c
size=#8pt,9pt,10pt,11pt,12pt,14pt,17pt,20pt,default
sans
serif
oldstyle
lining
#endkeyvals

\textui{text}

\codestyle#*
\code{text%plain}

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
