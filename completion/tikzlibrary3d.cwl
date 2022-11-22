# 3d tikzlibrary
# 2022/11/20 for v3.1.9a

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
plane origin=%<point%>
plane x=%<point%>
plane y=%<point%>
canvas is plane
canvas is xy plane at z=##L
canvas is yx plane at z=##L
canvas is xz plane at y=##L
canvas is zx plane at y=##L
canvas is yz plane at x=##L
canvas is zy plane at x=##L
#endkeyvals