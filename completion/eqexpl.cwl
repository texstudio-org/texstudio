# eqexpl package
# Matthew Bertucci 12/14/2021 for v1.1

#include:calc
#include:etoolbox

\begin{eqexpl}
\begin{eqexpl}[width]
\end{eqexpl}

\eqexplSetSpace{space%l}
\eqexplSetIntro{text}
\eqexplSetDelim{symbol}
\eqexplSetItemWidth{width}
\eqexplSetItemAlign{align%keyvals}
#keyvals:\eqexplSetItemAlign
l
c
r
#endkeyvals
\item{label}
\item{label}[symbol]

\eqexplDelim#*
\eqexplIntro#*
\eqexplItemAlign#*
\eqexplItemWidth#*
\eqexplSpaceWidth#*
\itemWidth#*
\leftSideWidth#*
\olditem#S