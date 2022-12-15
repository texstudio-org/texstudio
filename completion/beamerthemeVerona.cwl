# Verona beamertheme
# Matthew Bertucci 2/10/2022 for v0.2

#include:tikz
#include:tcolorbox
#include:tcolorboxlibraryskins

#keyvals:\usetheme/Verona#c
showheader
red
gray
colorblocks
graytitle
sidebar
noframetitlerule
#endkeyvals

Veronagreen#B
Veronablue#B
Veronaorange#B
Veronared#B
Veronagray#B
Veronagrayblue#B
Veronagraygreen#B

\lecturename#*
\begin{citazione}#*
\begin{citazione}<action specification>#*
\begin{citazione}[author%text]#*
\begin{citazione}<action specification>[author%text]#*
\end{citazione}#*
\begin{quotation}[author%text]
\begin{quotation}<action specification>[author%text]
\autorecitazione#*
\structureA#*
\structureB#*
\oldtitlegraphic#S

\titlegraphic{imagefile}{TikZ options}#g
\titlegraphic[options%keyvals]{imagefile}{TikZ options}#g

#ifOption:sidebar
\sidegraphics{imagefile}{TikZ options}#g
\sidegraphics[options%keyvals]{imagefile}{TikZ options}#g
\sidegraphics<overlay specification>{imagefile}{TikZ options}#g
\sidegraphics<overlay specification>[options%keyvals]{imagefile}{TikZ options}#g
#endif

#keyvals:\titlegraphic,\sidegraphics
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

\lectureinfoot#*
\frametitlesidebar#*
\mail{address%text}
\datelecture#*
