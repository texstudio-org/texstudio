# pst-cie package
# Matthew Bertucci 2/20/2022 for v1.06b

#include:pstricks
#include:pst-plot
#include:pst-node

\psChromaticityDiagram
\psChromaticityDiagram[options%keyvals]

#keyvals:\psChromaticityDiagram
gamma=%<number%>
contrast=%<number%>
ColorSpace=#Adobe,CIE,ColorMatch,NTSC,Pal-Secam,ProPhoto,SMPTE,sRGB
datas=%<name%>
primaries#true,false
trianglecolor=#%color
bgcolor=#%color
textcolor=#%color
Planck#true,false
showcontour#true,false
Tfontsize=##L
unit=%<number%>
PSfont=%<font name%>
fontscale=%<scale in pts%>
#endkeyvals

\pstCIEcontour
\pstCIEcontour[options%keyvals]

\pstPlanck
\pstPlanck[options%keyvals]

\txCIEdictBegin#*
\CIEdefaultYear#*
\PSTcieLoaded#S