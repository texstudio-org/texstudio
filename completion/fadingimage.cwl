# fadingimage package
# Matthew Bertucci 2024/03/17 for v0.1d

#include:tikz
#include:xcolor
#include:tikzlibraryfadings

\UPFadingImage{imagefile}#g
\UPFadingImage[options%keyvals]{imagefile}#g
\UPFadingImage*{imagefile}#g
\UPFadingImage*[options%keyvals]{imagefile}#g
\LOWFadingImage{imagefile}#g
\LOWFadingImage[options%keyvals]{imagefile}#g
\LOWFadingImage*{imagefile}#g
\LOWFadingImage*[options%keyvals]{imagefile}#g
\UPLOWFadingImage{imagefile}{imagefile}#g
\UPLOWFadingImage[options%keyvals]{imagefile}{imagefile}#*g
\UPLOWFadingImage{imagefile}[options]{imagefile}#*g
\UPLOWFadingImage[options%keyvals]{imagefile}[options]{imagefile}#g
\UPLOWFadingImage*{imagefile}{imagefile}#g
\UPLOWFadingImage*[options%keyvals]{imagefile}{imagefile}#*g
\UPLOWFadingImage*{imagefile}[options]{imagefile}#*g
\UPLOWFadingImage*[options%keyvals]{imagefile}[options]{imagefile}#g

#keyvals:\UPFadingImage,\UPFadingImage*,\LOWFadingImage,\LOWFadingImage*,\UPLOWFadingImage,\UPLOWFadingImage*
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