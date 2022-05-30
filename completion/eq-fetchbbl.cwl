# eq-fetchbbl package
# Matthew Bertucci 2022/05/21 for v1.0

#include:exerquiz
#include:fetchbibpes

\begin{BblPsg}
\end{BblPsg}
\begin{BblVrs}
\end{BblVrs}

\qFP{book ch:vrs}
\qFP[options%keyvals]{book ch:vrs}
\sFP{book ch:vrs}
\sFP[options%keyvals]{book ch:vrs}
\qFV{book ch:vrs}
\qFV[options%keyvals]{book ch:vrs}
\sFV{book ch:vrs}
\sFV[options%keyvals]{book ch:vrs}

#keyvals:\qFP,\sFP,\qFV,\sFV
abbr=#esword,none,long,short
roman#true,false
from=#KVJ,KVJ+,ISV
alt=%<word%>
alt*={%<word1,word2,...%>}
transl=%<text%>
from*=#KJV,KJV+,ISV
pcolor=#%color
pformat=%<format cmds%>
delims=%<<tok1><tok2>%>
enclosewith=%<<tok1><tok2>\quote%>
format=%<format cmds%>
caps#true,false
showfirst#true,false
shownone
useperiod#true,false
citeatend#true,false
nocite
priorref=
ltxquotes
replace={%<find1%>}{%<replace1%>}%<{find2}{replace2}...%>
localdefs={%<localdefs%>}
typeset=
typeset*=
#endkeyvals

\useNumbersOn
\useNumbersOff
\adjCAB{code}
\adjCAB[hfill code]{code}
\adjTBX{code}
\adjTBX[hfill code]{code}
\priorRBT{code}
\priorPsg{code}
\setRBTWidthTo{content}
\setRBTWidth{width}
\RBTWidth#*

# not documented
\CATorTBX{arg}#*
\eqfQorS#*
\presetMBbl#*