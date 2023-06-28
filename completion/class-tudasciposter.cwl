# tudasciposter class
# Matthew Bertucci 2022/08/17 for v3.27

#include:l3keys2e
#include:class-scrartcl
#include:tudafonts
#include:tikz
#include:tikzlibrarycalc
#include:tcolorbox
#include:tcolorboxlibraryposter
#include:pdfcol
#include:geometry
#include:tudarules
#include:tudacolors
#include:qrcode
#include:hyperref

#keyvals:\documentclass/tudasciposter#c
color=#%color
accentcolor=#%color
textaccentcolor=#%color
identbarcolor=#%color
footer#true,false
pdfa#true,false
boxstyle=#official,colored,boxed,default
paper=#a0,a1,a2,a3
fontsize=##L
logofile=%<Dateipfad%>
title=#default,large,small
colorback#true,false
#endkeyvals

#ifOption:pdfa
#include:pdfx
#endif
#ifOption:pdfa=true
#include:pdfx
#endif

\footergraphics{graphics code}
\footer{text}
\footerqrcode{URL}#U
\footerqrcode*{URL}#U
\Metadata{keyvals}
\authorandname#*
\titlegraphic{graphics code}
\institute{Einrichtung}
\inst{arg}
\contentwidth#L
\contentheight#L

titlefgcolor#B
titlebgcolor#B
blocktitlebgcolor#B
innerblockbodybgcolor#B
backgroundcolor#B
framecolor#B
blockbodybgcolor#B
blockbodyfgcolor#B
innerblocktitlebgcolor#B
innerblocktitlefgcolor#B
innerblockbodyfgcolor#B

#keyvals:\posterbox,\begin{posterboxenv}
TUDa
TUDa-inner
TUDa-colored
TUDa-colored-inner
TUDa-boxed
TUDa-boxed-inner
#endkeyvals
