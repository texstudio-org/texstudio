# amscdx package
# Matthew Bertucci 2/8/2022 for v2.2x

#include:amsgen
#include:xcolor
#include:graphicx

#keyvals:\usepackage/amscdx#c
lyx
#endkeyvals

\begin{CD}#m
\end{CD}#m

\CDlor{color}

\minCDarrowwidth#*

\CDat#S
\Iat#S

\iflyx#*
\lyxtrue#*
\lyxfalse#*
\ifCDfat#*
\CDfattrue#*
\CDfatfalse#*
\ifCDash#*
\CDashtrue#*
\CDashfalse#*