# threeparttablex package
# Matthew Bertucci 10/24/2021 for v0.3

#include:threeparttable
#include:environ

#keyvals:\usepackage/threeparttablex#c
referable
# options passed to threeparttable
para
flushleft
online
normal
#endkeyvals

\begin{ThreePartTable}
\end{ThreePartTable}
\begin{TableNotes}
\end{TableNotes}
\insertTableNotes#t

#ifOption:referable
\tnotex{label}#r
\tnotex*{label}#*r
\setTableNoteFont{font cmds}
\note#/tablenotes,TableNotes
\source#/tablenotes,TableNotes
\TPTLnotename#*
\TPTLsourcename#*
\TPTLnotesnamefontcommand#*
#endif
