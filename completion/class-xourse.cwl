# xourse class
# Matthew Bertucci 2024/05/13 for v1.5.1

#include:class-ximera

#keyvals:\documentclass/xourse#c
# unique to xourse class
notoc
nonewpage
# inherited from ximera class
handout
noauthor
nooutcomes
instructornotes
noinstructornotes
hints
newpage
numbers
wordchoicegiven
xake
tikzexport
#endkeyvals

\begin{graded}{weight}
\end{graded}

\activity{file}#i
\logo{imagefile}#g
\practice{file}#i

# not documented
\ifnotoc#S
\notoctrue#S
\notocfalse#S
\ifnonewpage#S
\nonewpagetrue#S
\nonewpagefalse#S