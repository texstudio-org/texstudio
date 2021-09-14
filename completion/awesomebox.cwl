# awesomebox package
# Matthew Bertucci 9/12/2021 for v0.6

#include:array
#include:fontawesome5
#include:xcolor
#include:xparse

\notebox{text}
\tipbox{text}
\warningbox{text}
\cautionbox{text}
\importantbox{text}

\begin{noteblock}
\end{noteblock}
\begin{tipblock}
\end{tipblock}
\begin{warningblock}
\end{warningblock}
\begin{cautionblock}
\end{cautionblock}
\begin{importantblock}
\end{importantblock}

\awesomebox{vrulewidth%l}{icon}{iconcolor%color}{text}#*
\awesomebox[vrulecolor%color][hrule][title]{vrulewidth%l}{icon}{iconcolor%color}{text}#*
\abShortLine#*
\abLongLine#*
\begin{awesomeblock}{vrulewidth%l}{icon}{iconcolor%color}#*
\begin{awesomeblock}[vrulecolor%color][hrule][title]{vrulewidth%l}{icon}{iconcolor%color}#*
\end{awesomeblock}#*
\aweboxleftmargin#*
\aweboxcontentwidth#*
\aweboxvskip#*
\aweboxsignraise#*
\aweboxrulewidth#*