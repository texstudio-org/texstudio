# cheatsheet class
# Matthew Bertucci 2/7/2022 for v1.0

#include:kvoptions
#include:xifthen
#include:hyperref
#include:fontenc
# fontenc loaded with T1 option
#include:libertine
#include:suffix
#include:amsmath
#include:amssymb
#include:multicol
#include:csquotes
#include:xcolor
#include:mdframed
#include:listings
#include:etoolbox
#include:geometry

#keyvals:\documentclass/cheatsheet#c
columns=%<integer%>
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
leqno
fleqn
openbib
#endkeyvals

\theauthor
\thedate
\thetitle

primaryColor#B
secondaryColor#B

\csfileversion#S
\csfiledate#S

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