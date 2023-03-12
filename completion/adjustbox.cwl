# adjustbox package
# Matthew Bertucci 10/5/2021 for v1.3

#include:trimclip
#include:ifoddpage
#include:varwidth

#keyvals:\usepackage/adjustbox#c
export
Export
pgf
PGF
minimal
etex
calc
pgfmath
defaultunit=%<unit%>
pdftex
luatex
dvips
xetex
dvipdfm
dvipdfmx
#endkeyvals

#ifOption:pgf
#include:pgf
#endif

#ifOption:PGF
#include:pgf
#endif

#ifOption:calc
#include:calc
#endif

#ifOption:pgfmath
#include:pgf
#endif

\adjustbox{options%keyvals}{content%text}
\begin{adjustbox}{options%keyvals}
\end{adjustbox}
\adjustimage{options%keyvals}{imagefile}#g
\adjincludegraphics[options%keyvals]{imagefile}#g

\newadjustboxenv{envname}{options%keyvals}#*N
\newadjustboxenv{envname}[num][default]{options%keyvals}#*N
\newadjustboxenv*{envname}{options%keyvals}#*N
\newadjustboxenv*{envname}[num][default]{options%keyvals}#*N
\renewadjustboxenv{envname}{options%keyvals}#*
\renewadjustboxenv{envname}[num][default]{options%keyvals}#*
\renewadjustboxenv*{envname}{options%keyvals}#*
\renewadjustboxenv*{envname}[num][default]{options%keyvals}#*
\provideadjustboxenv{envname}{options%keyvals}#*N
\provideadjustboxenv{envname}[num][default]{options%keyvals}#*N
\provideadjustboxenv*{envname}{options%keyvals}#*N
\provideadjustboxenv*{envname}[num][default]{options%keyvals}#*N
\declareadjustboxenv{envname}{options%keyvals}#*N
\declareadjustboxenv{envname}[num][default]{options%keyvals}#*N
\declareadjustboxenv*{envname}{options%keyvals}#*N
\declareadjustboxenv*{envname}[num][default]{options%keyvals}#*N
\newadjustboxcmd{cmd}{options%keyvals}#*d
\newadjustboxcmd{cmd}[num][default]{options%keyvals}#*d
\renewadjustboxcmd{cmd}{options%keyvals}#*
\renewadjustboxcmd{cmd}[num][default]{options%keyvals}#*
\provideadjustboxcmd{cmd}{options%keyvals}#*d
\provideadjustboxcmd{cmd}[num][default]{options%keyvals}#*d
\declareadjustboxcmd{cmd}{options%keyvals}#*d
\declareadjustboxcmd{cmd}[num][default]{options%keyvals}#*d
\newadjustimage{cmd}{options%keyvals}#*d
\newadjustimage{cmd}[num][default]{options%keyvals}#*d
\renewadjustimage{cmd}{options%keyvals}#*
\renewadjustimage{cmd}[num][default]{options%keyvals}#*
\provideadjustimage{cmd}{options%keyvals}#*d
\provideadjustimage{cmd}[num][default]{options%keyvals}#*d
\declareadjustimage{cmd}{options%keyvals}#*d
\declareadjustimage{cmd}[num][default]{options%keyvals}#*d
\NewAdjustImage{cmd}{xargs}{options%keyvals}#*d
\RenewAdjustImage{cmd}{xargs}{options%keyvals}#*
\ProvideAdjustImage{cmd}{xargs}{options%keyvals}#*d
\DeclareAdjustImage{cmd}{xargs}{options%keyvals}#*d

\adjustboxset{options%keyvals}
\adjustboxset*{options%keyvals}

\bgimagebox{imagefile}#*g
\bgimagebox[options%keyvals]{imagefile}#*g
\bgimagebox*{imagefile}#*g
\bgimagebox*[options%keyvals]{imagefile}#*g
\begin{bgimagebox}{imagefile}#*g
\begin{bgimagebox}[options%keyvals]{imagefile}#*g
\end{bgimagebox}#*
\begin{bgimagebox*}{imagefile}#*g
\begin{bgimagebox*}[options%keyvals]{imagefile}#*g
\end{bgimagebox*}#*
\fgimagebox{imagefile}#*g
\fgimagebox[options%keyvals]{imagefile}#*g
\fgimagebox*{imagefile}#*g
\fgimagebox*[options%keyvals]{imagefile}#*g
\begin{fgimagebox}{imagefile}#*g
\begin{fgimagebox}[options%keyvals]{imagefile}#*g
\end{fgimagebox}#*
\begin{fgimagebox*}{imagefile}#*g
\begin{fgimagebox*}[options%keyvals]{imagefile}#*g
\end{fgimagebox*}#*

\backgroundbox{content%text}#*
\backgroundbox[options%keyvals]{content%text}#*
\backgroundbox*{content%text}#*
\backgroundbox*[options%keyvals]{content%text}#*
\begin{backgroundbox}{content%text}#*
\begin{backgroundbox}[options%keyvals]{content%text}#*
\end{backgroundbox}#*
\begin{backgroundbox*}{content%text}#*
\begin{backgroundbox*}[options%keyvals]{content%text}#*
\end{backgroundbox*}#*
\foregroundbox{content%text}#*
\foregroundbox[options%keyvals]{content%text}#*
\foregroundbox*{content%text}#*
\foregroundbox*[options%keyvals]{content%text}#*
\begin{foregroundbox}{content%text}#*
\begin{foregroundbox}[options%keyvals]{content%text}#*
\end{foregroundbox}#*
\begin{foregroundbox*}{content%text}#*
\begin{foregroundbox*}[options%keyvals]{content%text}#*
\end{foregroundbox*}#*

### \includegraphics keys
#keyvals:\adjustbox,\begin{adjustbox},\adjustimage,\adjincludegraphics,\newadjustboxenv,\newadjustboxenv*,\renewadjustboxenv,\renewadjustboxenv*,\provideadjustboxenv,\provideadjustboxenv*,\declareadjustboxenv,\declareadjustboxenv*,\newadjustboxcmd,\renewadjustboxcmd,\provideadjustboxcmd,\declareadjustboxcmd,\newadjustimage,\renewadjustimage,\provideadjustimage,\declareadjustimage,\NewAdjustImage,\RenewAdjustImage,\ProvideAdjustImage,\DeclareAdjustImage,\bgimagebox,\bgimagebox*,\begin{bgimagebox},\begin{bgimagebox*},\fgimagebox,\fgimagebox*,\begin{fgimagebox},\begin{fgimagebox*},\backgroundbox,\backgroundbox*,\begin{backgroundbox},\begin{backgroundbox*},\foregroundbox,\foregroundbox*,\begin{foregroundbox},\begin{foregroundbox*}
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
intent
maskarray
ocobjnum
ocobjref
resetcolor
resolution
xmpfile
#endkeyvals

### \adjustbox specific keys
#keyvals:\adjustbox,\begin{adjustbox},\adjustimage,\adjincludegraphics,\newadjustboxenv,\newadjustboxenv*,\renewadjustboxenv,\renewadjustboxenv*,\provideadjustboxenv,\provideadjustboxenv*,\declareadjustboxenv,\declareadjustboxenv*,\newadjustboxcmd,\renewadjustboxcmd,\provideadjustboxcmd,\declareadjustboxcmd,\newadjustimage,\renewadjustimage,\provideadjustimage,\declareadjustimage,\NewAdjustImage,\RenewAdjustImage,\ProvideAdjustImage,\DeclareAdjustImage,\bgimagebox,\bgimagebox*,\begin{bgimagebox},\begin{bgimagebox*},\fgimagebox,\fgimagebox*,\begin{fgimagebox},\begin{fgimagebox*},\backgroundbox,\backgroundbox*,\begin{backgroundbox},\begin{backgroundbox*},\foregroundbox,\foregroundbox*,\begin{foregroundbox},\begin{foregroundbox*}
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

#ifOption:export
#keyvals:\includegraphics
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
#endif

#ifOption:Export
#keyvals:\includegraphics
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
#endif

\Width#*
\Height#*
\Depth#*
\Totalheight#*
\smallestside
\largestside
\Smallestside#*
\Largestside#*

\minsizebox{width}{height}{content%text}#*
\minsizebox*{width}{totalheight%l}{content%text}#*
\maxsizebox{width}{height}{content%text}#*
\maxsizebox*{width}{totalheight%l}{content%text}#*

\rndcornersbox{length}{content%text}#*
\rndframebox{length}{content%text}#*
\rndfbox{length}{content%text}#*

\adjboxvtop#*
\adjboxvbottom#*
\adjboxvcenter#*

\centerbox{content%text}#*
\centerbox[width]{content%text}#*
\begin{centerbox}#*
\begin{centerbox}[width]#*
\end{centerbox}#*
\leftalignbox{content%text}#*
\leftalignbox[width]{content%text}#*
\begin{leftalignbox}#*
\begin{leftalignbox}[width]#*
\end{leftalignbox}#*
\rightalignbox{content%text}#*
\rightalignbox[width]{content%text}#*
\begin{rightalignbox}#*
\begin{rightalignbox}[width]#*
\end{rightalignbox}#*
\innersidebox{content%text}#*
\innersidebox[width]{content%text}#*
\begin{innersidebox}#*
\begin{innersidebox}[width]#*
\end{innersidebox}#*
\outersidebox{content%text}#*
\outersidebox[width]{content%text}#*
\begin{outersidebox}#*
\begin{outersidebox}[width]#*
\end{outersidebox}#*
\centerpagebox{content%text}#*
\centerpagebox[width]{content%text}#*
\begin{centerpagebox}#*
\begin{centerpagebox}[width]#*
\end{centerpagebox}#*
\pagecenterbox{content%text}#*
\pagecenterbox[width]{content%text}#*
\begin{pagecenterbox}#*
\begin{pagecenterbox}[width]#*
\end{pagecenterbox}#*
\pageleftalignbox{content%text}#*
\pageleftalignbox[width]{content%text}#*
\begin{pageleftalignbox}#*
\begin{pageleftalignbox}[width]#*
\end{pageleftalignbox}#*
\pagerightalignbox{content%text}#*
\pagerightalignbox[width]{content%text}#*
\begin{pagerightalignbox}#*
\begin{pagerightalignbox}[width]#*
\end{pagerightalignbox}#*
\pageinnerbox{content%text}#*
\pageinnerbox[width]{content%text}#*
\begin{pageinnerbox}#*
\begin{pageinnerbox}[width]#*
\end{pageinnerbox}#*
\pageouterbox{content%text}#*
\pageouterbox[width]{content%text}#*
\begin{pageouterbox}#*
\begin{pageouterbox}[width]#*
\end{pageouterbox}#*
\textareacenterbox{content%text}#*
\textareacenterbox[width]{content%text}#*
\begin{textareacenterbox}#*
\begin{textareacenterbox}[width]#*
\end{textareacenterbox}#*
\textarealeftalignbox{content%text}#*
\textarealeftalignbox[width]{content%text}#*
\begin{textarealeftalignbox}#*
\begin{textarealeftalignbox}[width]#*
\end{textarealeftalignbox}#*
\textarearightalignbox{content%text}#*
\textarearightalignbox[width]{content%text}#*
\begin{textarearightalignbox}#*
\begin{textarearightalignbox}[width]#*
\end{textarearightalignbox}#*
\textareainnerbox{content%text}#*
\textareainnerbox[width]{content%text}#*
\begin{textareainnerbox}#*
\begin{textareainnerbox}[width]#*
\end{textareainnerbox}#*
\textareaouterbox{content%text}#*
\textareaouterbox[width]{content%text}#*
\begin{textareaouterbox}#*
\begin{textareaouterbox}[width]#*
\end{textareaouterbox}#*

\lapbox{length}{content%text}#*
\lapbox[width]{length}{content%text}#*

\bgcolorbox{color}#*
\bgcolorbox[model]{color}#*
\bgcolorbox*{color macro}#*
\begin{bgcolorbox}{color}#*
\begin{bgcolorbox}[model]{color}#*
\end{bgcolorbox}#*
\begin{bgcolorbox*}{color mcro}#*
\end{bgcolorbox*}#*

\pwidth#*
\pheight#*
\pdepth#*
\ptotalheight#*

\pdfpxdimen#*

\stackbox{content%text}#*
\stackbox[halign]{content%text}#*
\stackbox[halign][valign]{content%text}#*
\begin{stackbox}#*
\begin{stackbox}[halign]#*
\begin{stackbox}[halign][valign]#*
\end{stackbox}#*

\begin{adjnofloat}{float type}#*
\end{adjnofloat}#*
\adjnofloat#*
\endadjnofloat#*

\phantombox{width}{height}{depth}#*

\newadjustboxkey{keyname}{code}#*
\newadjustboxkey{keyname}[default]{code}#*
\newadjustboxkey*{keyname}{code}#*
\newadjustboxkey*{keyname}[default]{code}#*
\renewadjustboxkey{keyname}{code}#*
\renewadjustboxkey{keyname}[default]{code}#*
\renewadjustboxkey*{keyname}{code}#*
\renewadjustboxkey*{keyname}[default]{code}#*
\provideadjustboxkey{keyname}{code}#*
\provideadjustboxkey{keyname}[default]{code}#*
\provideadjustboxkey*{keyname}{code}#*
\provideadjustboxkey*{keyname}[default]{code}#*
\defadjustboxkey{keyname}{code}#*
\defadjustboxkey{keyname}[default]{code}#*
\defadjustboxkey*{keyname}{code}#*
\defadjustboxkey*{keyname}[default]{code}#*
