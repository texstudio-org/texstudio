# todo package
# Matthew Bertucci 12/16/2021 for v2.4142

#include:amssymb

#keyvals:\usepackage/todo#c
nothing
hide
superscript
marginpar
#endkeyvals

\todo{text%todo}#D
\todo[mark text]{text%todo}#D
\todo*{text%todo}#D
\todo*[mark text]{text%todo}#D
\Todo{text%todo}#D
\Todo[mark text]{text%todo}#D
\Todo*{text%todo}#*D
\Todo*[mark text%text]{text%todo}#*D

\todoformat#*
\todomark#*

\done
\done[done text%text]

\begin{todoenv}
\end{todoenv}

\todoopen#*
\todoclose#*
\astodos{mark text%text}#*
\todoenvformat#*

\todos

\todoname#*
\thetodo#*
\doneitem{arg1}{arg2}#*
\todoitem{arg1}{arg2}#*