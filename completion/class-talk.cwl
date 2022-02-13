# talk class
# Matthew Bertucci 2/12/2022 for v1.1

#include:multido
#include:amsmath
#include:graphicx
#include:pgf
#include:hyperref

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

\slidestyle{style%keyvals}

\begin{multislide}{sub-slides}{title%text}
\begin{multislide}[style%keyvals]{sub-slides}{title%text}
\end{multislide}

\fromslide{slide number}{material%text}
\fromslide*{slide number}{material%text}
\toslide{slide number}{material%text}
\toslide*{slide number}{material%text}
\onlyslide{slide number}{material%text}
\onlyslide*{slide number}{material%text}

\tableofcontents[%<<fromsec>.<fromsubsec>-<tosec>.<tosubsec>%>]

\slidewidth#*
\slideheight#*
\theslide#*
\thesubslide#*
\theslidelabel#*
\slidesadjust{hadjust}{vadjust}#*