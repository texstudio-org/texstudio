# ipsum package
# Matthew Bertucci 2025/07/15 for v0.1.3

#include:kvoptions
#include:xstring
#include:xintexpr
#include:simplekv

#keyvals:\usepackage/ipsum#c
lng=#all,{%<languages%>}
#endkeyvals

\ipsum
\ipsum[range]
\ipsum<keyvals>
\ipsum<keyvals>[range]

#keyvals:\ipsum
Lang=#LAT,EN,FR,DE,ES,PT,IT,NL
Type=#par,sent,enum,item
#endkeyvals
