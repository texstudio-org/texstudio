# bmpsize package
# Matthew Bertucci 1/4/2022 for v1.8

#include:iftex
#include:pdftexcmds
#include:infwarerr
#include:graphics
#include:keyval
#include:bmpsize-base

\bmpsizesetup{options%keyvals}

#keyvals:\bmpsizesetup,\includegraphics
resolutionunit=##L
defaultresolution=%<resolution%>
resolution=%<resolution%>
bmpsizefast#true,false
#endkeyvals

#keyvals:\bmpsizesetup
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
