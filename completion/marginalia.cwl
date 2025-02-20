# marginalia package
# Matthew Bertucci 2025/02/18 for v0.80.1

#include:luatex

\marginalia{content%text}
\marginalia[options%keyvals]{content%text}
\marginaliasetup{options%keyvals}
\marginalianewgeometry

\marginaliapage#*
\marginaliacolumn#*

#keyvals:\marginalia,\marginaliasetup
type=#normal,fixed,optfixed
pos=#auto,reverse,left,right,nearest
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
valign=#t,b
yshift=##L
ysep=##L
ysep above=##L
ysep below=##L
ysep page top=##L
ysep page top=##L
width=##L
width outer=##L
width inner=##L
width between=##L
width recto outer=##L
width recto inner=##L
width verso outer=##L
width verso inner=##L
width right between=##L
width left between=##L
style=%<code%>
style recto outer=%<code%>
style recto inner=%<code%>
style verso outer=%<code%>
style verso inner=%<code%>
style right between=%<code%>
style left between=%<code%>

#endkeyvals
















