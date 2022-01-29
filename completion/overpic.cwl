# updated 11/13/2021 for v1.3

#include:epic
#include:graphicx

\begin{overpic}{file}#\picture,pictureHighlight
\begin{overpic}[options]{file}#\picture
\begin{Overpic}{tex-code}#\picture
\begin{Overpic}[options]{tex-code}#\picture
\end{Overpic}
\end{overpic}
\setOverpic{options}

#keyvals:\begin{overpic},\begin{Overpic},\setOverpic
abs#true,false
percent#true,false
permil#true,false
rel=
grid#true,false
tics=%<number%>
unit=##L
#endkeyvals
