# pgf-umlsd package
# Matthew Bertucci 4/7/2022 for v0.6

#include:tikz
#include:tikzlibraryshadows
#include:ifthen

#keyvals:\usepackage/pgf-umlsd#c
underline#true,false
roundedcorners#true,false
#endkeyvals

\begin{sequencediagram}#\pictureHighlight
\end{sequencediagram}

\newthread{name}{text}
\newthread[color]{name}{text}
\newinst{name}{text}
\newinst[edge distance]{name}{text}

\begin{call}{caller}{function}{callee}{return value}
\begin{call}[height%plain]{caller}{function}{callee}{return value}
\end{call}
\begin{messcall}{caller}{function}{callee}
\begin{messcall}[height%plain]{caller}{function}{callee}
\end{messcall}
\messcall{caller}{function}{callee}#S
\messcall[height%plain]{caller}{function}{callee}#S

\mess{caller}{message%text}{callee}
\mess[delay]{caller}{message%text}{callee}

\begin{sdblock}{caption%text}{description%text}
\begin{sdblock}[color]{caption%text}{description%text}
\end{sdblock}

\prelevel
\postlevel

\begin{callself}{caller}{function}{return value}
\begin{callself}[height%plain]{caller}{function}{return value}
\end{callself}

\setthreadbias{anchor%keyvals}
#keyvals:\setthreadbias#c
center
west
east
#endkeyvals

\begin{callanother}{caller}{function}{callee}{return value}#*
\begin{callanother}[height%plain]{caller}{function}{callee}{return value}#*
\end{callanother}#*
\blockcolor#*
\blockcomm#*
\blockname#*
\drawthread{anchor1}{anchor2}#*
\returnvalue#*
\theblocklevel#*
\thecallevel#*
\thecallselflevel#*
\theinstnum#*
\thepreinst#*
\theseqlevel#*
\thethreadnum#*
\threadbias#*
