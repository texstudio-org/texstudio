# timechart package
# Matthew Bertucci 2025/02/16 for v0.51

#include:tikz

\begin{timechart}{start}{finish}#\tikzpicture
\begin{timechart}[options%keyvals]{start}{finish}#\tikzpicture
\end{timechart}

\timechartinterval{start}{finish}{label text%text}
\timechartinterval[options%keyvals]{start}{finish}{label text%text}
\timecharttext{year}{text}
\timecharttext[options%keyvals]{year}{text}
\timechartspace
\timechartspace[options%keyvals]
\timechartsety{length}
\timechartsavey
\timechartresety
\timechartsetyminimumautoreset{min-coordinate}
\timechartsetymaximumautoreset{max-coordinate}
\timechartstepy
\timechartstepy[count]
\timechartfinish

\timechartmakebeforeyear{number}
\timechartmakeafteryear{number}
\timechartlegenditem
\timechartlegenditem[options%keyvals]
\timechartlegendstartrange
\timechartlegendstartrange[options%keyvals]
\timechartlegendfinishrange
\timechartlegendfinishrange[options%keyvals]