# pst-mirror package
# Matthew Bertucci 2/25/2022 for v1.02

#include:pstricks
#include:pst-node
#include:pst-tools
#include:multido
#include:pst-xkey

\pstSphereText(x,y,z){text}
\pstSphereText[options%keyvals](x,y,z){text}
\pstSphereCube
\pstSphereDie
\pstSphereTetraedre
\pstSpherePoint(x,y,z){node name}
\NormalIIIDCoor#*
\pstSphereLine(%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstSphereLine[%<options%>](%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstSpherePolygon(%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstSpherePolygon[%<options%>](%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstSphereCircle{radius}
\pstSphereCircle[options%keyvals]{radius}
\pstSphereArc{radius}{angle min}{angle max}
\pstSphereArc[options%keyvals]{radius}{angle min}{angle max}
\pstSphereFrame(x1,y1)(x2,y2)
\pstSphereFrame[options%keyvals](x1,y1)(x2,y2)
\pstSphereGrid(x,y,z)
\pstSphereGrid[options%keyvals](x,y,z)
\pstMirrorSphere{radius}
\pstSphereCylinder{radius}{height}
\pstSphereCylinder[options%keyvals]{radius}{height}
\pstSphereCone{radius}{height}
\pstSphereCone[options%keyvals]{radius}{height}
\pstSpherePyramide
\pstSphereImage(x,y,z){imagefile}#g
\pstSphereImage[options%keyvals](x,y,z){imagefile}#g
\parametricplotSphere{x0}{x1}{function%definition}
\parametricplotSphere{x0}{x1}[PS code]{function%definition}
\parametricplotSphere[options%keyvals]{x0}{x1}{function%definition}
\parametricplotSphere[options%keyvals]{x0}{x1}[PS code]{function%definition}

# not documented
\pstFaceSAB#*
\pstFaceSAB[options%keyvals]#*
\pstFaceSBC#*
\pstFaceSBC[options%keyvals]#*
\pstFaceSCD#*
\pstFaceSCD[options%keyvals]#*
\pstFaceSDA#*
\pstFaceSDA[options%keyvals]#*
\pstFaceABCD#*
\pstFaceABCD[options%keyvals]#*
\PSTMirrorLoaded#S
Beige#B
GrisClair#B
GrisTresClair#B
OrangeTresPale#B
OrangePale#B
BleuClair#B
LightBlue#B
DarkGreen#B
Copper#B

# compatibility
\psparametricplotSphere{x0}{x1}{function%definition}#S
\psparametricplotSphere{x0}{x1}[PS code]{function%definition}#S
\psparametricplotSphere[options%keyvals]{x0}{x1}{function%definition}#S
\psparametricplotSphere[options%keyvals]{x0}{x1}[PS code]{function%definition}#S