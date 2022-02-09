# autopuncitems package
# Matthew Bertucci 2022-02-09 for release 2022-01-30

#include:enumitem
#include:etoolbox
#include:luacode

#keyvals:\usepackage/autopuncitem#c
noenumitem
#endkeyvals

\APomit
\APpass
\setAPeach{default punct}{second last punct}{last punct}
\setAPall{punct}
\setAPdef{punct}
\setAPseclast{punct}
\setAPlast{punct}
\enableAPautopassnest
\disableAPautopassnest
\enableAPprotectnest
\disableAPprotectnest

#keyvals:\setlist,\SetEnumitemKey,\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
autopunc
autopuncO
autopuncE
#endkeyvals

\begin{AutoPuncItems}
\end{AutoPuncItems}
\begin{AutoPuncItemsO}#*
\end{AutoPuncItemsO}#*
\begin{AutoPuncItemsE}#*
\end{AutoPuncItemsE}#*
