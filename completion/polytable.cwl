# polytable package
# Matthew Bertucci 4/15/2022 for v0.8.6

#include:lazylist
#include:array

#keyvals:\usepackage/polytable#c
debug
info
silent
defaultcolumns
memory
#endkeyvals

\nodefaultcolumn
\defaultcolumn{colspec}

\begin{pboxed}
\end{pboxed}
\begin{ptboxed}
\end{ptboxed}
\begin{pmboxed}#m
\end{pmboxed}#m

\column{column id}{spec}
\column[dimen%l]{column id}{spec}
\={from id}
\={from id}[spec]
\>
\>[from id]
\>[from id][spec]
\<
\<[from id]
\fromto{from id}{to id}{text}

\savecolumns
\savecolumns[set id]
\restorecolumns
\restorecolumns[set id]

\beginpolytable#*
\disktables#*
\maxcolumn#*
\memorytables#*

# deprecated
\begin{ptabular}#*
\end{ptabular}#*
\begin{parray}#*m
\end{parray}#*m
\nextline#*
\nextline[dimen%l]#*