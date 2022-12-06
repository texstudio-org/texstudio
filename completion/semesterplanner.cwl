# semesterplanner package
# Matthew Bertucci 11/14/2021 for v1.0

#include:fontawesome
#include:color
#include:schedule
#include:tikz
#include:tikzlibraryshapes

\begin{timetable}
\end{timetable}

\lecture{course name}{lecturer}{room}{day%keyvals}{start-end}{priority}
\seminar{course name}{lecturer}{room}{day%keyvals}{start-end}{priority}
\meeting{course name}{lecturer}{room}{day%keyvals}{start-end}{priority}
\officehour{course name}{lecturer}{room}{day%keyvals}{start-end}{priority}
\tutorial{course name}{lecturer}{room}{day%keyvals}{start-end}{priority}

#keyvals:\lecture,\seminar,\meeting,\officehour,\tutorial
M
T
W
Th
F
#endkeyvals

\begin{legend}
\end{legend}

\ttlegend{color}{description}

\begin{appointments}
\begin{appointments}[room-column title]
\end{appointments}

\appointment{date}{time}{course}{description}{room}{priority}

\begin{deadlines}
\end{deadlines}

\deadline{date}{course}{description}{priority}

\begin{exams}
\end{exams}

\exam{date}{time}{course}{type}

\pnone
\plow
\pmid
\phigh
\pmandatory

\teams
\zoom
\youtube

\written
\oral

\tba
\tbd
