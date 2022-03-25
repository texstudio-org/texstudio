# graphicx package
# mario 09/06/2007
# muzimuzhi/10 Aug 2019 for graphicx v1.1a
# URL: http://tug.ctan.org/tex-archive/macros/latex/required/graphics/

#include:keyval
# loads graphics package but to avoid completer issues with differing syntax,
# all commands listed in graphicx.cwl rather than writing #include:graphics
#include:trig

#keyvals:\usepackage/graphicx#c
unknownkeysallowed
# options passed to graphics package
draft
final
hiresbb
demo
setpagesize
nosetpagesize
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
xetex
pdftex
luatex
dvisvgm
dvipsone
dviwindo
emtex
dviwin
oztex
textures
pctexps
pctexwin
pctexhp
pctex32
truetex
tcidvi
vtex
debugshow
hiderotate
hidescale
#endkeyvals

\DeclareGraphicsExtensions{ext-list}
\DeclareGraphicsRule{ext}{type}{read-file}{command%plain}
# use %definition so _ not marked as incorrect
\graphicspath{dir-list%definition}
\includegraphics*{imagefile}
\includegraphics*[keyvals]{imagefile}
\includegraphics{imagefile}
\includegraphics[keyvals]{imagefile}
\reflectbox{text}
\resizebox*{h-length%l}{v-length%l}{text}
\resizebox{h-length%l}{v-length%l}{text}
\rotatebox[keyvals]{angle}{text}
\rotatebox{angle}{text}
\scalebox{h-scale}{text}
\scalebox{h-scale}[v-scale]{text}

#keyvals:\includegraphics
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

#keyvals:\rotatebox
origin=
x=##L
y=##L
units=%<number%>
#endkeyvals
