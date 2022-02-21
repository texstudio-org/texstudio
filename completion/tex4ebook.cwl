# tex4ebook package
# Matthew Bertucci 2/20/2022 for v0.1d

#include:etoolbox
#include:graphicx
#include:kvoptions

\Author
\Date
\DeclareLanguageEbook{language}{lang code}
\GetLanguage
\Title
\title[short title]{text}
\author[short author]{name}
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
\ncxtable#*
\opftable#*
\origdate{date}#*