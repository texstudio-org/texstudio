# string-diagrams package
# Matthew Bertucci 2023/06/13 for v0.2.0

#include:tikz

#keyvals:\node#c
box
box ports north=%<integer%>
box ports east=%<integer%>
box ports south=%<integer%>
box ports west=%<integer%>
box ports=%<integer1%>/%<integer2%>/%<integer3%>/%<integer4%>
dot
#endkeyvals

\wires{connectivity}{loose ends}
\wires[TikZ keys]{connectivity}{loose ends}
