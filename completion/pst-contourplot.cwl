# pst-contourplot package
# Matthew Bertucci 2/25/2022 for v0.6

#include:pstricks
#include:pst-xkey

\psContourPlot[function=%<function%>](%<x1,y1%>)(%<x2,y2%>)
\psContourPlot[function=%<function%>,%<options%>](%<x1,y1%>)(%<x2,y2%>)
\psContourPlot[options%keyvals](x1,y1)(x2,y2)#S

\psReadData[FileName=%<file name%>]
\psReadData[FileName=%<file name%>,%<options%>]
\psReadData[options%keyvals]#S

#keyvals:\psContourPlot#c,\psReadData#c
a=%<side length%>
ChoicePoints=%<n1 n2 ...%>
FileName=%<file name%>
grid#true,false
linecolor=#%color
linewidth=##L
ReverseColors#true,false
showpoints#true,false
unit=%<number%>
#endkeyvals

#keyvals:\psContourPlot#c
algebraic
Fill#true,false
fillcolor=#%color
function=%<function%>
WriteData#true,false
#endkeyvals

\PSTCONTOURPLOTLoaded#S