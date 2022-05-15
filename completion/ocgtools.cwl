# ocgtools package
# Matthew Bertucci 2022/05/14 for v0.95a

#include:color
#include:hyperref
#include:graphicx
#include:pifont
#include:ocg
#include:xkeyval
#include:atbegshi
#include:eforms

#keyvals:\usepackage/ocgtools#c
transparent
insertvisible
nobutton
noprogressmsg
minimouseover
mouseover
nopageclose
inactive
noocg
active
fixcolor
#endkeyvals

#ifOption:transparent
#include:transparent
#endif

\ocgtext{text1%text}{text2%text}
\ocgtext[options%keyvals]{text1%text}{text2%text}
ocgpaper#B
ocgfontcolor#B
\defaultocgpapercolor#*
\defaultocgfontcolor#*
\ocgpicture{imagefile}#g
\ocgpicture[options%keyvals]{imagefile}#g
\ocgminitext{text1%text}{text2%text}
\ocgminitext[options%keyvals]{text1%text}{text2%text}
\ocgminitextrt{text1%text}{text2%text}
\ocgminitextrt[options%keyvals]{text1%text}{text2%text}
\ocgminitextrb{text1%text}{text2%text}
\ocgminitextrb[options%keyvals]{text1%text}{text2%text}
\ocgminitextlt{text1%text}{text2%text}
\ocgminitextlt[options%keyvals]{text1%text}{text2%text}
\ocgminitextlb{text1%text}{text2%text}
\ocgminitextlb[options%keyvals]{text1%text}{text2%text}
\ocgtextstart#*
\ocgtextend#*
ocgbg#B
\layerHshift#*
\layerVshift#*
\ocgclosechar#*

#keyvals:\ocgtext#c,\ocgminitext#c,\ocgminitextrt#c,\ocgminitextrb#c,\ocgminitextlt#c,\ocgminitextlb#c
width=##L
%<width%>
bg=#%color
fg=#%color
#endkeyvals

#keyvals:\ocgpicture
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