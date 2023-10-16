# memoizable package
# Matthew Bertucci 2023/10/15 for v1.0.0

#include:pgfopts

\mmzset{options%keyvals}
\nommzkeys{options%keyvals}#*
\ifmemoize#*
\memoizetrue#*
\memoizefalse#*
\IfMemoizing{name}{true code}{false code}#*
\IfMemoizing[offset]{name}{true code}{false code}#*