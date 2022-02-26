# pst-gantt package
# Matthew Bertucci 2/25/2022 for v0.22a

#include:pstricks
#include:pst-node
#include:pst-grad
#include:pst-xkey
#include:multido

\PstGanttChart{vertical units}{horizontal units}#*
\PstGanttChart[options%keyvals]{vertical units}{horizontal units}#*
\endPstGanttChart#*
\begin{PstGanttChart}{vertical units}{horizontal units}#\pictureHighlight
\begin{PstGanttChart}[options%keyvals]{vertical units}{horizontal units}
\end{PstGanttChart}

#keyvals:\PstGanttChart#c,\begin{PstGanttChart}#c
PstPicture#true,false
ChartShowIntervals
ChartStartInterval=%<number%>
ChartModulo#true,false
ChartModuloValue=%<number%>
ChartUnitIntervalName=%<name%>
ChartUnitBasicIntervalName=%<name%>
TaskUnitIntervalValue=%<number%>
TaskUnitType=%<text%>
TaskOutsideLabelMaxSize=%<number%>
unit=%<number%>
xunit=%<number%>
yunit=%<number%>
#endkeyvals

\PstGanttTask{start}{end}
\PstGanttTask[options%keyvals]{start}{end}

#keyvals:\PstGanttTask#c
TaskUnitType=%<text%>
TaskOutsideLabel={%<text%>}
TaskInsideLabel={%<text%>}
TaskStyle=%<style%>
#endkeyvals

\PSTganttLoaded#S