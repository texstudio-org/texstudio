# schedule package
# Matthew Bertucci 11/14/2021 for v1.20

#include:calc
#include:xcolor

dark#B

\begin{schedule}
\begin{schedule}[title%plain]
\end{schedule}
\class{name}{location}{days of week%keyvals}{start-end}
#keyvals:\class
M
T
W
Th
F
#endkeyvals

\CellHeight{height}
\CellWidth{width}
\TimeRange{start-end}
\SubUnits{number}
\BeginOn{day%keyvals}
#keyvals:\BeginOn
Sunday
Monday
Tuesday
Wednesday
Thursday
Friday
Saturday
#endkeyvals
\TextSize{size}
\FiveDay
\SevenDay
\TwelveHour
\TwentyFourHour
\NewAppointment{name}{background color}{text color}
\LineThickness{dimen%l}

\IncludeWeekends#*
\NoWeekends#*
\ifweekends#*
\weekendstrue#*
\weekendsfalse#*
\iftwelve#*
\twelvetrue#*
\twelvefalse#*
\ifsetboxdepth#*
\setboxdepthtrue#*
\setboxdepthfalse#*
\ifinrange#*
\inrangetrue#*
\inrangefalse#*
\thexcoords#*
\theycoords#*