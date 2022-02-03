# overlays package
# Matthew Bertucci 2/2/2022 for v2.12

#include:xcolor
#include:environ
#include:pgffor

\begin{overlays}{number}
\end{overlays}
\begin{fragileoverlays}{number}
\end{fragileoverlays}

\alert{overlay specification}{content%text}
\visible{overlay specification}{content%text}
\only{overlay specification}{content%text}

\savecounterbetweenoverlays{counter}
\savebetweenoverlays{counter}#S
\saveseriesbetweenoverlays{series name}

\overlaysoff
\alertsoff

\psalert{overlay specification}{content%text}#*
\psvisible{overlay specification}{content%text}#*

\next#S
\processslidefirstline{arg1}#S
\processslideline{arg1}#S
\stopslide#S
\stopslidefirst#S