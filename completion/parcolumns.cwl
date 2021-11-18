# parcolumns package
# Matthew Bertucci 11/17/2021 for v1.2

#include:processkv

\begin{parcolumns}{number of cols}
\begin{parcolumns}[options%keyvals]{number of cols}
\end{parcolumns}

#keyvals:\begin{parcolumns}
colwidths={%<col=width,...%>}
distance=##L
rulebetween#true,false
nofirstindent#true,false
sloppy#true,false
sloppyspaces#true,false
#endkeyvals

\colchunk{chunk%text}
\colchunk[column]{chunk%text}

\colplacechunks