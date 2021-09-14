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
author=
source=
translation=
etc=
after skip=##L
before skip=##L
author and source indent=##L
text indent=##L
width=##L
style=
quote style=
translation style=
dash=
#endkeyvals