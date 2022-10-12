# chemobabel package
# Matthew Bertucci 2022/10/10 for v0.9k

#include:verbatim
#include:graphicx

#keyvals:\usepackage/chemobabel#c
extract
pdf
eps
inkscape-old
inkscape
librsvg
nocrop
#endkeyvals

\chemobabel{imagefile}{obabel options}#g
\chemobabel[options%keyvals]{imagefile}{obabel options}#g
\chemobabel*{imagefile}#g
\chemobabel*[options%keyvals]{imagefile}#g
\smilesobabel{SMILES notation%definition}{obabel options}
\smilesobabel[options%keyvals]{SMILES notation%definition}{obabel options}
\smilesobabel*{SMILES notation%definition}
\smilesobabel*[options%keyvals]{SMILES notation%definition}

#keyvals:\chemobabel,\chemobabel*,\smilesobabel,\smilesobabel*
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

\chemobabelimgdir#*
