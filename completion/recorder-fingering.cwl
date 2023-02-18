# recorder-fingering package
# Matthew Bertucci 2023/02/17 for v1.0

#include:tikz
#include:tikzlibrarycalc
#include:graphicx

\Sopranino{note}
\Sopranino[parameters%keyvals]{note}
\Soprano{note}
\Soprano[parameters%keyvals]{note}
\Alto{note}
\Alto[parameters%keyvals]{note}
\Tenor{note}
\Tenor[parameters%keyvals]{note}
\Bass{note}
\Bass[parameters%keyvals]{note}

\fingeringSetup{parameters%keyvals}

#keyvals:\Sopranino,\Soprano,\Alto,\Tenor,\Bass,\fingeringSetup
thumboffset#true,false
width=##L
#endkeyvals

\NewFfingering{notename}{fingering vector}
\NewCfingering{notename}{fingering vector}
\AddFingerings{%<key%>}{%<note1={vector1},...%>}