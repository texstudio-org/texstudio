# Amurmaple beamertheme
# Matthew Bertucci 2024/02/07 for v1.3

#include:multicol
#include:iftex
#include:pgfpages
#include:fontawesome5
#include:luamesh
#include:tcolorbox
#include:tcolorboxlibraryskins
#include:tikzlibrarybackgrounds
#include:tikzlibraryquotes
#include:tikzlibraryangles
#include:tikzlibraryautomata
#include:tikzlibrarycalc

#keyvals:\usetheme/Amurmaple#c
nogauge
nomail
delaunay
amurmapleblue
amurmaplegreen
amurmapleblack
sidebarwidth=##L
sidebar
toplogo
leftframetitle
rule
rulecolor=#%color
#endkeyvals

\begin{information}
\begin{information}[title%text]
\end{information}
\begin{quotation}[%<author(s)%>]
\begin{remark}
\begin{remark}[title complement%text]
\end{remark}
\boxalert{text}
\boxalert<overlay specification>{text}
\collaboration{collaboration%text}
\framesection{text}
\mail{email%URL}#U
\sepframe
\sepframe[options%keyvals]
\thanksframe[graphic]{title}
\thanksframe{title}
\webpage{URL}#U

#keyvals:\sepframe
title={%<text%>}
image={%<graphics code%>}
#endkeyvals

\begin{boxalertenv}#*
\end{boxalertenv}#*
\pourc#S
\theamurmapletoc#*
\xj#S

AmurmapleRed#B
AmurmapleBlack#B
AmurmapleOrange#B
AmurmapleBlue#B
AmurmapleGreen#B
AmurmapleRemarkColor#B
