# scanpages package
# Matthew Bertucci 2022/06/23 for v1.05

#include:ifpdf
#include:pgffor
#include:xcolor
#include:xkeyval
#include:fp-basic
#include:graphicx
#include:etoolbox

#keyvals:\usepackage/scanpages#c
nogrid#true,false
scale=%<factor%>
llx=##L
lly=##L
w=##L
h=##L
#endkeyvals

\scanpage{imagefile}#g
\scanpage[options%keyvals]{imagefile}#g

#keyvals:\scanpage
origpgnum=%<page number%>
origindest#true,false
origpgnumoff#true,false
dx=##L
dy=##L
page=%<page number%>
rot=%<degrees%>
tanrot=%<tangent%>
#endkeyvals

\initviewport{scale}{llx%l}{lly%l}{w%l}{h%l}

\whitesq(x,y){scale}
\whitesq(x,y){x-scale}[y-scale]
\whitecirc(x,y){scale}
\whitecirc(x,y){x-scale}[y-scale]

\origpgcmd#*
\origpgnum#*
\putn(x,y){stuff}#*
\thegrid{width}{height}#*

\fileversion#S
\filedate#S