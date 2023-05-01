# tilings.penrose tikzlibrary
# 2023/04/25 for v1.6

#include:tikzlibrarytilings

#keyvals:\BakeTile#c,\pic#c
kite
dart
thin rhombus
thick rhombus
pentagon 5
pentagon 3
pentagon 2
pentagram
boat
diamond
golden triangle
reverse golden triangle
golden gnomon
reverse golden gnomon
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every kite/.style={%<TikZ keys%>}
every dart/.style={%<TikZ keys%>}
every thin rhombus/.style={%<TikZ keys%>}
every thick rhombus/.style={%<TikZ keys%>}
every pentagon 5/.style={%<TikZ keys%>}
every pentagon 3/.style={%<TikZ keys%>}
every pentagon 2/.style={%<TikZ keys%>}
every pentagram/.style={%<TikZ keys%>}
every boat/.style={%<TikZ keys%>}
every diamond/.style={%<TikZ keys%>}
every golden triangle/.style={%<TikZ keys%>}
every reverse golden triangle/.style={%<TikZ keys%>}
every golden gnomon/.style={%<TikZ keys%>}
every reverse golden gnomon/.style={%<TikZ keys%>}
#endkeyvals