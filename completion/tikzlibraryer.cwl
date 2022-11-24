# er tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibraryshapes.geometric

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
entity
relationship
attribute
key attribute
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every entity/.style={%<options%>}
every relationship/.style={%<options%>}
every attribute/.style={%<options%>}
#endkeyvals