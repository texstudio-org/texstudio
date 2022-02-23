# luacensor package
# Matthew Bertucci 2/22/2022 for v1.0.0

#include:luacode
#include:environ
#include:verbatim
#include:accsupp
#include:fontspec

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