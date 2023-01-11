# xistercian package
# Matthew Bertucci 12/22/2021 for v1.2

#include:pgf
#include:expkv-opt

\cistercian{counter}
\cisterciannum{integer}
\cisterciannumE{integer expression}
\cisterciansetup{options%keyvals}
\cistercianredraw#*
\cistercianredrawlazy#*
\cistercianstyle{keyname%specialDef}{options%keyvals}#s#%cisterciankey
\cistercianstyle*{keyname%specialDef}{options%keyvals}#s#%cisterciankey

#keyvals:\cisterciansetup,\cistercianstyle,\cistercianstyle*,\usepackage/xistercian#c
width=##L
wd=##L
height=##L
ht=##L
bound-x=%<factor%>
bx=%<factor%>
bound-y=%<factor%>
by=%<factor%>
baseline=%<factor%>
bs=%<factor%>
stroke-v=##L
sv=##L
stroke-h=##L
sh=##L
stroke-du=##L
sdu=##L
stroke-dd=##L
sdd=##L
strokes=##L
s=##L
fraction=%<fraction%>
fr=%<fraction%>
orientation=#horizontal,h,vertical,v
o=#horizontal,h,vertical,v
horizontal
vertical
alternate-5=%<choice%>
5=%<choice%>
alternate-6=%<choice%>
6=%<choice%>
alternate-9=%<choice%>
9=%<choice%>
font={%<font setup%>}
f={%<font setup%>}
%cisterciankey
#endkeyvals

#keyvals:\cisterciansetup,\cistercianstyle,\cistercianstyle*
redraw={%<feature list%>}
redraw +={%<feature list%>}
redraw
redraw!
r={%<feature list%>}
r +={%<feature list%>}
r
r!
#endkeyvals

#keyvals:\usepackage/xistercian#c
debug
#endkeyvals
