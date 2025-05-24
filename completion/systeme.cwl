# systeme package
# Matthew Bertucci 2025/05/13 for v0.4

#include:xstring
#include:simplekv

\systeme{eq1,eq2,...%formula}
\systeme[keyvals]{eq1,eq2,...%formula}
\setsysteme{keyvals}
\resetsysteme

#keyvals:\systeme,\setsysteme
eq sep=%<code%>
delim=%<code%>
align={%<list%>}
sign space=##L
member sep space=##L
line skip coeff=%<number%>
member sep subst={%<code1,code2,...%>}
add member sep=%<code%>
remove member sep=%<code%>
extra col sign=%<character%>
extra col pre=%<code%>
extra col post=%<code%>
autonum code=%<code%>
autonum continue#true,false
sort={%<instructions%>}
align terms#true,false
main eq count=%<integer%>
extra height=##L
member sep list={%<code1,code2,...%>}
coeff space=##L
post subst={%<x1%>}{%<y1%>}%<{x2}{y2}...%>
store=%<command%>
#endkeyvals

\aligncal{eq1,eq2,...%formula}

\SYSeqnum#*
\+#*

\SYSstyfile#S
\SYSname#S
\SYSver#S
\SYSdate#S
