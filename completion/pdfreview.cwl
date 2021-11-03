# pdfreview package
# Matthew Bertucci 11/2/2021 for v1.20

#include:adjustbox
#include:calc
#include:environ
#include:etoolbox
#include:fp
#include:graphicx
#include:kvoptions
#include:tikz
#include:twoopt
#include:xstring
#include:grffile
#include:ulem
#include:hyperref
#include:bookmark
#include:geometry

\note{height}{text}
\note[alignment%keyvals]{height}{text}
#keyvals:\note
b
c
t
#endkeyvals
\bnote{height}{text}
\cnote{height}{text}
\tnote{height}{text}
\sourcedoc{file}
\pagegrid
\pagegrid[TikZ settings]
\pagegrid[TikZ settings][steps]

\begin{page}{page number}
\begin{page}[options%keyvals]{page number}
\end{page}

#keyvals:\begin{page}
bb=
bbllx=##L
bblly=##L
bburx=##L
bbury=##L
natwidth=##L
natheight=##L
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=
trim=
angle=
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=
ext=
read=
command=
quiet
page=
interpolate#true,false
decodearray=
intent
maskarray
ocobjnum
ocobjref
resetcolor
resolution
xmpfile
Trim=
Viewport=
Clip=
Clip*=
rndcorners=
margin=
margin*=
padding=
padding*=
vspace=
vspace*=
min width=##L
max width=##L
min height=##L
max height=##L
min totalheight=##L
max totalheight=##L
min size={%<width%>}{%<height%>}
max size={%<width%>}{%<height%>}
min totalsize={%<width%>}{%<totalheight%>}
max totalsize={%<width%>}{%<totalheight%>}
warn width
warn width=##L
scale={%<h-factor%>}{%<v-factor%>}
reflect
fbox
fbox=
frame
frame=
cfbox=
cframe=
rndframe=
color=#%color
color*=%<color cmd%>
sep=##L
rndcornersbox
rndfbox
valign=#T,M,B,t,m,b
raise=
set height=##L
set depth=##L
set vsize={%<height%>}{%<depth%>}
center
center=##L
right
right=##L
left
left=##L
inner
inner=##L
outer
outer=##L
pagecenter
pagecenter=##L
pageleftalign
pageleftalign=##L
pagerightalign
pagerightalign=##L
pageinner
pageinner=##L
pageouter
pageouter=##L
textareacenter
textareacenter=##L
textarealeftalign
textarealeftalign=##L
textarearightalign
textarearightalign=##L
textareainner
textareainner=##L
textareaouter
textareaouter=##L
noindent
leavevmode
lap=
rlap
llap
clap
color=
color*=%<color macro%>
fgcolor=
fgcolor*=%<color macro%>
bgcolor=
bgcolor*=%<color macro%>
bgimage=
bgimage*=
fgimage=
fgimage*=
background=
background*=
foreground=
foreground*=
dpi=%<number%>
pxdim=##L
minipage=
varwidth=##L
tabular=[%<position%>]{%<col spec%>}
tabular*=[%<position%>]{%<width%>}{%<col spec%>}
array=[%<position%>]{%<col spec%>}
stack
stack=
innerenv=%<envname%>
innercode={%<begin code%>}{%<end code%>}
caption=
captionabove=
captionbelow=
label=##l
figure
figure=%<placement%>
float=
nofloat=%<float type%>
rotate=
env=
addcode={%<code before%>}{%<code after%>}
Addcode={%<code before%>}{%<code after%>}
appcode=%<code after%>
precode=%<code before%>
Precode={%<code before%>}
execute=%<code%>
Execute=%<code%>
phantom
phantom=#h,v
gobble
discard
content=%<new content%>
gstore=%<box register%>
gstore*=%<box register%>
gstore width=%<length register%>
gstore height=%<length register%>
gstore depth=%<length register%>
gstore totalheight=%<length register%>
gstore sizes=
process
#endkeyvals

\begin{leftnotes}
\end{leftnotes}
\begin{rightnotes}
\end{rightnotes}
\begin{insertpage}
\begin{insertpage}[heading]
\end{insertpage}
