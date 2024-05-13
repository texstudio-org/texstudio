# fadingimage package
# Matthew Bertucci 2024/05/13 for v0.3a

#include:tikz
#include:tikzlibraryfadings

\UPFadingImage{imagefile}#g
\UPFadingImage[options%keyvals]{imagefile}#g
\UPFadingImage*{imagefile}#g
\UPFadingImage*[options%keyvals]{imagefile}#g
\LOWFadingImage{imagefile}#g
\LOWFadingImage[options%keyvals]{imagefile}#g
\LOWFadingImage*{imagefile}#g
\LOWFadingImage*[options%keyvals]{imagefile}#g
\LTFadingImage{imagefile}#g
\LTFadingImage[options%keyvals]{imagefile}#g
\LTFadingImage*{imagefile}#g
\LTFadingImage*[options%keyvals]{imagefile}#g
\RITFadingImage{imagefile}#g
\RITFadingImage[options%keyvals]{imagefile}#g
\RITFadingImage*{imagefile}#g
\RITFadingImage*[options%keyvals]{imagefile}#g

#keyvals:\UPFadingImage,\UPFadingImage*,\LOWFadingImage,\LOWFadingImage*,\LTFadingImage,\LTFadingImage*,\RITFadingImage,\RITFadingImage*
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
