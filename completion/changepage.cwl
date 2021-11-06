# changepage package
# Matthew Bertucci 11/3/2021 for v1.0c

\ifstrictpagecheck#*
\strictpagecheckfalse#*
\strictpagechecktrue#*

\strictpagecheck
\easypagecheck

\ifoddpage#*
\oddpagefalse#*
\oddpagetrue#*
\cplabel#*

\pmemlabel{label}#*l
\newpmemlabel{label}{page num}#*l
\pmemlabelref{label}#*r

\checkoddpage

\changetext{textheight%l}{textwidth%l}{evenmargin%l}{oddmargin%l}{colsep%l}
\changepage{textheight%l}{textwidth%l}{evenmargin%l}{oddmargin%l}{colsep%l}{topmargin%l}{headheight%l}{headsep%l}{footskip%l}

\begin{adjustwidth}{leftmargin%l}{rightmargin%l}
\end{adjustwidth}
\begin{adjustwidth*}{leftmargin%l}{rightmargin%l}
\end{adjustwidth*}