# recorder-fingering package
# Matthew Bertucci 2023/07/16 for v1.2

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
\Whistle{note}
\Whistle[parameters%keyvals]{note}

\fingeringSetup{parameters%keyvals}

#keyvals:\Sopranino,\Soprano,\Alto,\Tenor,\Bass,\Whistle,\fingeringSetup
thumboffset#true,false
width=##L
LHRHdivider#true,false
LHRHspace=##L
trilldir=#L,R,LR
Lpointer=%<symbol%>
Rpointer=%<symbol%>
trill={%<list of holes%>}
#endkeyvals

\NewFfingering{notename}{fingering vector}
\NewFfingering*{notename}{fingering vector}
\NewCfingering{notename}{fingering vector}
\NewCfingering*{notename}{fingering vector}
\NewDfingering{notename}{fingering vector}
\NewDfingering*{notename}{fingering vector}
\AddFingerings{%<key%>}{%<note1={vector1},...%>}
