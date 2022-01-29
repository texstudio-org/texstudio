# texsurgery package
# Matthew Bertucci 1/27/2022 for v0.6.0

#include:verbatim
#include:listings
#include:xcolor
#include:environ
#include:hyperref

#keyvals:\usepackage/texsurgery#c
showcode
noinstructions
#endkeyvals

codegreen#B
codegray#B
codepurple#B
backcolour#B

\theTSeval#*
\theTSrun#*
\theTSrunsilent#*

\begin{run}#V
\begin{run}[language]#V
\end{run}
\begin{runsilent}#V
\begin{runsilent}[language]#V
\end{runsilent}
\lstinlinesafe|%<code%>|
\lstinlinesafe{verbatimSymbol}#S
\eval{code%definition}
\eval[language]{code%definition}
\sage{code%definition}