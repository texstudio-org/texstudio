# egplot package
# Matthew Bertucci 2/22/2022 for v1.02a

#include:graphicx
#include:ifthen
#include:verbatim

#keyvals:\usepackage/egplot#c
german
gnuplot35
gnuplot36beta
# options passed to graphicx
unknownkeysallowed
draft
final
hiresbb
demo
setpagesize
nosetpagesize
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
xetex
pdftex
luatex
dvisvgm
dvipsone
dviwindo
emtex
dviwin
oztex
textures
pctexps
pctexwin
pctexhp
pctex32
truetex
tcidvi
vtex
debugshow
hiderotate
hidescale
#endkeyvals

\begin{egpfile}
\begin{egpfile}[gnuplot file%file]
\end{egpfile}
\begin{egpcmds}
\end{egpcmds}
\egpwrite{gnuplot code%definition}
\egpprelude{gnuplot prelude%definition}
\egpaddtoprelude{gnuplot code%definition}

\begin{egp}
\begin{egp}[name]
\end{egp}
\begin{egpx}{keyvals}
\begin{egpx}[name]{keyvals}
\end{egpx}
\begin{egpdef}{name}
\end{egpdef}
\egpuse{name}
\egpuse[keyvals]{name}

#keyvals:\begin{egpx},\egpuse
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
#endkeyvals

\egpfigprelude{gnuplot prelude%definition}
\egpaddtofigprelude{gnuplot code%definition}
\egpfigepilog{gnuplot epilog%definition}
\egpaddtofigepilog{gnuplot code%definition}

\egpcalc{gnuplot expr%definition}
\egpcalc[name%definition]{gnuplot expr%definition}
\egpuseval{name%definition}
\egpshowval{gnuplot expr%definition}
\egpshowval[name%definition]{gnuplot expr%definition}
\egpassign{variable%definition}{gnuplot expr%definition}

\theegpcalc#*
\theegpfig#*
\theegpfile#*
\theegpfilename#*
\theegpfilenum#*
\egpcomment#*

\egpfile#S
\egpfile[gnuplot file%file]#S
\endegpfile#S
\egpcmds#S
\endegpcmds#S
\egp#S
\egp[name]#S
\endegp#S
\egpx{keyvals}#S
\egpx[name]{keyvals}#S
\endegpx#S
\egpdef{name}#S
\endegpdef#S
\filedate#S
\filemaintainer#S
\filename#S
\fileversion#S
