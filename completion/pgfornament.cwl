# pgfornament package
# Matthew Bertucci 9/17/2021 for v1.2

#include:tikz

\newpgfornamentfamily{family%keyvals}
\begin{newfamily}[family%keyvals]
\end{newfamily}

#keyvals:\newpgfornamentfamily,\begin{newfamily}
pgfhan
vectorian
#endkeyvals

\pgfornament{ornament number}#/tikzpicture
\pgfornament[options%keyvals]{ornament number}#/tikzpicture
\pgfornamentline{point1}{point2}{number}{ornament number}
\pgfornamentline[options%keyvals]{point1}{point2}{number}{ornament number}

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
