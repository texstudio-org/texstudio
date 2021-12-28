# autopuncitem package
# Matthew Bertucci 12/24/2021

#include:enumitem
#include:luacode

\APomit
\APpass
\setAPeach{default punct}{second last punct}{last punct}
\setAPall{punct}
\setAPdef{punct}
\setAPseclast{punct}
\setAPlast{punct}
\enableAPautopassnest
\disableAPautopassnest

#keyvals:\begin{itemize}#c,\begin{enumerate}#c,\begin{description}#c
autopunc
#endkeyvals

\begin{AutoPuncItemize}#*
\end{AutoPuncItemize}#*