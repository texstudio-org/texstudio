# pst-intersect package
# Matthew Bertucci 2/26/2022 for v0.4

#include:pstricks
#include:pst-xkey
#include:pst-node
#include:pst-func

\pssavepath{name}{commands}
\pssavepath[options%keyvals]{name}{commands}
\pssavebezier{%<name%>}(%<x0,y0%>)(%<x1,y1%>)%<...(xN,yN)%>
\pssavebezier[%<options%>]{%<name%>}(%<x0,y0%>)(%<x1,y1%>)%<...(xN,yN)%>
\psintersect{curveA}{curveB}
\psintersect[options%keyvals]{curveA}{curveB}
\pstracecurve{curve name}
\pstracecurve{intersection}{curve name}
\pstracecurve[options%keyvals]{curve name}
\pstracecurve[options%keyvals]{intersection}{curve name}
\psGetCurvePoint{curve name}{macro%cmd}#d
\psGetIsectCenter{intersection}{curve name}{macro%cmd}#d
\PSTintersectLoaded#S