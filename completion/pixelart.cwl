# pixelart package
# Matthew Bertucci 12/14/2021 for v0.2.0

#include:pgf
#include:pgfopts
#include:tikz
#include:pgfkeys
#include:etoolbox
# loads the parser pgfmodule and calc tikzlibrary

#keyvals:\usepackage/pixelart#c
draft
#endkeyvals

\bwpixelart{pixels}
\bwpixelart[options%keyvals]{pixels}

#keyvals:\bwpixelart
color=#%color
scale=%<factor%>
raise=##L
#endkeyvals

\tikzbwpixelart{pixels}
\tikzbwpixelart[options%keyvals]{pixels}

#keyvals:\tikzbwpixelart
color=#%color
scale=%<factor%>
#endkeyvals