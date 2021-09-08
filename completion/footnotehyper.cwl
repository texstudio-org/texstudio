# footnotehyper package
# Matthew Bertucci 9/7/2021 for v1.1e

#include:expl3
#include:xparse

\begin{savenotes}
\end{savenotes}
\savenotes#*
\spewnotes#*
\begin{footnote}
\begin{footnote}[number]
\end{footnote}
\begin{footnotetext}
\end{footnotetext}
\makesavenoteenv{environment}#*
\makesavenoteenv[new_envname%envname]{environment}#*N
\footnotehyperwarnfalse#*