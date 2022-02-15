# epigraph-keys package
# Matthew Bertucci 9/13/2021 for v1.0

#include:enumitem
#include:pgfkeys
#include:conditionals
#include:microtype

\epigraph{text}
\epigraph[keyvals]{text}
\begin{epigraphs}
\end{epigraphs}
\qitem{text}#/epigraphs
\qitem[keyvals]{text}#/epigraphs

#keyvals:\epigraph,\qitem
author={%<author%>}
source={%<source%>}
translation={%<translation text%>}
etc={%<text%>}
after skip=##L
before skip=##L
author and source indent=##L
text indent=##L
width=##L
style=%<font commands%>
quote style=%<font commands%>
translation style=%<font commands%>
dash={%<dash code%>}
#endkeyvals

\expblank{arg}#S
\expgiven{arg}#S
\expnil{arg}#S
\beforeepigraphskip#*
\afterepigraphskip#*
\epigraphtextindent#*
\epigraphauthorsourceindent#*
\epigraphtextwidth#*
\epigraphstyle#*
\epigraphdash#*
\epigraphquotefont#*
\epigraphtranslationfont#*
