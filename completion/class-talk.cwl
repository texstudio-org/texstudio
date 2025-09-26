# talk class
# Matthew Bertucci 2025/09/26 for v2.0

#include:multido
#include:graphicx
#include:pgf
#include:xstring
#include:environ

#keyvals:\documentclass/talk#c
notes
slides
screen
rotate
norotate
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\title[short title%text]{text}
\author[short author]{names}

\begin{slide}{title%text}
\begin{slide}[style%keyvals]{title%text}
\end{slide}

\slidesmag{factor}

\begin{notes}
\end{notes}

\layout{style%keyvals}

\begin{multislide}{sub-slides}{title%text}
\begin{multislide}[style%keyvals]{sub-slides}{title%text}
\end{multislide}

\fromslide{slide number}{material%text}
\fromslide*{slide number}{material%text}
\toslide{slide number}{material%text}
\toslide*{slide number}{material%text}
\onlyslide{slide number}{material%text}
\onlyslide*{slide number}{material%text}

\shiftbox{x}{y}{material%text}
\shiftbox[anchor]{x}{y}{material%text}
\twocolumn{valign}{left-material%text}{right-material%text}
\twocolumn[fraction]{valign}{left-material%text}{right-material%text}

\tableofcontents[%<<fromsec>.<fromsubsec>-<tosec>.<tosubsec>%>]

\slidewidth#*
\slideheight#*
\theslide#*
\thesubslide#*
\theHsubslide#*
\theslidelabel#*

\slidesadjust{hadjust}{vadjust}#*
\setparskip{glue}#*
