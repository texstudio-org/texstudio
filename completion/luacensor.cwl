# luacensor package
# Matthew Bertucci 2/24/2022 for v1.1.0

#include:luacode
#include:environ
#include:verbatim
#include:accsupp
#include:fontspec
#include:xcolor
#include:graphicx

#keyvals:\usepackage/luacensor#c
warning
#endkeyvals

\cnsr{text}

\ifcnsr#*
\cnsrtrue
\cnsrfalse

\luacensorversionnumber#S
\cnsrfnt#*
\onething#*
\twothings#*
\donothing#*
\voidenvironment{envname}#*
\hddn{text}#*
\begin{hidden}#*
\end{hidden}#*
\ifwarning#*
\warningtrue#*
\warningfalse#*
\wrnstncl#*
\warnword#*
\danger#*
\warnformat#*
\textwarn#*
\textsafe#*
\dquad#*
\dangersign{arg}#*
\dangerblock#*
\warnblock#*
\tworules#*
\allwarning#*
\confwarning#*
\oldmaketitle#S
darkgreen#B
darkspringgreen#B
forestgreen#B
