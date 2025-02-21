# codehigh package
# Matthew Bertucci 2025/02/21 for v2025C

#include:catchfile
#include:xcolor
#include:ninecolors
#include:varwidth
#include:iftex

\begin{codehigh}#V
\begin{codehigh}[options%keyvals]#V
\end{codehigh}
\begin{codehigh*}#V
\begin{codehigh*}[options%keyvals]#V
\end{codehigh*}
\begin{demohigh}
\begin{demohigh}[options%keyvals]
\end{demohigh}
\begin{demohigh*}#V
\begin{demohigh*}[options%keyvals]#V
\end{demohigh*}
\CodeHigh{options%keyvals}
\dochighinput{file}
\dochighinput[options%keyvals]{file}
\fakeverb{verbatim content%definition}

#keyvals:\begin{codehigh},\begin{codehigh*},\begin{demohigh},\begin{demohigh*},\CodeHigh,\dochighinput
language=#latex,latex/latex2,latex/latex3,latex/math,latex/table
style/main=#%color
style/code=#%color
style/demo=#%color
boxsep=##L
lite#true,false
long#true,false
demo#true,false
theme=%<theme%>
visiblespace
#endkeyvals

# not documented
\NewCodeHighEnv{envname}{options%keyvals}#*N
\NewCodeHighInput{command}{options%keyvals}#*d
\AddCodeHighRule{type}{name}{regex%definition}#*
\AddCodeHighRule[language]{type}{name}{regex%definition}#*
\SetCodeHighStyle{type}{color}#*
\SetCodeHighStyle[theme]{type}{color}#*
\GetCodeHighStyle{type}#*
\GetCodeHighStyle[theme]{type}#*
\codehighspace#*
\SetCodeHighTracing{options%keyvals}#*
#keyvals:\SetCodeHighTracing
+code
-code
+demo
-demo
+parser
-parser
all
none
#endkeyvals
