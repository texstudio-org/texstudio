# mindmap tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibrarytrees
#include:tikzlibrarydecorations

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
mindmap
every mindmap/.style={%<options%>}
small mindmap
large mindmap
huge mindmap
every concept/.style={%<options%>}
concept color=#%color
every extra concept/.style={%<options%>}
root concept/.append style={%<options%>}
level 1 concept/.append style={%<options%>}
level 2 concept/.append style={%<options%>}
level 3 concept/.append style={%<options%>}
level 4 concept/.append style={%<options%>}
every circle connection bar/.style={%<options%>}
every annotation/.style={%<options%>}
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
concept
extra concept
annotation
#endkeyvals

#keyvals:\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c
concept connection
#endkeyvals