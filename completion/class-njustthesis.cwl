# njustthesis class
# Matthew Bertucci 2022/07/03 for v0.0.1

#include:kvdefinekeys
#include:kvsetkeys
#include:kvoptions
#include:class-ctexbook
#include:xeCJK
#include:csquotes
#include:indentfirst
#include:setspace
#include:titletoc
#include:tocbibind
#include:fancyhdr
#include:pifont
#include:footmisc
#include:natbib
#include:graphicx
#include:cnlogo
# loads njust option of cnlogo
#include:tabu
#include:multicol
#include:newtxmath
#include:exercise
#include:enumitem
#include:boxedminipage

\njustsetup{options%keyvals}

#keyvals:\njustsetup
logo=%<logo code%>
cover-title=%<text%>
author=%<name%>
id=%<id number%>
department=%<department%>
discipline=%<discipline%>
title=%<text%>
subtitle=%<text%>
supervisor=%<name%>
associate-supervisor=%<name%>
judge=%<name%>
supervisor-title=%<text%>
associate-supervisor-title=%<text%>
judge-title=%<text%>
year=%<year%>
month=%<month%>
day=%<day%>
signature=%<signature%>
signature*=%<English signature%>
abstract-prefix=
title*=%<English text%>
subtitle*=%<English text%>
header-title=%<text%>
#endkeyvals

\begin{abstract}
\end{abstract}
\begin{abstract*}
\end{abstract*}
\begin{acknowledgement}
\end{acknowledgement}
\begin{keyword}
\end{keyword}
\begin{keyword*}
\end{keyword*}

\copyrightpage
\reviewpage

\filedate#S
\filename#S
\fileversion#S

# from njust option of cnlogo
njust#B
\njustwhole
\njustwhole[color]
\njustwhole[color][scale]