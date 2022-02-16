# ditaa package
# Matthew Bertucci 2/15/2022 for v0.01

#include:fancyvrb
#include:graphicx
#include:kvoptions

#keyvals:\usepackage/ditaa#c
imagepath=%<path%>
#endkeyvals

\begin{ditaa}{caption%text}{name}
\begin{ditaa}[width]{caption%text}{name}
\end{ditaa}

\ditaacaption#*
\ditaadir#*
\ditaafigwidth#*
\ditaafile#*
\ditaastem#*