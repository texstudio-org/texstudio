# cu-kruk package
# Matthew Bertucci 2023/06/25 for v0.2

#include:keyval
#include:ifluatex
#include:cu-kinovar

#keyvals:\usepackage/cu-kruk#c
autocolormarks
noautocolormarks
#endkeyvals

\cuKruk{neume}{text}
\cuKruk[options%keyvals]{neume}{text}
\cuKrukPara{neumes \\ ... \\ lyrics}
\cuKrukPara[options%keyvals]{neumes \\ ... \\ lyrics}

#keyvals:\cuKruk,\cuKrukPara
krukFont=%<font%>
sylSpace=##L
topMargin=##L
krukRaise=##L
sylRuleHeight=##L
#endkeyvals

\cuSup{sup text}{base text%text}
\cuSup[options%keyvals]{sup text}{base text%text}

#keyvals:\cuSup
raise=##L
#endkeyvals

\cuKrukFont#*
\cuKrukSylSpace#*
\cuKrukTopMargin#*
\cuKrukSylRuleHeight#*
\cuKrukRaise#*
\cuSupRaise#*