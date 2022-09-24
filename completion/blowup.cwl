# blowup package
# Matthew Bertucci 2022/09/24 for v2.1.0

#include:atbegshi
#include:keyval
#include:graphics
#include:typearea
#include:iftex

\blowUp{keyvals}

#keyvals:\blowUp
target=%<paper size%>
origin=%<paper size%>
h-mirroring#true,false
v-mirroring#true,false
landscape#true,false
noscale#true,false
pos=#left,right,inside,outside,top,bottom
onepage#true,false
#endkeyvals

\tPaperWidth#*
\tPaperHeight#*
\oPaperWidth#*
\oPaperWidth#*
