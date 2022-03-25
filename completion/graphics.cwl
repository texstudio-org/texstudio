# graphics package
# Matthew Bertucci 3/22/2022 for v1.4e

#include:trig

#keyvals:\usepackage/graphics#c
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
\includegraphics{imagefile}#g
\includegraphics[llx,lly]{imagefile}#g
\includegraphics[llx,lly][urx,ury]{imagefile}#g
\includegraphics*{imagefile}#g
\includegraphics*[llx,lly]{imagefile}#g
\includegraphics*[llx,lly][urx,ury]{imagefile}#g
\reflectbox{text}
\resizebox{h-length%l}{v-length%l}{text}
\resizebox*{h-length%l}{v-length%l}{text}
\rotatebox{angle}{text}
\scalebox{h-scale}{text}
\scalebox{h-scale}[v-scale]{text}
\GDebug{text}#S