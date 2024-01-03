# nomemoize package
# Matthew Bertucci 2024/01/02 for v1.1.0

#include:pgfkeys

\mmzset{options%keyvals}
\mmznext{options%keyvals}
\nommzkeys{options%keyvals}#*
\mmz{code%text}
\mmz[options%keyvals]{code%text}
\begin{memoize}
\begin{memoize}[options%keyvals]
\end{memoize}
\nommz{code%text}
\nommz[options%keyvals]{code%text}
\begin{nomemoize}
\begin{nomemoize}[options%keyvals]
\end{nomemoize}
\ifmemoize#*
\memoizetrue#*
\memoizefalse#*
\ifmemoizing#*
\ifinmemoize#*
\IfMemoizing{name}{true code}{false code}#*
\IfMemoizing[offset]{name}{true code}{false code}#*
\mmzAbort
\mmzUnmemoizable
\mmzNoRef{label}#*
\mmzForceNoRef{label}#*
\mmzContext#*
\mmzContextExtra#*
\mmzCMemo#*
\mmzCCMemo#*
\mmzExternPages#*
\mmzExtraPages#*
\mmzTracingOn#*
\mmzTracingOff#*
