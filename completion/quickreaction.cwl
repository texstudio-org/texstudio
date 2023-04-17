# quickreaction package
# Matthew Bertucci 2023/04/14 for v1.02

#include:tikz
#include:tikzlibrarymatrix
#include:tikzlibrarypositioning

#keyvals:\usepackage/quickreaction#c
iupac
#endkeyvals

\begin{quickreaction}
\begin{quickreaction}[opt1]#*
\begin{quickreaction}[opt1][opt2]#*
\end{quickreaction}

\quickarrow
\quickarrow[above]
\quickarrow[above][below]

\fixrow#*

# not documented
\pippo#S
\reactionbody#S
\saltyarrowmax#S
\settomaxwidth{arg1}{arg2}#S