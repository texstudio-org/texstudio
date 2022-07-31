# stex-tikzinput package
# Matthew Bertucci 2022/07/30 for v3.1.0

#include:stex
#include:tikzinput

\mhtikzinput{file}#i
\mhtikzinput[options%keyvals]{file}#i
\cmhtikzinput{file}#i
\cmhtikzinput[options%keyvals]{file}#i
\libusetikzlibrary{library}

#keyvals:\mhtikzinput,\cmhtikzinput
mhrepos=%<file path%>
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