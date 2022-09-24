# blowup package
# Matthew Bertucci 2022/09/21 for v2.0.0

#include:atbegshi
#include:keyval
#include:graphics
#include:typearea
#include:iftex

\blowUp{keyvals}

#keyvals:\blowUp
target=%<paper size%>
origin=%<paper size%>
landscape#true,false
noscale#true,false
pos=#left,right,inside,outside,top,bottom
onepage#true,false
#endkeyvals

\tPaperWidth#*
\tPaperHeight#*
\oPaperWidth#*
\oPaperWidth#*
