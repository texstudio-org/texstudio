# examz class
# Matthew Bertucci 2023/06/08 for v1.0.0

#include:environ
#include:xpatch
#include:counterz
#include:class-exam

#keyvals:\documentclass/examz#c
complete
randomize
norandomize
prompt
# options passed to exam class
answers
cancelspace
addpoints
#endkeyvals

\begin{qbitem}{item number}
\end{qbitem}
\begin{qbsolution}
\end{qbsolution}
\begin{qbsolutionbox}
\end{qbsolutionbox}
\begin{qbsolutionorbox}
\end{qbsolutionorbox}
\begin{qbsolutionordottedlines}
\end{qbsolutionordottedlines}
\begin{qbsolutionorgrid}
\end{qbsolutionorgrid}
\begin{qbsolutionorlines}
\end{qbsolutionorlines}
\begin{questionbank}
\end{questionbank}
\begin{versions}
\begin{versions}[number]
\end{versions}

\coursename#*
\coveranswers
\covernoanswers
\examname#*
\instructions#*
\instructorname#*
\namespace#*
\printcover
\printworkspace
\promptrandomexam
\promptversions
\questionfrombank[points]{file}#i
\questionfrombank{file}#i
\setcoursename{text}
\setcoveranswers{format}
\setcovernoanswers{format}
\setexamname{text}
\setinstructions{text}
\setinstructorname{text}
\setnamespace{format}
\setnumberofquestions{number}
\setquestionpath{path%definition}
\setsolutionspace{length}
\settermname{text}
\setworkspace{format}
\termname#*
\thenumversions#S
\theversion#*
\workspace#*