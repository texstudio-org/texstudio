# pst-magneticfield package
# Matthew Bertucci 2/22/2022 for v1.16

#include:pstricks
#include:pst-3d
#include:multido
#include:pst-node
#include:pst-arrow
#include:pst-xkey

\psmagneticfield(x1,y1)(x2,y2)
\psmagneticfield[options%keyvals](x1,y1)(x2,y2)
\psmagneticfieldThreeD(x1,y1)(x2,y2)
\psmagneticfieldThreeD[options%keyvals](x1,y1)(x2,y2)

#keyvals:\psmagneticfield#c,\psmagneticfieldThreeD#c
R=%<number%>
N=%<number%>
L=%<number%>
nL=%<integer%>
numSpires=
pointsB=%<integer%>
pointsS=%<integer%>
PasB=%<number%>
PasS=%<number%>
nS=%<integer%>
styleSpire=%<style%>
styleCourant=%<style%>
drawSelf#true,false
AntiHelmholtz#true,false
StreamDensityPlot#true,false
setgray#true,false
changeNS#true,false
linecolor=#%color
#endkeyvals

\psBarMagnet
\psBarMagnet(x,y)
\psBarMagnet[options%keyvals]
\psBarMagnet[options%keyvals](x,y)

#keyvals:\psBarMagnet#c
rot=%<degrees%>
showField#true,false
showPoleLabels#true,false
fontstyle=%<font commands%>
magnetScale=%<factor%>
#endkeyvals

\CalcIntermediaire#S
\yA#S
\PSTMagneticFieldLoaded#S