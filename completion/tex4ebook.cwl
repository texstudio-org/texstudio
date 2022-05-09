# tex4ebook package
# Matthew Bertucci 2022/05/09 for v0.1d

#include:etoolbox
#include:kvoptions
#include:graphicx

\coverimage{imagefile}#g
\coverimage[options%keyvals]{imagefile}#g

#keyvals:\coverimage
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

\DeclareLanguageEbook{lang name}{lang code}#*
\GetLanguage#*

\ncxtable#S
\opftable#S
\Title#S
\Author#S
\Date#S
\origdate{date}#S