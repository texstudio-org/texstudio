# callouts package
# Matthew Bertucci 12/3/2021

#include:tikz
#include:tikzlibrarycalc
#include:xifthen
#include:kvoptions

#keyvals:\usepackage/callouts#c
bwr
wby
bww
background=#%color
arrow=#%color
#endkeyvals

\begin{annotate}{object}{width-factor}#\pictureHighlight
\end{annotate}
\helpgrid
\helpgrid[color]
\callout{center-coords}{note%text}{tip-coords}
\note{coords}{note%text}
\arrow{center-coords}{tip-coords}

\focol#*
\bgcol#*
\arcol#*
\xtic#*
\ytic#*
