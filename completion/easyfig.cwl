# easyfig package
# Matthew Bertucci 12/6/2021 for v1.2a

#include:adjustbox
#include:xkeyval
#include:ifetex

\Figure{imagefile}#g
\Figure[options%keyvals]{imagefile}#g
\Figure*{imagefile}#g
\Figure*[options%keyvals]{imagefile}#g

\easyfigdefault{options%keyvals}
\easyfigdefault*{options%keyvals}

#keyvals:\Figure,\Figure*,\easyfigdefault,\easyfigdefault*
# includegraphics keys
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
# adjustbox keys
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
# figure keys
placement=%<placement chars%>
here
twocolumn#true,false
#endkeyvals
