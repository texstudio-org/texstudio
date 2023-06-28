# tudaexercise class
# Matthew Bertucci 2022/08/17 for v3.27

#include:l3keys2e
#include:environ
#include:class-scrartcl
#include:tudarules
#include:scrlayer-scrpage
#include:tudafonts
#include:geometry
#include:tudacolors
#include:graphicx
#include:hyperref

#keyvals:\documentclass/tudaexercise#c
color=#%color
accentcolor=#%color
textaccentcolor=#%color
identbarcolor=#%color
custommargins=#true,false,geometry
fontsize=##L
BCOR=%<Länge%>
paper=#a0,a1,a2,a3,a4,a5,a6
logofile=%<Dateipfad%>
credit
headontitle#true,false
colorback=#true,false
title=#default,small,large
department=mecheng
departmentlogofile=%<Dateipfad%>
match-task-subtask-syntax#true,false
solution#true,false
points=#true,false,auto
subtask=#ruled,runin,plain
#endkeyvals

#ifOption:department=mecheng
TUDa-Primary1#B
TUDa-Primary2#B
TUDa-Secondary1#B
TUDa-Secondary2#B
TUDa-Secondary3#B
TUDa-Secondary4#B
TUDa-Secondary5#B
TUDa-Secondary6#B
TUDa-Arrow#B
# from tudamecheng.cfg
#include:pgf
\MechEngArrow{Länge}
\MechEngArrow*{Länge}
#endif

\title[Kurztitel für die Kopfzeile%text]{text}
\term{Semester}
\sheetnumber{Nummer des Übungsblatts}

\begin{task}{Überschrift%text}
\begin{task}[Optionen%keyvals]{Überschrift%text}
\end{task}
\begin{task*}{Aufgabentitel%text}
\begin{task*}[Optionen%keyvals]{Aufgabentitel%text}
\end{task*}
\thetask

#keyvals:\begin{task}#c,\begin{task*}#c
points=%<auto|<Nummer>%>
credit=%<Nummer%>
solution#true,false
#endkeyvals

\begin{subtask}
\begin{subtask}[Optionen%keyvals]
\end{subtask}
\begin{subtask*}{Titel der Teilaufgabe%text}
\begin{subtask*}[Optionen%keyvals]{Titel der Teilaufgabe%text}
\end{subtask*}
\thesubtask

#keyvals:\begin{subtask}#c,\begin{subtask*}#c
points=%<Nummer%>
credit=%<Nummer%>
title=%<text%>
#endkeyvals

\ConfigureHeadline{keyvals}

#keyvals:\ConfigureHeadline#c
headline={%<text%>}
even={%<text%>}
odd={%<text%>}
oneside={%<text%>}
#endkeyvals

\ShortTitle
\StudentID
\StudentName

\begin{solution}
\end{solution}
\begin{solution*}
\end{solution*}

\IfSolutionT{true code}
\IfSolutionF{false code}
\IfSolutionTF{true code}{false code}

\creditformat{text}#*
\creditformatsum{text}#*
\PointName#*
\PointsName#*
\pointformat{text}#*

\getPoints{Nummer}
\getPointsTotal
\refPoints{label}#r
\mapPoints{code%text}
\mapPoints*{code%text}

# not documented
\authorandname#*
\institution{Einrichtung}#*
\sheetsep#*
\solutionsep#*
\StudentIDname#*
\StudentIDsep#*
\StudentNamesep#*
\subtaskformat#*
\taskformat#*
\tasksep#*
\titleimage{graphics code}#*

# deprecated
\begin{examheader}#S
\end{examheader}#S
\examheaderdefault#S
\subsubtitle{text}#S