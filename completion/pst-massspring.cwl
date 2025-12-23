# pst-massspring package
# Matthew Bertucci 2025/12/22 for v0.01

#include:pstricks
#include:pst-xkey
#include:pst-slpe

\psSpiral(x1,y1)(x2,y2)
\psSpiral{arrows}(x1,y1)(x2,y2)
\psSpiral[options%keyvals](x1,y1)(x2,y2)
\psSpiral[options%keyvals]{arrows}(x1,y1)(x2,y2)
\psElectromagnet
\psMassSpring
\psMassSpring[options%keyvals]