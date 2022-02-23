# pst-lens package
# Matthew Bertucci 2/22/2022 for v1.02

#include:pstricks
#include:pst-grad
#include:pst-xkey

\PstLens{stuff}
\PstLens(x,y){stuff}
\PstLens[options%keyvals]{stuff}
\PstLens[options%keyvals](x,y){stuff}

#keyvals:\PstLens
LensHandle#true,false
LensStyleHandle=%<style%>
LensHandleWidth=##L
LensHandleHeight=##L
LensShadow#true,false
LensStyleGlass=%<style%>
LensSize=##L
LensMagnification=%<factor%>
LensRotation=%<degrees%>
#endkeyvals

\PstLensShape#*
\PSTLensLoaded#S
Brown#B
Salmon#B