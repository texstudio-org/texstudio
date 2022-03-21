#rotating.cwl
#for rotating package
#neeraavi 12 Apr 2007; Matthew Bertucci 29 Aug 2021 for v2.16d

#include:graphicx
#include:ifthen

#keyvals:\usepackage/rotating#c
clockwise
counterclockwise
anticlockwise
figuresleft
figuresright
quiet
log
chatter
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

\begin{sidewaystable}
\end{sidewaystable}
\begin{sidewaystable*}
\end{sidewaystable*}
\begin{sidewaysfigure}
\end{sidewaysfigure}
\begin{sidewaysfigure*}
\end{sidewaysfigure*}
\begin{sideways}
\end{sideways}
\begin{turn}{angle}
\end{turn}
\begin{rotate}{angle}
\end{rotate}
\turnbox{angle}{contents}
\rotFPtop#*
\rotFPbot#*
