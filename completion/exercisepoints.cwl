# exercisepoints package
# Matthew Bertucci 1/18/2022 for v1.2.3

#include:ifthen

#keyvals:\usepackage/exercisepoints#c
customlayout
#endkeyvals

\begin{exercise}
\begin{exercise}[title%text]
\end{exercise}

\points{number}
\itempoints{number}
\setitempointsunit{singular}{plural}

\numberofexercises
\totalpoints
\getpoints{exercise number}

\bonuspoints{number}
\getbonuspoints
\totalpointswithbonus

\begin{subexercise}
\begin{subexercise}[title%text]
\end{subexercise}

\AtBeginExercise{code}#*
\AtEndExercise{code}#*
\currentexercisetitle#*
\currentexercisenumber#*
\currentexercisepoints#*
\AtBeginSubexercise{code}#*
\AtEndSubexercise{code}#*
\currentsubexercisenumber#*
\currentsubexercisepoints#*
\currentsubexercisetitle#*