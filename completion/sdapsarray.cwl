# sdapsarray package
# Matthew Bertucci 12/18/2021 for v0.1

#include:sdapsbase

\begin{sdapsarray}#\tabular
\begin{sdapsarray}[options%keyvals]#\tabular
\end{sdapsarray}

#keyvals:\begin{sdapsarray}
flip#true,false
layouter=#default,rotated
angle=%<angle%>
align=%<string%>
keepenv
no_header#true,false
colsep=##L
rowsep=##L
#endkeyvals

\sdapsnested{content%text}