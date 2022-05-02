# expex-acro package
# Matthew Bertucci 2022/04/30 for v0.0.1

#include:expex
#include:ifthen
#include:acro
#include:xspace
#include:enumitem
# loads inline option of enumitem

\exref{tag}
\exref[tag1]{tag2}
\exrefnil{tag}
\exrefnil[tag1]{tag2}
\mexref{tag1,tag2,...}
\mexref[separator]{tag1,tag2,...}
\gl{id}
\newGlossingAbbrev{id}{long form}
\glossingAbbrevsList
\obj{text}
\qu{text}
\rc{text}
\ort{text}
\pnt{text}
\pnm{text}
\dbqu{text}
\ungr{text}
\bad{text}
\lxm{text}
\glosstilde

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}