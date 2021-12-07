# storebox package
# Matthew Bertucci 12/6/2021 for v1.3a

#include:ifpdf
#include:collectbox

\newstorebox{boxname%cmd}#d
\storebox{boxname}{content%text}
\begin{storebox}{boxname}
\end{storebox}
\usestorebox{boxname}
\ifstorebox#*
\endstorebox#S