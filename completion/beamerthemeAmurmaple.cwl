# Amurmaple beamertheme
# Matthew Bertucci 2022/09/12 for v1.1

#include:multicol
#include:xparse
#include:xfp
#include:expl3
#include:iftex
#include:luamesh
#include:tcolorbox
# loads skins tcolorbox library
#include:tikz
# loads backgrounds, quotes, angles, automata, arrows, and calc tikzlibraries

#keyvals:\usetheme/Amurmaple#c
nogauge
nomail
delaunay
amurmapleblue
amurmaplegreen
sidebarwidth=##L
sidebar
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
AmurmapleOrange#B
AmurmapleBlue#B
AmurmapleGreen#B
