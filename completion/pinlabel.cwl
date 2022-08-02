# pinlabel package
# Matthew Bertucci 2022/08/01 for v1.2

#include:graphicx

\endlabellist
\hair
\hyperactivelabels#*
\labellist
\pinlabel {%<label text%>} [%<pos%>] at %<xxx yyy%>
\pinlabel {%<label text%>} at %<xxx yyy%>
\pinlabel* {%<label text%>} [%<pos%>] at %<xxx yyy%>
\pinlabel* {%<label text%>} at %<xxx yyy%>
\psfig{keyvals}
\reallyincludegraphics[options%keyvals]{imagefile}#g
\reallyincludegraphics{imagefile}#g

#keyvals:\psfig
file=%<imagefile%>
height=##L
width=##L
bbllx=##L
bblly=##L
bburx=##L
bbury=##L
rheight=
rwidth=
clip=
scale=%<factor%>
proportional=
#endkeyvals

#keyvals:\reallyincludegraphics
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

\atcatcode#S
\dvifalse#S
\dvitrue#S
\ifdvi#S
\ifoldlabels#S
\includegraphicsplain{imagefile}#Sg
\includegraphicswithoptions[options]{imagefile}#Sg
\maxheaderlines#S
\oldlabelsfalse#S
\oldlabelstrue#S
\partest#S
\psdraft#S
\psfull#S
\psnoisy#S
\pssilent#S
\setlabel*{arg1}{arg2}{arg3}{arg4}{arg5}#S
\setlabel{arg1}{arg2}{arg3}{arg4}{arg5}#S
\thelabellist#S
