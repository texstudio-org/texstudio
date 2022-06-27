# combinedgraphics package
# Matthew Bertucci 2022/06/25 for v0.2.2

#include:keyval
#include:graphicx
#include:color

#keyvals:\usepackage/combinedgraphics#c
textfontcmd=%<font csname%>
textcolorcmd=%<color csname%>
vecscale=%<factor%>
vecwidth=##L
vecheight=##L
vecinclude=%<file name%>
vecfirst#true,false
#endkeyvals

\includecombinedgraphics{file}#i
\includecombinedgraphics[options%keyvals]{file}#i

#keyvals:\includecombinedgraphics
textfont=%<font commands%>
textcolor=%<color commands%>
vecscale=%<factor%>
vecwidth=##L
vecheight=##L
vecinclude=#auto,true,false,overwrite
vecfirst#true,false
vecfile=%<file name%>
angle=%<degrees%>
origin=
x=
y=
units=
scale=%<factor%>
hscale=%<factor%>
vscale=%<factor%>
height=##L
totalheight=##L
width=##L
keepaspectratio
#endkeyvals