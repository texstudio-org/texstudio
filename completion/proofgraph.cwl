# proofgraph package
# Matthew Bertucci 2026/06/03 for v1.0.0

#include:amsthm
#include:etoolbox
#include:xstring
#include:kvoptions

#keyvals:\usepackage/proofgraph#c
autorun#true,false
cite#true,false
citelabel=#key,tag
direction=#usedby,uses
engine=%<engine%>
file=%<file name%>
format=%<format%>
hyperlinks#true,false
rankdir=%<direction%>
selfloops=#remove,keep
#endkeyvals

\proofgraph
\proofgraph[options%keyvals]
\proofgraphedge{result}{label1,label2,...}
\proofgraphexclude{label}
\proofgraphignore{from}{to}
\proofgraphstylecite{attributes}
\proofgraphstyle{style}{attributes}
\proofgraphtrack{names}
\proofgraphuntrack{names}
\proofof{label%plain}
\uses{label1,label2,...}

#keyvals:\proofgraph
actualtext={%<text%>}
alt={%<alt text%>}
artifact#true,false
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

# not documented
\pgphnodemap{arg1}{arg2}#S
\pgphnodemapcite{arg1}{arg2}#S


