# incgraph package
# muzimuzhi,31 Jul 2020 for incgraph 1.12

#include:pgfkeys
#include:pgf
#include:pgffor
#include:graphicx
#include:bookmark

\incgraph{imagefile}
\incgraph[options%keyvals]{imagefile}
\incgraph[options%keyvals][graphics options]{imagefile}
\incmultigraph{file name pattern}{list}
\incmultigraph[options%keyvals]{file name pattern}{list}
\incmultigraph[options%keyvals][graphics options]{file name pattern}{list}
\begin{inctext}
\begin{inctext}[options%keyvals]
\end{inctext}
\igrset{options%keyvals}

#keyvals:\incgraph,\incmultigraph,\begin{inctext},\igrset
currentpaper
documentpaper
graphicspaper
paper size=%<width%>:%<height%>
paper=#current,document,graphics,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,d0,d1,d2,d3,d4,d5,d6,d7,landscape
portrait
a0paper
a1paper
a2paper
a3paper
a4paper
a5paper
a6paper
a7paper
a8paper
a9paper
a10paper
b0paper
b1paper
b2paper
b3paper
b4paper
b5paper
b6paper
b7paper
b8paper
b9paper
b10paper
c0paper
c1paper
c2paper
c3paper
c4paper
c5paper
c6paper
c7paper
c8paper
c9paper
c10paper
d0paper
d1paper
d2paper
d3paper
d4paper
d5paper
d6paper
d7paper
executivepaper
letterpaper
legalpeper
ledgerpaper
center
page
options={%<graphics options%>}
options add={%<graphics options%>}
include command=%<macro%>
existence check=%<macro%>
fail on not found
ignore on not found
hyper
no hyper
target=%<hyperref anchor%>
label=##l
bookmark=
bookmark options=
bookmark heading=
bookmark heading options=
left border=##L
bottom border=##L
right border=##L
top border=##L
horizontal border=##L
vertical border=##L
border=##L
set matches={%<list%>}
if match code={%<key%>}{%<then%>}{%<else%>}
if match set={%<key%>}{%<then%>}{%<else%>}
if match set bookmark={%<key%>}{%<then%>}{%<else%>}
disable match
overlay={%<tikz code%>}
overlay page number at=%<position%>
overlay page number at bottom=##L
overlay page number at top=##L
no overlay
pagestyle=%<page style%>
zerofill=%<digits%>
#endkeyvals

\igfpage{text}
\igrcenter{text}
\igrcenterfit{width}{height}{text}
\igrtargetset{hyperref anchor}

\igfboxset{text}
\igrboxcenter
\igrboxtikz
\igrboxtikzpage
\igfboxtikzcenter

\igrsetmatchvalue{key%plain}{value}
\igrsetmatches{list}
\igrifmatch{key%plain}{then}{else}
\igrmakezerofill{macro}{digits}
