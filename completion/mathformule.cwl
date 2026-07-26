# mathformule package
# Matthew Bertucci 2026/07/26 for v0.6

#keyvals:\usepackage/mathformule#c
section
chapter
#endkeyvals

\begin{formule}#\math,array
\begin{formule}[options%keyvals]#\math,array
\end{formule}

#keyvals:\begin{formule}#c
lineskip=##L
lbrace
lbrace=%<code%>
rbrace
rbrace=%<code%>
lbraceskip=##L
rbraceskip=##L
multnum
multnum=%<type%>
#endkeyvals

\formuleskip{skip}
\mathformulenumberwithin{counter}
\notag#m

\mathformulelineskip#*
\mathformulerowautorefname#*
\themathformulerow#S