# answers package
# Matthew Bertucci 2/8/2022 for v2.16

#include:verbatim

#keyvals:\usepackage/answers#c
nosolutionfiles
#endkeyvals

\Newassociation{envname}{name}{file}#N
\solutionextension#*
\Opensolutionfile{file}
\Opensolutionfile{file}[prefix]
\Closesolutionfile{file}
\Writetofile{file}{text}
\begin{Filesave}{file}
\end{Filesave}
\Readsolutionfile{file}

\Currentlabel#*
\Ifanswerfiles{true}{false}#*
\Iffileundefined{file}{true}{false}#*
\Ifopen{file}{true}{false}#*
\Tmp#S
\newsolution{name}#*
\solutionpoint#*
\solutionstyle{text}#*
\ifanswerfiles#*
\answerfilestrue#*
\answerfilesfalse#*