# texments package
# Matthew Bertucci 12/16/2021 for v0.2.0

#include:color
#include:fancyvrb
#include:ifthen

\usestyle{pygments style}

\pygment{language}{code}

\includecode{file}#i
\includecode[language]{file}#i

\begin{pygmented}{language}
\end{pygmented}

\proglang#*
\lexercommand{arg}#*