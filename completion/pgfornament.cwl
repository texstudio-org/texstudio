# pgfornament package
# Matthew Bertucci 6/21/2021

#include:tikz

\newpgfornamentfamily{keyvals}
\begin{newfamily}[keyvals]
\end{newfamily}

#keyvals:\newpgfornamentfamily,\begin{newfamily}
pgfhan
vectorian
#endkeyvals

\pgfornament[keyvals]{ornament number}#/tikzpicture
\pgfornamentline[keyvals]{point1}{point2}{number}{ornament number}

#keyvals:\pgfornament#c,\pgfornamentline#c
scale=
width=##L
height=##L
color=#%color
opacity=
ydelta=##L
symmetry=#v,h,c,none
anchor=
#endkeyvals

\pgfornamentscale#*/tikzpicture
\pgfornamentydelta#*/tikzpicture
\pgfornamentanchor#*/tikzpicture

\resetpgfornamentstyle#*/tikzpicture

\getornamentlength#*/tikzpicture