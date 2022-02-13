# pgfornament package
# Matthew Bertucci 2/12/2022 for v1.2

#include:tikz
#include:pgfopts

#keyvals:\usepackage/pgfornament#c
object=#vectorian,pgfhan
#endkeyvals

\newpgfornamentfamily{family%keyvals}
\begin{newfamily}[family%keyvals]
\end{newfamily}

#keyvals:\newpgfornamentfamily,\begin{newfamily}
pgfhan
vectorian
#endkeyvals

\pgfornament{ornament number}
\pgfornament[options%keyvals]{ornament number}
\pgfornamentline{point1}{point2}{number}{ornament number}
\pgfornamentline[options%keyvals]{point1}{point2}{number}{ornament number}

#keyvals:\pgfornament#c,\pgfornamentline#c
scale=%<factor%>
width=##L
height=##L
color=#%color
opacity=%<factor%>
ydelta=##L
symmetry=#v,h,c,none
anchor=%<anchor%>
#endkeyvals

\pgfornamenthline{anchor1}{anchor2}{direction}{ornament number}#*
\pgfornamentvline{anchor1}{anchor2}{direction}{ornament number}#*
\getornamentlength{anchor1}{anchor2}{direction}{ornament number}#*
\resetpgfornamentstyle#*
\callornament{file}#*

\pgfornamentscale#*
\pgfornamentwidth#*
\pgfornamentheight#*
\pgfornamentcolor#*
\pgfornamentopacity#*
\pgfornamentanchor#*
\pgfornamentydelta#*
\ornamenttopos#*
\ornamenttoanchor#*
\ornamenttosymmetry#*
\ornamentlen#*
\nbo#S
\pgfOrnamentsObject#*
\OrnamentsFamily#*
\SavedOrnamentsFamily#*
