# bashful package
# Matthew Bertucci 1/28/2022 for v0.93

#include:catchfile
#include:listings
#include:textcomp
#include:xcolor
#include:xkeyval

#keyvals:\usepackage/bashful#c
unique#true,false
hide#true,false
dir=%<directory%>
verbose#true,false
#endkeyvals

\bash[options%keyvals]
\END

#keyvals:\bash
scriptFile=%<file name%>
stdoutFile=%<file name%>
stderrFile=%<file name%>
exitCodeFile=%<file name%>
script#true,false
stdout#true,false
stderr#true,false
ignoreExitCode#true,false
ignoreStderr#true,false
prefix=%<tokens%>
environment=%<envname%>
verbose#true,false
#endkeyvals

\bashStdout
\bashStderr
\splice{shell command%definition}

#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline
style=bashfulScript
style=bashfulStdout
style=bashfulStderr
#endkeyvals

\bashI[options]#*
\bashII{arg}#*
\bashIII{arg}#*
\bashIV{shell command%definition}#*
\bashV{arg}#*
\logBL{message%text}#*

\eoln#S
\firstErrorLine#S