# memoizable package
# Matthew Bertucci 2024/01/02 for v1.1.0

#include:pgfkeys

\mmzset{options%keyvals}
\nommzkeys{options%keyvals}#*
\ifmemoize#*
\memoizetrue#*
\memoizefalse#*
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
