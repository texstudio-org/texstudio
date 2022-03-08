# pst-rubans package
# Matthew Bertucci 3/4/2022 for v1.2

#include:pstricks
#include:pst-solides3d
#include:pst-xkey

\pshelices[options%keyvals]
\pshelices[options%keyvals](x,y,z)
\psSpiralRing[options%keyvals]
\psSpiralRing[options%keyvals](x,y,z)
\psSphericalSpiral[options%keyvals]
\psSphericalSpiral[options%keyvals](x,y,z)
\psSpiralParaboloid[options%keyvals]
\psSpiralParaboloid[options%keyvals](x,y,z)
\psSpiralCone[options%keyvals]
\psSpiralCone[options%keyvals](x,y,z)

\PSTRubansLoaded#S