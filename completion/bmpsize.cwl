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
alt=
bb=
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
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
scale=
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
#endkeyvals