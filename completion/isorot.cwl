# isorot package
# Matthew Bertucci 2/4/2022 for v2.1

#include:graphicx
#include:lscape

#keyvals:\usepackage/isorot#c
errorshow
debugshow
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
hiderotate
hidescale
#endkeyvals

\rotdriver{driver%keyvals}
#keyvals:\rotdriver#c
dvipdf
dvips
dvipsone
dvitops
dviwindo
pctex32
pctexps
pubps
textures
#endkeyvals
\clockwise
\counterclockwise
\figuresright
\figuresleft
\rotcaption
\controtcaption
\begin{sideways}
\end{sideways}
\begin{turn}{angle}
\end{turn}
\begin{rotate}{angle}
\end{rotate}
\begin{sidewaystable}
\end{sidewaystable}
\begin{sidewaystable*}
\end{sidewaystable*}
\begin{sidewaysfigure}
\end{sidewaysfigure}
\begin{sidewaysfigure*}
\end{sidewaysfigure*}
\rotcapfont#*

# not documented
\rotatedirection{direction}#*
\turnbox{angle}{content%text}#*
\therpage#*