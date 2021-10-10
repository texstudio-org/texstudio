# graphicx package
# mario 09/06/2007
# muzimuzhi/10 Aug 2019 for graphicx v1.1a
# URL: http://tug.ctan.org/tex-archive/macros/latex/required/graphics/

#include:keyval

\DeclareGraphicsExtensions{ext-list}
\DeclareGraphicsRule{ext}{type}{read-file}{command%plain}
\graphicspath{dir-list}
\includegraphics*{imagefile}
\includegraphics*[keyvals]{imagefile}
\includegraphics{imagefile}
\includegraphics[keyvals]{imagefile}
\reflectbox{text}
\resizebox*{h-length}{v-length}{text}
\resizebox{h-length}{v-length}{text}
\rotatebox[keyvals]{angle}{text}
\rotatebox{angle}{text}
\scalebox{h-scale}{text}
\scalebox{h-scale}[v-scale]{text}

#keyvals:\includegraphics
bb=
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=
trim=
angle=
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=
clip#true,false
draft#true,false
type=
ext=
read=
command=
quiet
page=
interpolate#true,false
decodearray=
#endkeyvals

#keyvals:\rotatebox
origin=
x=
y=
units=
#endkeyvals
