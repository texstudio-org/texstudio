# multicoltab package
# Matthew Bertucci 2026/09/11 for v0.8

#include:array
#include:tabularx
#include:keyval

\begin{multicoltab}{preamble}#\tabular
\begin{multicoltab}[options%keyvals]{preamble}#\tabular
\end{multicoltab}

#keyvals:\begin{multicoltab}
width=##L
row-sep=##L
break-penalty=%<integer%>
natural-widths=#local,global
#endkeyvals

\mchead{cells%text}#t
\mchead[before%text]{cells%text}#t
\mchead[before%text][after%text]{cells%text}#t
\multicoltabbreak#t
\multicoltabpagebreak#t
\mcheadrepeat#t