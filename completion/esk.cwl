# esk package
# Matthew Bertucci 2/22/2022 for v1.0

#include:kvsetkeys
#include:verbatim

\begin{esk}
\begin{esk}[name]
\begin{esk}(def1,def2,...)
\begin{esk}[name](def1,def2,...)
\end{esk}
\begin{eskdef}{name}
\end{eskdef}
\eskwrite{Sketch code%definition}
\eskprelude{Sketch prelude%definition}
\eskaddtoprelude{Sketch code%definition}
\eskglobals{Sketch properties}
\eskaddtoglobals{Sketch properties}

\begin{eskfile}#*
\begin{eskfile}[name]#*
\end{eskfile}#*
\eskwritetoken{code}#*
\theeskfig#*
\theeskfile#*

\RCS#S
\endRCS#S
\esk#S
\esk[name]#S
\esk(def1,def2,...)#S
\esk[name](def1,def2,...)#S
\endesk#S
\eskdef{name}#S
\endeskdef#S
\eskfile#S
\eskfile[name]#S
\endeskfile#S
\filedate#S
\filemaintainer#S
\filename#S
\filerevision#S
\fileversion#S
\futurenospacelet{arg}#S
\leftparanthesis#S
\next#S
\nexttoken#S
\stepone#S
\steptwo#S
\stepthree#S
\stoken#S