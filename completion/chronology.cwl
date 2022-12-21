# chronology package
# Matthew Bertucci 2022/12/16 for v1.1.1

#include:calc
#include:tikz

\begin{chronology}{start}{end}{width}
\begin{chronology}{start}{end}{width1}[width2]#*
\begin{chronology}[stepsize]{start}{end}{width}#*
\begin{chronology}[stepsize]{start}{end}{width1}[width2]
\begin{chronology}*{start}{end}{width}
\begin{chronology}*{start}{end}{width1}[width2]#*
\begin{chronology}*[stepsize]{start}{end}{width}#*
\begin{chronology}*[stepsize]{start}{end}{width1}[width2]
\end{chronology}

\event{year}{text}
\event[start-year]{end-year}{text}
\decimaldate{day}{month}{year}

\thestep#S
\thestepstart#S
\thestepstop#S
\theyearstart#S
\theyearstop#S
\thedeltayears#S
\xstart#S
\xstop#S
\unit#S
\timelinewidth#S
\timelinebox#S