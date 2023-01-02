# calctab package
# Matthew Bertucci 12/26/2021 for v0.6.1

#include:alphalph
#include:booktabs
#include:eurosym
#include:xcolor
# loads table option of xcolor
#include:numprint
#include:xkeyval
#include:ifthen
#include:fltpoint
#include:xstring

\begin{calctab}
\begin{calctab}[description%text]
\end{calctab}
\amount{description%text}{value}
\amount[options%keyvals]{description%text}{value}
\perc{description%text}{percentage}
\perc[options%keyvals]{description%text}{percentage}
\add{description%text}
\add[options%keyvals]{description%text}
\inrule

\begin{xcalctab}
\end{xcalctab}
\amount{description%text}{value1}{value2}
\amount[options%keyvals]{description%text}{value1}{value2}

\ctcurrency{text}
\ctdescription{text}
\ctontranslation{on translation}
\ctheaderone{header%text}
\ctheadertwo{header%text}
\ctsep#*

#keyvals:\amount
id=%<row id%>
#endkeyvals

#keyvals:\perc#c,\add#c
id=%<row id%>
from=%<row id%>
until=%<row id%>
%<row id%>
#endkeyvals

# from table option of xcolor
#include:colortbl
