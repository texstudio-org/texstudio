# storebox package
# Matthew Bertucci 12/6/2021 for v1.3a

#include:ifpdf
#include:collectbox

#keyvals:\usepackage/storebox#c
disable
enable
immediate
delayed
#endkeyvals

\newstorebox{boxname%cmd}#d
\storebox{boxname}{content%text}
\begin{storebox}{boxname}
\end{storebox}
\usestorebox{boxname}
\ifstorebox#*
\endstorebox#S
