# graphicx package
# mario 09/06/2007
# URL: http://tug.ctan.org/tex-archive/macros/latex/required/graphics/
\DeclareGraphicsExtensions{ext-list}
\DeclareGraphicsRule{ext}{type}{read-file}{command}
\graphicspath{dir-list}
\includegraphics*[graphicx keys]{file}
\includegraphics[graphicx keys]{file}
\reflectbox{text}
\resizebox*{h-length}{v-length}{text}
\resizebox{h-length}{v-length}{text}
\rotatebox[key val list]{angle}{text}
\scalebox{h-scale}{text}
\scalebox{h-scale}[v-scale]{text}
\setkeys{Gin}{key val}
#keyvals:\includegraphics
width=
height=
bb=
bbllx=
bbly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
angle=
origin=
trim=
viewport=
totalheight=
scale=
clip#true,false
draft#true,false
type=
ext=
read=
command=
keepaspectratio
#endkeyvals
#keyvals:\rotatebox
origin=
x=
y=
units=
#endkeyvals