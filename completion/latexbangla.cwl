# latexbangla package
# Matthew Bertucci 2022/06/20 for v0.2

#include:xetex
#include:polyglossia
#include:fontspec
#include:xkeyval
#include:ifxetex
#include:ucharclasses
#include:titlesec
#include:amsthm
#include:xpatch
#include:amsfonts
#include:amssymb
#include:amsmath
#include:enumerate
#include:chngcntr
#include:hyperref

#keyvals:\usepackage/latexbangla#c
banglamainfont=%<font name%>
banglattfont=%<font name%>
feature=#0,1,2
changecounternumbering=
#endkeyvals

#ifOption:feature=2
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{property}
\begin{property}[heading%text]
\end{property}
\begin{hint}
\begin{hint}[heading%text]
\end{hint}
\begin{remarks}
\begin{remarks}[heading%text]
\end{remarks}
\begin{motive}
\end{motive}
\thecorollary#*
\theproperty#*
#endif

\tobangla{counter}
\numtobangla{number}

\begin{solution}
\end{solution}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{problem}
\begin{problem}[heading%text]
\end{problem}
\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\thetheorem#*
\theexample#*
\theproblem#*

\bengalifont#*
\bengalifonttt#*
\begin{latin}#*
\end{latin}#*