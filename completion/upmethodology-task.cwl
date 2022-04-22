# upmethodology-task package
# Matthew Bertucci 2022/04/21 for release 2022/02/10

#include:upmethodology-p-common
#include:upmethodology-version

#keyvals:\usepackage/upmethodology-task#c
french
francais
english
#endkeyvals

\begin{taskdescription}{id}
\end{taskdescription}
\begin{taskdescription*}{id}
\end{taskdescription*}

\taskname{name}#/taskdescription,taskdescription*
\tasksuper{id}#/taskdescription,taskdescription*
\taskcomment{text}#/taskdescription,taskdescription*
\taskprogress{percent}#/taskdescription,taskdescription*
\taskstart{date}#/taskdescription,taskdescription*
\taskend{date}#/taskdescription,taskdescription*
\taskmanager{name}#/taskdescription,taskdescription*
\taskmember{name}#/taskdescription,taskdescription*
\taskmilestone{date}{comment%text}#/taskdescription,taskdescription*

\thetasksuper{id}
\thetaskname{id}
\thetaskcomment{id}
\thetaskprogress{id}
\thetaskstart{id}
\thetaskend{id}
\thetaskmanagers{id}
\thetaskmembers{id}
\thetaskmilestones{id}
\thetaskmilestonecomment{id}{date}
\thetaskdescription{id}
\thetaskdescription[width]{id}