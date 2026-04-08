# metaphor package
# Matthew Bertucci 2026/04/07 for v1.0

#include:imakeidx
#include:kvoptions
#include:tabularx

#keyvals:\usepackage/metaphor#c
index
indextitle=%<title%>
borders
thickness=##L
rowheight=%<factor%>
small
footnotesize
xcolor
#endkeyvals

\begin{metaphormapping}{source title%text}{target title%text}
\end{metaphormapping}

\map{source%text}{target%text}
\metaphor{text}
\metonym{text}