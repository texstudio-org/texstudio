# string-diagrams package
# Matthew Bertucci 2026/11/12 for v0.4.0

#include:tikz
#include:tikzlibraryfit
#include:tikzlibraryquotes

#keyvals:\node#c
box
box ports north=%<integer%>
box ports east=%<integer%>
box ports south=%<integer%>
box ports west=%<integer%>
box ports=%<integer1%>/%<integer2%>/%<integer3%>/%<integer4%>
dot
#endkeyvals

\wires{wires}
\wires[TikZ keys]{wires}

#keyvals:\begin{tikzpicture},\tikz,\tikzset,\begin{scope},\scoped
wire flow=#north,south,east,west
#endkeyvals
