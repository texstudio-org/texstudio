# beamerbaseframecomponents package
# Matthew Bertucci 1/30/2022 for v3.65

\setbeamersize{options%keyvals}

#keyvals:\setbeamersize
text margin left=##L
text margin right=##L
sidebar width left=##L
sidebar width right=##L
description width=##L
description width of=%<text%>
mini frame size=##L
mini frame offset=##L
#endkeyvals

\insertpagenumber#*

\begin{columns}
\begin{columns}[options%keyvals]
\begin{columns}<overlay specification>[options%keyvals]
\end{columns}

#keyvals:\begin{columns}
b#true,false
c#true,false
onlytextwidth#true,false
t#true,false
T#true,false
totalwidth=##L
#endkeyvals

\begin{column}{column width%l}#/columns
\begin{column}[placement%keyvals]{column width%l}#/columns
\begin{column}<overlay specification>[placement%keyvals]{column width%l}#/columns
\end{column}#/columns
\column{column width%l}#/columns
\column[placement%keyvals]{column width%l}#/columns
\column<overlay specification>[placement%keyvals]{column width%l}#/columns

#keyvals:\begin{column},\column
t
T
c
b
#endkeyvals

\insertfootnotetext#*
\insertfootnotemark#*

\footnote[options%keyvals]{text}
\footnote<overlay specification>{text}
\footnote<overlay specification>[options%keyvals]{text}

#keyvals:\footnote#c
%<number%>
frame
#endkeyvals