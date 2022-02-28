# pst-ob3d package
# Matthew Bertucci 2/23/2022 for v0.22

#include:pstricks
#include:pst-xkey
#include:pst-3d
#include:pst-tools

\PstCube{x length}{y length}{z length}
\PstCube[options%keyvals]{x length}{y length}{z length}

\PstDie
\PstDie[options%keyvals]

\PstObjectsThreeDFaceA#*
\PstObjectsThreeDFaceB#*
\PstObjectsThreeDFaceC#*
\PstObjectsThreeDFaceD#*
\PstObjectsThreeDFaceE#*
\PstObjectsThreeDFaceF#*
\PstObjectsThreeDFaceCenterA#*
\PstObjectsThreeDFaceCenterB#*
\PstObjectsThreeDFaceCenterC#*
\PstObjectsThreeDFaceCenterD#*
\PstObjectsThreeDFaceCenterE#*
\PstObjectsThreeDFaceCenterF#*
\PstObjectsThreeDLoaded#S