# marginalia package
# Matthew Bertucci 2026/08/10 for v0.84.1

#include:luatex

\marginalia{content%text}
\marginalia[options%keyvals]{content%text}
\marginaliasetup{options%keyvals}
\marginalianewgeometry

\marginaliapage#*
\marginaliacolumn#*

#keyvals:\marginaliasetup
binding side=#left,right
#endkeyvals

#keyvals:\marginalia,\marginaliasetup
type=#normal,fixed,optfixed
pos=#auto,reverse,outer,inner,right,left,nearest
column=#auto,one,left,right
xsep=##L
xsep outer=##L
xsep inner=##L
xsep between=##L
xsep recto outer=##L
xsep recto inner=##L
xsep verso outer=##L
xsep verso inner=##L
xsep right between=##L
xsep left between=##L
valign=#t,b,c,m
yshift=##L
ysep=##L
ysep above=##L
ysep below=##L
ysep page top=##L
ysep page top=##L
width recto right=##L
width recto left=##L
width verso right=##L
width verso left=##L
width right between=##L
width left between=##L
width recto outer=##L
width recto inner=##L
width verso outer=##L
width verso inner=##L
width=##L
width between=##L
width outer=##L
width inner=##L
style recto right=%<code%>
style recto left=%<code%>
style verso right=%<code%>
style verso left=%<code%>
style right between=%<code%>
style left between=%<code%>
style recto outer=%<code%>
style recto inner=%<code%>
style verso outer=%<code%>
style verso inner=%<code%>
style=%<code%>
mark recto right=%<code%>
mark recto left=%<code%>
mark verso right=%<code%>
mark verso left=%<code%>
mark right between=%<code%>
mark left between=%<code%>
mark recto outer=%<code%>
mark recto inner=%<code%>
mark verso outer=%<code%>
mark verso inner=%<code%>
mark=%<code%>
max problem count=%<integer%>
max item data change count=%<integer%>
max page data change count=%<integer%>
#endkeyvals
