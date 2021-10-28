# flagderiv package
# Matthew Bertucci 10/27/2021 for v0.10

#include:ifthen
#include:array
#include:longtable

\begin{flagderiv}
\begin{flagderiv}[label prefix]
\end{flagderiv}
\begin{flagderiv*}
\begin{flagderiv*}[label prefix]
\end{flagderiv*}
\introduce{label}{formula}{comment%text}#l
\assume{label}{formula}{comment%text}#l
\step{label}{formula}{comment%text}#l
\conclude{label}{formula}{comment%text}#l
\conclude[number]{label}{formula}{comment%text}#l
\introduce*{custom label}{formula}{comment%text}
\assume*{custom label}{formula}{comment%text}
\step*{custom label}{formula}{comment%text}
\conclude*{custom label}{formula}{comment%text}
\conclude*[number]{custom label}{formula}{comment%text}
\skipsteps{number}{formula}{comment%text}
\skipsteps*{formula}{comment%text}
\done
\done[number]

\derivskip#*
\introsymb#*
\thestepcount#*
\thesteplabel#*
\inlcmnts#*
\noinlcmnts#*
\theinlcmnt#*
\tablehead#*
\tablefirsthead#*
\endfoot#*
\endlastfoot#*