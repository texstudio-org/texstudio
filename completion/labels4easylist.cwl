# labels4easylist package
# Matthew Bertucci 11/6/2021 for v1.4

#include:easylist

#keyvals:\usepackage/labels4easylist#c
pilcrow
at
sharp
ampersand
%<number of counters%>
#endkeyvals

#ifOption:ampersand
\begin{easylist}#\tabular
\begin{easylist}[style%keyvals]#\tabular
#endif

\itemLabel{label}#l
\itemLabel{label}[skipA]#l
\itemLabel{label}[skipA][skipB]#l