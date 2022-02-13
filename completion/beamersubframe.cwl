# beamersubframe package
# Matthew Bertucci 2/12/2022 for v0.2

#include:verbatim

#keyvals:\usepackage/beamersubframe#c
embed
append
nominiframes
#endkeyvals

\begin{subframe}
\begin{subframe}<overlay specification>
\begin{subframe}<overlay specification>[<default overlay specification>]
\begin{subframe}<overlay specification>[<default overlay specification>][options]
\begin{subframe}<overlay specification>[<default overlay specification>][options]{title}
\begin{subframe}<overlay specification>[<default overlay specification>][options]{title}{subtitle}
\begin{subframe}[<default overlay specification>]
\begin{subframe}[<default overlay specification>][options]
\begin{subframe}[<default overlay specification>][options]{title}
\begin{subframe}[<default overlay specification>][options]{title}{subtitle}
\begin{subframe}[options]
\begin{subframe}[options]{title}
\begin{subframe}[options]{title}{subtitle}
\begin{subframe}{title}
\end{subframe}

\appendsubframes
\ifappend{append-mode material%text}{embed-mode material%text}

\begin{lastframe}
\begin{lastframe}<overlay specification>
\begin{lastframe}<overlay specification>[<default overlay specification>]
\begin{lastframe}<overlay specification>[<default overlay specification>][options]
\begin{lastframe}<overlay specification>[<default overlay specification>][options]{title}
\begin{lastframe}<overlay specification>[<default overlay specification>][options]{title}{subtitle}
\begin{lastframe}[<default overlay specification>]
\begin{lastframe}[<default overlay specification>][options]
\begin{lastframe}[<default overlay specification>][options]{title}
\begin{lastframe}[<default overlay specification>][options]{title}{subtitle}
\begin{lastframe}[options]
\begin{lastframe}[options]{title}
\begin{lastframe}[options]{title}{subtitle}
\begin{lastframe}{title}
\end{lastframe}

\inserttotalframenumberwithsub#*
\ifsubframe{subframe material%text}{normal-frame material%text}
\subslideentry{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#*

\bsfrestorepart{new part page}{prev part num}#*
\bsfrestoresection{new sec page}{prev sec num}#*
\bsfrestoresubsection{new subsec page}{prev subsec num}#*
\bsfrestore{part num}{sec num}{subsec num}{subsecslide num}#*
\bsfsubframepages{part num}{sec num}{subsec num}{subsecslide num}{first page}{last page}#*

\filedate#S
\fileversion#S