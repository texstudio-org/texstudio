# dijkstra package
# Matthew Bertucci 10/11/2021 for v0.12

#include:simplekv

\readgraph{graph specs}
\readgraph*{graph specs}

\dijkstra{vertex1}{vertex2}
\dijkstra[options%keyvals]{vertex1}{vertex2}
\setdijk{options%keyvals}
\setdijkdefault{options%keyvals}

#keyvals:\dijkstra,\setdijk,\setdijkdefault
show-tab#true,false
v-position=
pre-tab=%<code%>
post-tab=%<code%>
col-type=
infinity-code=%<code%>
norevisit-code=%<code%>
h-rules#true,false
show-lastcol#true,false
lastcol-type=
lastcol-label=
nopath-string=
path-sep=
#endkeyvals

\dijkdist
\dijkpath
\initdijk

\formatnodewithprev{arg1}{arg2}#*
\highlightfistnode{arg}#*
\highlightnode{arg1}{arg2}#*
\dijkname#S
\dijkver#S
\dijkdate#S