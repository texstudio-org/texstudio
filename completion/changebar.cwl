# changebar package
# Matthew Bertucci 11/3/2021 for v3.6c

#ifOption:color
#include:color
\cbcolor{color}
#endif

#ifOption:xcolor
#include:xcolor
\cbcolor{color}
#endif

\cbstart
\cbend
\begin{changebar}
\end{changebar}
\cbdelete
\cbdelete[width]
\nochangebars

\changebarwidth#*
\deletebarwidth#*
\changebarsep#*
\thechangebargrey#*
\driver{driver name}#*