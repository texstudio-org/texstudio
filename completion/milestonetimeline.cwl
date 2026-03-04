# milestonetimeline package
# Matthew Bertucci 2026/03/04 for v1.0

#include:tikz
#include:xifthen
#include:kvoptions
#include:tikzlibrarycalendar

\begin{timeline}
\begin{timeline}[options%keyvals]
\end{timeline}

\milestone{date}{label%text}
\milestone[position]{date}{label%text}
\milestone[position][options%keyvals]{date}{label%text}
\highlightmilestone{date}{label%text}
\highlightmilestone[position]{date}{label%text}
\highlightmilestone[position][options%keyvals]{date}{label%text}
\milestoneat{x}{date}{label%text}
\milestoneat[position]{x}{date}{label%text}
\milestoneat[position][options%keyvals]{x}{date}{label%text}
\timelinetitle{text}
\datemarker{date}{label%text}