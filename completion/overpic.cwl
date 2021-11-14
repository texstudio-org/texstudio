# overpic package
# Matthew Bertucci 11/13/2021 for v1.3

#include:graphicx
#include:epic

\begin{overpic}{imagefile}
\begin{overpic}[options%keyvals]{imagefile}
\end{overpic}

\begin{Overpic}{TeX code}
\begin{Overpic}[options%keyvals]{TeX code}
\end{Overpic}

\setOverpic{options%keyvals}

#keyvals:\begin{overpic},\begin{Overpic},\setOverpic
abs#true,false
percent#true,false
permil#true,false
rel=
grid#true,false
tics=%<number%>
unit=##L
#endkeyvals