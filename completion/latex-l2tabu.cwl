# latex mode: LaTeX commands (l2tabu level)
# commands that shall not be used for reasons documented in l2tabu.pdf
# dani/2006-02-18
# muzimuzhi/2026-10-04

# there is no \begin{appendix} env, only \appendix cmd
\begin{appendix}
\begin{eqnarray}#\math,array
\begin{eqnarray*}#\math,array
\begin{sloppypar}
\end{appendix}
\end{eqnarray}
\end{eqnarray*}
\end{sloppypar}
\centerline{text}
\sloppy
