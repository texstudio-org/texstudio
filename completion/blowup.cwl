# blowup package
# Matthew Bertucci 11/13/2021 for v1.0

#include:atbegshi
#include:keyval
#include:graphics
#include:typearea
#include:ifxetex
#include:ifluatex
#include:ifpdf
#include:ifvtex

\blowUp{keyvals}

#keyvals:\blowUp
target=%<paper size%>
origin=%<paper size%>
landscape#true,false
noscale#true,false
pos=#left,right,inside,outside,top,bottom
onepage#true,false
#endkeyvals

\tPaperWidth
\tPaperHeight
\oPaperWidth
\oPaperWidth