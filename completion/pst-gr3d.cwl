# pst-gr3d package
# Matthew Bertucci 2/25/2022 for v1.34

#include:pstricks
#include:pst-node
#include:pst-3d
#include:multido
#include:pst-xkey

\PstGridThreeD(x,y,z)
\PstGridThreeD[options%keyvals](x,y,z)

\PstGridThreeDYFace{arg1}{arg2}{arg3}#*
\PstGridThreeDHookNode#*
\PstGridThreeDHookXFace#*
\PstGridThreeDHookYFace#*
\PstGridThreeDHookZFace#*
\PstGridThreeDHookEnd#*

\PstGridThreeDNodeProcessor{color}

\PSTGridThreeDLoaded#S