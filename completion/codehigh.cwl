# codehigh package
# Matthew Bertucci 10/3/2021 for v2021C

#include:expl3
#include:l3benchmark
#include:catchfile
#include:xcolor
#include:ninecolors
#include:varwidth

\begin{codehigh}#V
\begin{codehigh}[options%keyvals]#V
\end{codehigh}
\begin{demohigh}#V
\begin{demohigh}[options%keyvals]#V
\end{demohigh}
\CodeHigh{options%keyvals}
\dochighinput{file}
\dochighinput[options%keyvals]{file}

#keyvals:\begin{codehigh},\begin{demohigh},\CodeHigh,\dochighinput
language=#latex,latex/latex2,latex/latex3,latex/math,latex/table
style/main=#%color
style/code=#%color
style/demo=#%color
boxsep=##L
#endkeyvals

\NewCodeHighEnv{envname}{style}#*N
\NewCodeHighInput{cmd}{style}#*d
