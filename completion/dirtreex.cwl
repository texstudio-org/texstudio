# dirtreex package
# Matthew Bertucci 2026/09/19 for v1.2

#include:tikz
#include:tikzlibrarybackgrounds
#include:zref-abspage

\begin{dirtreex}
\begin{dirtreex}[options%keyvals]
\end{dirtreex}

\dir{directory}{description%text}{contents}
\dir[options%keyvals]{directory}{description%text}{contents}
\file{name}{description%text}
\file[options%keyvals]{name}{description%text}
\archive{directory}{description%text}{contents}
\archive[options%keyvals]{directory}{description%text}{contents}

\verbdir[%<options%>]|%<directory%>|{description%text}{contents}
\verbdir[options%keyvals]{verbatimSymbol}{description%text}{contents}#S
\verbfile|%<name%>|{description%text}
\verbfile[%<options%>]|%<name%>|{description%text}
\verbfile[options%keyvals]{verbatimSymbol}{description%text}#S
\verbarchive[%<options%>]|%<directory%>|{description%text}{contents}
\verbarchive[options%keyvals]{verbatimSymbol}{description%text}{contents}#S

\DirtreexFormatName{arg}#*
\DirtreexGetField{arg1}{arg2}#*