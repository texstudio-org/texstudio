# enparen package
# Matthew Bertucci 10/17/2021 for v1.1

#include:ltxcmds
#include:protecteddef
#include:atveryend
#include:uniquecounter
#include:zref-base
#include:kvoptions
#include:kvsetkeys

\enparen{text}
\enparenLeft
\enparenRight
\enparenSetSymbols{level}{open}{close}
\enparenUnsetSymbols{level}
\enparenBeginContext{name}
\enparenEndContext{name}
\enparenSetup{options%keyvals}

#keyvals:\enparenSetup
caption#true,false
footnote#true,false
#endkeyvals

\enparenContextDefault#*
\enparenBeginContext#*
\enparenEndContext#*
\enparenCheckEmptyStack#*