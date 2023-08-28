# thm-restate package
# Matthew Bertucci 1/21/2022 for v0.72

#include:thmtools

\begin{restatable}[options%keyvals]{envname}{cmd name}
\begin{restatable}{envname}{cmd name}
\end{restatable}

\begin{restatable*}[options%keyvals]{envname}{cmd name}#*
\begin{restatable*}{envname}{cmd name}#*
\end{restatable*}#*

#keyvals:\begin{restatable}#c,\begin{restatable*}#c
%<title%>
name=%<title%>
label=##l
#endkeyvals

\restatable#S
\endrestatable#S
