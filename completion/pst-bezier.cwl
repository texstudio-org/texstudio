# pst-bezier package
# Matthew Bertucci 2/26/2022 for v0.03

#include:pstricks
#include:pst-xkey
#include:pst-plot
#include:pst-node

\psbcurve(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\psbcurve[%<options%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>

#keyvals:\psbcurve
bcurveTension=%<value%>
dash=%<a b%>
fillcolor=#%color
fillstyle=%<style%>
linecolor=#%color
linestyle=%<style%>
linewidth=##L
showpoints#true,false
#endkeyvals

\psRQBCmasse(x0,y0)(x1,y1)(x2,y2){w0,w1,w2}
\psRQBCmasse[options%keyvals](x0,y0)(x1,y1)(x2,y2){w0,w1,w2}

#keyvals:\psRQBCmasse
autoTrace#true,false
linecolor=#%color
linewidth=##L
nPoints=%<number%>
showpoints#true,false
showPolygon#true,false
#endkeyvals

\pscalculate{expr%definition}#*
\PSTbezierLoaded#S
\defopt{macro%cmd}{default}[optargs]args{definition}#*d