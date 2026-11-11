# string-diagrams package
# Matthew Bertucci 2026/11/11 for v0.3.0

#include:tikz
#include:tikzlibraryfit

#keyvals:\node#c
box
box ports north=%<integer%>
box ports east=%<integer%>
box ports south=%<integer%>
box ports west=%<integer%>
box ports=%<integer1%>/%<integer2%>/%<integer3%>/%<integer4%>
dot
#endkeyvals

\wires{connectivity}
\wires[TikZ keys]{connectivity}
