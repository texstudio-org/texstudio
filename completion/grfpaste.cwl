# grfpaste package
# Matthew Bertucci 3/21/2022 for v0.2

#include:graphicx

#keyvals:\usepackage/grfpaste#c
write
writepages
include
defpaste
# options passed to graphicx
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

#ifOption:defpaste
\paste{fragment number}{imagefile}#g
#endif

\sendout{code}
\sendout[label]{code}

#keyvals:\includegraphics
num=%<fragment number%>
ref=%<fragment label%>
natdepth=##L
#endkeyvals

\xxx#*