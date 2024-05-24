# semesterplannerlua
# Matthew Bertucci 2024/05/22 for v1.1.2

#include:tikz
#include:tikzlibrarycalendar
#include:tikzlibrarypositioning
#include:tikzlibraryshapes.misc
#include:tikzlibrarybackgrounds
#include:pgfkeys
#include:xcolor
#include:fontawesome
#include:luapackageloader

\begin{timetable}
\begin{timetable}[options]
\end{timetable}

\lecture
\lecture[options]
\seminar
\seminar[options]
\tutorial
\tutorial[options]
\meeting
\meeting[options]
\officehour
\officehour[options]
\laboratory
\laboratory[options]
\fieldstudy
\fieldstudy[options]

\printSpCalendar{start date}{end date}
\printSpCalendar[cols]{start date}{end date}

\begin{appointments}{true|false}
\begin{appointments}[header%text]{true|false}
\end{appointments}

\appointment
\appointment[options]

\begin{exams}{true|false}
\end{exams}

\exam
\exam[options]

\begin{deadlines}{true|false}
\end{deadlines}

\deadline
\deadline[options]

\oral
\written
\pmandatory
\phigh
\pmid
\plow
\pnone
\teams
\zoom
\youtube
\BBB
\tbd
\tba