# slides class
# Matthew Bertucci 2022/02/12 for release 2021/10/04

#keyvals:\documentclass/slides#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
clock
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
#endkeyvals

\theminutes#*
\theseconds#*
\settime{seconds}
\addtime{seconds}

\ifourteenpt#*
\iseventeenpt#*
\itwentypt#*
\itwentyfourpt#*
\itwentyninept#*
\ithirtyfourpt#*
\ifortyonept#*

\newifG%<\ifmacro%>#*
\newifG{cmd}#Sd

\theslide#*
\theoverlay#*
\thenote#*

\onlyslides{list}
\onlynotes{list}

\begin{slide}
\end{slide}
\begin{overlay}
\end{overlay}
\begin{note}
\end{note}

\invisible
\visible