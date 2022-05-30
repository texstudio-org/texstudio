# aeb_tilebg package
# Matthew Bertucci 2022/05/10 for v1.2

#include:graphicx
#include:multido

#keyvals:\usepackage/aeb_tilebg#c
uselltiling
draft
ignoreforpaper
#endkeyvals

\setTileBgGraphic{imagefile}#g
\setTileBgGraphic[options%keyvals]{imagefile}#g

#keyvals:\setTileBgGraphic
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
# graphicxsp options
name=%<name%>
transparency={%<specs%>}
presp={%<PS code%>}
postsp={%<PS code%>}
#endkeyvals

\disableTiling
\enableTiling
\maxiterations{number}
\autosetScreensizeWithMargins{rows}{cols}{left}{right}{top}{bottom}

\placeTilesinLayers{keyvals}
\placeTilesinLayers[name]{keyvals}

# not documented
\theReqHeight#*
\theReqWidth#*
\tileboxheight#*
\tileboxwidth#*
\tileheight#*
\tilewidth#*
\turnOffTiling#*