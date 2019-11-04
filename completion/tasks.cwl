# tasks pacakge
# muzimuzhi/3 Nov 2019, tasks v1.0c

#include:expl3
#include:xparse
#include:xtemplate

\begin{tasks}
\begin{tasks}[keyvals]
\begin{tasks}[keyvals](cols)
\begin{tasks}(cols)
\end{tasks}
\task
\task[label format]
\task[label format](cols)
\task(cols)
\task*
\task*[label format]
\task*[label format](cols)
\task*(cols)
\task!
\startnewitemline
\settasks{keyvals}
\NewTasksEnvironment{name}
\NewTasksEnvironment[keyvals]{name}[seperator](cols)
\RenewTasksEnvironment{name}
\RenewTasksEnvironment[keyvals]{name}[seperator](cols)

#keyvals:\begin{tasks},\settasks,\NewTasksEnvironment,\RenewTasksEnvironment
style=itemize,enumerate
label-format=%<code%>
label=%<code%>
label-width=##L
label-offset=##L
item-format=%<code%>
item-indent=##L
column-sep=##L
label-align=left,right,center
before-skip=##L
after-skip=##L
after-item-skip=##L
resume#true,false
debug#true,false
#endkeyvals
