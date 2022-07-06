# thaispec package
# Matthew Bertucci 2022/07/06 for v2021.03.01

#include:kvoptions
#include:fontspec
#include:ucharclasses
#include:setspace
#include:polyglossia
#include:xstring
#include:xpatch

#keyvals:\usepackage/thaispec#c
thainum
math
thaifont=%<font name%>
sloppy#true,false
thaispacing#true,false
thaicaption#true,false
beamerthmcount#true,false
thmcount=#default,no,full,section,chapter,kind,kind-section,kind-chapter
#endkeyvals

#ifOption:math
#include:mathtools
#include:amssymb
#include:amsthm
#include:mathspec
#endif

\thaifont
\begin{thailang}
\end{thailang}
\thaialph{counter}
\thalph{number}
\thainum{counter}
\thainumber{number}
\thaidigits{arg}
\thdigits{arg}
\thaispecver#*

\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{axiom}
\begin{axiom}[heading%text]
\end{axiom}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{note}
\begin{note}[heading%text]
\end{note}