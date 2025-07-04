# stabular package
# Matthew Bertucci 2025/06/25 for v2.3

#keyvals:\usepackage/stabular#c
array
#endkeyvals

#ifOption:array
#include:array
#endif

\begin{stabular}{cols}#\tabular
\begin{stabular}[pos]{cols}#\tabular
\end{stabular}
\begin{stabular*}{width}[pos]{cols}#\tabular
\begin{stabular*}{width}{cols}#\tabular
\end{stabular*}
