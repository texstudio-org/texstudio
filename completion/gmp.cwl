# gmp package
# Matthew Bertucci 2/8/2022 for v1.0

#include:xkeyval
#include:graphicx
#include:ifpdf
#include:ifxetex
#include:environ

\gmpoptions{options%keyvals}

#keyvals:\usepackage/gmp#c,\gmpoptions
tex
latex
noshellescape
shellescape
nowrite
write
envname=%<envname%>
extension=%<extension%>
everymp={%<metapost code%>}
clean=#none,aux,mp
rmcommand=%<cmd%>
postrmcommand=%<cmd%>
#endkeyvals

\usempxclass{class}
\usempxclass[options]{class}
\usempxpackage{package}#u
\usempxpackage[options]{package}#u
\resetmpxpackages
\mpxcommands{commands}
\resetmpxcommands
\mpdim{dimen param}
\usempost{string}
\usempost[options]{string}
#keyvals:\usempost
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
\begin{mpost}
\begin{mpost}[options%keyvals]
\end{mpost}
\begin{mpost*}
\begin{mpost*}[options%keyvals]
\end{mpost*}
#keyvals:\begin{mpost},\begin{mpost*}
name=%<string%>
use#true,false
mpmem=%<metapost format%>
mpxprogram=#tex,latex
mpxcommands=%<commands%>
mpsettings={%<metapost code%>}
runs=%<number%>
#endkeyvals
\btex
\verbatimtex