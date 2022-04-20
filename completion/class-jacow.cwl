# jacow class
# Matthew Bertucci 4/19/2022 for v2.7

#include:fix-cm
#include:flushend
#include:etoolbox
#include:iftex
#include:textcase
#include:siunitx
#include:graphicx
#include:booktabs
#include:caption
#include:xcolor
#include:amsmath
#include:csquotes
#include:geometry
#include:footmisc
#include:url
#include:newtxtt
#include:textcomp
#include:fontenc
# loads T1 option of fontenc
#include:lmodern
#include:tgtermes
#include:newtxmath
#include:microtype
#include:enumitem
#include:cite

#keyvals:\documentclass/jacow#c
acus
aca4
boxit
biblatex
refpage
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:biblatex
#include:biblatex
# loads style=ieee option of biblatex
\mkpagegrouped{text}#*
\mkonepagegrouped{text}#*
#endif

\begin{Enumerate}
\end{Enumerate}
\begin{Itemize}
\end{Itemize}
\begin{Description}
\end{Description}
\titleblockheight#*
\titleblockstartskip#*
\titleblockmiddleskip#*
\titleblockendskip#*
\copyrightspace
\copyrightspace[length]

\fileversion#S
\filedate#S
\docdate#S
\ifjacowbiblatex#*
\jacowbiblatextrue#*
\jacowbiblatexfalse#*
\ifjacowrefpage#*
\jacowrefpagetrue#*
\jacowrefpagefalse#*
\urlZDtxt#*

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