# hrefhide package
# Matthew Bertucci 2023/02/26 for v1.1a

#include:xcolor
#include:hyperref
#include:kvoptions

#keyvals:\usepackage/hrefhide#c
linktextcolour=#%color
backgroundcolour=#%color
pdfborder={%<a b c%>}
#endkeyvals

\hrefdisplayonly{URL}{text%plain}#U
\hycon
\hycoff

hyanchorbordercolor#B
hycitebordercolor#B
hyfilebordercolor#B
hylinkbordercolor#B
hymenubordercolor#B
hyrunbordercolor#B
hyurlbordercolor#B

\ifhrefhide#S
\hrefhidetrue#S
\hrefhidefalse#S
