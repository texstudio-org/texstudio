# returntogrid package
# Matthew Bertucci 11/19/2021 for v0.2

#include:eso-pic
#include:zref-savepos
#include:zref-abspage

\returntogrid
\returntogrid[options%keyvals]

#keyvals:\returntogrid
save=%<name%>
use=%<name%>
label=%<name%>
strut=%<integer%>
debug-vgrid#true,false
tab
tab=%<name%>
#endkeyvals

\showdebugpagegrid

\returntogridsetup{options%keyvals}

#keyvals:\returntogridsetup
active#true,false
step=##L
reference=%<point name%>
offset=##L
settabpositions={%<name%>}{%<dim-expr1,dim-expr2,...%>}
tab-list=%<name%>
hfill#true,false
twoside#true,false
debug-tab#true,false
#endkeyvals