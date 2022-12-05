# bchart package
# Matthew Bertucci 9/3/2021 for v0.1.2

#include:ifthen
#include:tikz
#include:tikzlibrarycalc

\begin{bchart}[options%keyvals]
\end{bchart}

#keyvals:\begin{bchart}
max=%<number%>
min=%<number%>
step=
steps=
plain
unit=
width=##L
scale=
#endkeyvals

\bcbar{number}#/bchart
\bcbar[options%keyvals]{number}#/bchart

#keyvals:\bcbar
text=
color=#%color
plain
value=
label=
#endkeyvals

\bcskip{length}#/bchart
\bcxlabel{label}#/bchart
\bclabel{label}#/bchart

\bcfontstyle#*
\bcpos#S
\bcwidth#S
\bcunit#S
\bcmin#S
\bcmax#S
\bcstep#S
\bcsteps#S
\bcscale#S
\bcplainchart#S
\bcbarcolor#S
\bcbartext#S
\bcbarlabel#S
\bcbarvalue#S
\bcplainbar#S
\bcskiplabel#S
\bcstripunit{arg}#S
