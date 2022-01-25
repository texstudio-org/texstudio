# nccpic package
# Matthew Bertucci 1/23/2022 for v1.2

#include:graphicx
#include:nccboxes

#keyvals:\usepackage/nccpic#c
unknownkeysallowed
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

\ipic{imagefile}#g
\draftgraphics
\finalgraphics
\putimage(x,y){imagefile}#g
\putimage(x,y)[width,height]{imagefile}#g
\putimage(x,y)(xshift,yshift){imagefile}#g
\putimage(x,y)[width,height](xshift,yshift){imagefile}#g