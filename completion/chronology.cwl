# chronology package
# Matthew Bertucci 2023/08/19 for v2.0

#include:calc
#include:tikz

\begin{chronology}{year-start}{year-stop}{width}
\begin{chronology}{year-start}{year-stop}{width}[scaling]#*
\begin{chronology}[step]{year-start}{year-stop}{width}#*
\begin{chronology}[step]{year-start}{year-stop}{width}[scaling]
\begin{chronology}*{year-start}{year-stop}{width}
\begin{chronology}*{year-start}{year-stop}{width}[scaling]#*
\begin{chronology}*[step]{year-start}{year-stop}{width}#*
\begin{chronology}*[step]{year-start}{year-stop}{width}[scaling]
\end{chronology}

\decimaldate{day}{month}{year}
\eventspan{begin-date}{end-date}{label%text}
\eventspan{begin-date}{end-date}{label%text}[fill]
\eventspan{begin-date}{end-date}{label%text}[fill][opacity]
\eventspan{begin-date}{end-date}{label%text}[fill][opacity][bar-thickness]
\eventspan{begin-date}{end-date}{label%text}[fill][opacity][bar-thickness][indicator]
\eventpoint{date}{label%text}
\eventpoint{date}{label%text}[fill]
\eventpoint{date}{label%text}[fill][opacity]
\eventpoint{date}{label%text}[fill][opacity][height]

# deprecated
\event{end-date}{label%text}#*
\event[begin-date]{end-date}{label%text}#*

# not documented
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
