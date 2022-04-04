# twemojis package
# Matthew Bertucci 3/31/2022 for v1.3.1

#include:tikz
#include:ifthen

\twemoji{emoji name}
\twemoji[options%keyvals]{emoji name}
\texttwemoji{emoji name}

#keyvals:\twemoji
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

\twemojiDefaultHeight#*
\defineTwemoji{number}{name}#*