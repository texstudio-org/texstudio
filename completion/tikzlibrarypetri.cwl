# petri tikzlibrary
# 2022/11/21 for v3.1.9a

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
place
transition
token
tokens=%<integer%>
colored tokens={%<color list%>}
structured tokens={%<text list%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every place/.style={%<options%>}
every transition/.style={%<options%>}
every token/.style={%<options%>}
#endkeyvals