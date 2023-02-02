# texments package
# Matthew Bertucci 12/16/2021 for v0.2.0

#include:color
#include:fancyvrb
#include:ifthen

\usestyle{pygments style}

\pygment{language}{code%definition}

\includecode{file}
\includecode[language]{file}

\begin{pygmented}{language}#V
\end{pygmented}

\proglang#*
\lexercommand{arg}#*
