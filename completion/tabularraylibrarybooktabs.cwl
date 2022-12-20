# booktabs tabularray library
# 2022/12/15 for v2022D

#include:booktabs
#include:etoolbox

\toprule
\toprule[options%keyvals]
\midrule
\midrule[options%keyvals]
\cmidrule{i-j}
\cmidrule[options%keyvals]{i-j}
\bottomrule
\bottomrule[options%keyvals]
\cmidrulemore{i-j}
\cmidrulemore[options%keyvals]{i-j}
\morecmidrules
\begin{booktabs}{preamble}#\tabular
\end{booktabs}
\begin{longtabs}{preamble}#\tabular
\end{longtabs}
\begin{talltabs}{preamble}#\tabular
\end{talltabs}
\specialrule{options%keyvals}{belowsep}{abovesep}
\addrowspace
\addrowspace[space%l]
\addlinespace
\addlinespace[space%l]