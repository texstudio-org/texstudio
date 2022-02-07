# graphviz package
# Matthew Bertucci 2/5/2022 for v0.94

#include:graphicx

#keyvals:\usepackage/graphviz#c
singlefile
psfrag
ps
pdf
tmpdir
#endkeyvals

#ifOption:psfrag
#include:psfrag
#endif

\digraph{name}{graph}
\digraph[options%keyvals]{name}{graph}
\neatograph{name}{graph}
\neatograph[options%keyvals]{name}{graph}
\inputdigraph{name}{graph}{type}#*
\inputdigraph[options%keyvals]{name}{graph}{type}#*

#keyvals:\digraph,\neatograph,\inputdigraph
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

\ifsinglefile#*
\singlefiletrue#*
\singlefilefalse#*
\ifpsfrag#*
\psfragtrue#*
\psfragfalse#*