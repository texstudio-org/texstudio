# sidecap package
# Matthew Bertucci 11/14/2021 for v1.6f

#include:ifthen

#keyvals:\usepackage/sidecap#c
outercaption
innercaption
leftcaption
rightcaption
wide
raggedright
raggedleft
ragged
#endkeyvals

#ifOption:raggedright
#include:ragged2e
#endif
#ifOption:raggedleft
#include:ragged2e
#endif
#ifOption:ragged
#include:ragged2e
#endif

\begin{SCtable}
\begin{SCtable}[rel-width]
\begin{SCtable}[rel-width][float]
\end{SCtable}

\begin{SCfigure}
\begin{SCfigure}[rel-width]
\begin{SCfigure}[rel-width][float]
\end{SCfigure}

\begin{SCtable*}
\begin{SCtable*}[rel-width]
\begin{SCtable*}[rel-width][float]
\end{SCtable*}

\begin{SCfigure*}
\begin{SCfigure*}[rel-width]
\begin{SCfigure*}[rel-width][float]
\end{SCfigure*}

\begin{wide}
\end{wide}

# not documented
\sidecaptionsep#*
\sidecaptionrelwidth#*
\sidecaptionvpos{arg1}{arg2}#*
