# pst-electricfield package
# Matthew Bertucci 2/25/2022 for v0.13

#include:pstricks
#include:multido
#include:pst-xkey

\psElectricfield
\psElectricfield[options%keyvals]

\psEquipotential(x1,y1)(x2,y2)
\psEquipotential[options%keyvals](x1,y1)(x2,y2)

#keyvals:\psElectricfield#c,\psEquipotential#c
Q={[%<x1,y1,z1%>][%<x2,y2,z2%>]%<...%>}
N=%<integer%>
linewidth=##L
linecolor=#%color
#endkeyvals

#keyvals:\psElectricfield#c
points=%<integer%>
Pas=%<number%>
posArrow=%<factor%>
radius=##L
runit=%<number%>
#endkeyvals

#keyvals:\psEquipotential#c
Vmax=%<number%>
Vmin=%<number%>
stepV=%<number%>
stepFactor=%<factor%>
#endkeyvals

\PSTElectricFieldLoaded#S