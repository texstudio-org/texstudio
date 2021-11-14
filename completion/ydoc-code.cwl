# ydoc-code package
# Matthew Bertucci 11/13/2021 for v0.6alpha

#include:hyperref
#include:needspace
#include:xcolor
#include:listings

macroimpl#B

\begin{macrocode}
\end{macrocode}
\begin{macro}{macro}
\begin{macro}{%<macro%>}[%<args%>]{%<arg1%>}%<{arg2}...{argN}%>
\end{macro}
\begin{environment}{envname}
\begin{environment}{%<envname%>}[%<args%>]{%<arg1%>}%<{arg2}...{argN}%>
\end{environment}
\begin{style}{stylename}
\begin{style}{%<stylename%>}[%<args%>]{%<arg1%>}%<{arg2}...{argN}%>
\end{style}
\begin{key}{keyname}{value}
\end{key}
\bslash

\ydocwrite#*
\ydocfname#*
\newlinemacro#*
\spacemacro#*
\bslashmacro#*
\lastlinemacro#*
\firstlinemacro#*
\thelinenumber#*
\linenumberbox#*
\PrintMacroCode#*
\themacrocode#*
\ydoclistingssettings#*
\PrintMacroImpl{arg}#*
\PrintMacroImplName{arg}#*
\PrintEnvImplName{arg}#*
\PrintStyleImplName{arg}#*
\implstyle#*