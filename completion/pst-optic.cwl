# pst-optic package
# Matthew Bertucci 2/25/2022 for v1.02

#include:pstricks
#include:pst-node
#include:pst-plot
#include:pst-3d
#include:pst-grad
#include:pst-math
#include:multido
#include:pst-xkey

\resetOpticOptions
\lens
\lens[options%keyvals]
\lensCVG
\lensDVG
\Transform
\rayInterLens(start node)(intermediate node)(lens distance){lens node}
\telescope
\telescope[options%keyvals]
\mirrorCVG
\mirrorCVG[options%keyvals]
\mirrorDVG
\mirrorDVG[options%keyvals]
\mirrorCVGRay(node1)(node2){mirror node}
\mirrorCVGRay[options%keyvals](node1)(node2){mirror node}
\mirrorDVGRay(node1)(node2){mirror node}
\mirrorDVGRay[options%keyvals](node1)(node2){mirror node}
\planMirrorRay(mirror begin)(mirror end)(original point){new point}
\symPlan(node1)(node2){stuff}
\beamLight
\beamLight[options%keyvals]
\refractionRay(A)(B)(C)(D){n1}{n2}{end node}
\psprism
\psprism[options%keyvals]
\lensSPH
\lensSPH[options%keyvals]
\mirrorCVG
\mirrorCVG[options%keyvals]
\mirrorDVG
\mirrorDVG[options%keyvals]
\ABinterSPHLens(A)(B)(center){name}
\lensSPHRay(A)(B){refractA}{refractB}{node name}
\lensSPHRay[options%keyvals](A)(B){refractA}{refractB}{node name}
\reflectionRay(A)(B){node name}
\reflectionRay[options%keyvals](A)(B){node name}
\eye
\Arrows(nodeA)(nodeB)
\Arrows[options%keyvals](nodeA)(nodeB)
\psOutLine(nodeA)(nodeB){end node}
\psOutLine[options%keyvals](nodeA)(nodeB){end node}
\psBeforeLine(nodeA)(nodeB){start node}
\psBeforeLine[options%keyvals](nodeA)(nodeB){start node}
\Parallel(nodeA)(nodeB)(start node){end node}
\Parallel[options%keyvals](nodeA)(nodeB)(start node){end node}
\ABinterCD(A)(B)(C)(D){E}
\nodeBetween(A)(B){C}
\rotateNode{node name}{degrees}
\rotateTriangle{nodeA}{nodeB}{nodeC}{degrees}
\rotateFrame{nodeA}{nodeB}{nodeC}{nodeD}{degrees}
\arrowLine(start)(end){arrow number}
\arrowLine[options%keyvals](start)(end){arrow number}
\mirrorTwo

# not documented
\pslensDVG{width}{height}#*
\pslensCVG{width}{height}#*
\lensTypeCVG#*
\lensTypeDVG#*
\lensTypePCVG#*
\lensTypePDVG#*
\mirrorType#*
\psprismColor#*
\PSTopticLoaded#S