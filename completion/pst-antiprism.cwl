# pst-antiprism package
# Matthew Bertucci 2/25/2022 for v0.02

#include:pstricks
#include:pst-solides3d
#include:pst-xkey

\psAntiprism
\psAntiprism[options%keyvals]

#keyvals:\psAntiprism#c
a=%<radius%>
action=#none,draw,draw*,draw**,writesolid,writeobj,writeoff
affinage=#0,1,2,3,all
affinagecoeff=%<factor%>
affinagerm
colored#true,false
deactivatecolor
fan#true,false
fillcolor=#%color
hollow#true,false
hue=%<hue spec%>
incolor=#%color
inouthue=%<hue spec%>
linecolor=#%color
linewidth=##L
meshbases#true,false
n=%<number of edges%>
name=%<name%>
numfaces=#0,1,2,3,all,%<PS code%>
opacity=%<factor%>
plansepare={[%<a b c d%>]}
rm=
#endkeyvals

\PSTANTIPRISMLoaded#S