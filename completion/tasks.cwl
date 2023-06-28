# tasks package
# muzimuzhi/3 Nov 2019, tasks v1.0c
# updated 12/29/2021 for v1.3a

#include:xtemplate

\begin{tasks}
\begin{tasks}[keyvals]
\begin{tasks}[keyvals](cols)
\begin{tasks}(cols)
\end{tasks}
\task
\task[label text]
\task[label text](cols)
\task(cols)
\task*
\task*[label text]
\task*[label text](cols)
\task*(cols)
\task!
\startnewitemline
\settasks{keyvals}
\NewTasksEnvironment{envname}#N
\NewTasksEnvironment[keyvals]{envname}[separator](cols)#N
\RenewTasksEnvironment{envname}
\RenewTasksEnvironment[keyvals]{envname}[separator](cols)

#keyvals:\begin{tasks},\settasks,\NewTasksEnvironment,\RenewTasksEnvironment
style=#itemize,enumerate
label-format=%<code%>
label=%<code%>
ref=%<code%>
label-width=##L
label-offset=##L
item-format=%<code%>
item-indent=##L
column-sep=##L
label-align=#left,right,center
before-skip=##L
after-skip=##L
after-item-skip=##L
resume#true,false
start=%<integer%>
counter=%<counter%>
debug#true,false
#endkeyvals

\tasksifmeasuringTF{true}{false}#*
\tasksifmeasuringT{true}#*
\tasksifmeasuringF{false}#*
\tasklabel#*
\thetask#*
\theHtask#S
