# celtic tikzlibrary
# 2022/11/25 for v1.1

\CelticDrawPath{options%keyvals}

#keyvals:\CelticDrawPath#c
max steps=%<integer%>
flip
width=##L
height=##L
size={%<width,height%>}
crossings={%<x,y,type; ...%>}
symmetric crossings={%<x,y,type; ...%>}
ignore crossings={%<x,y,type; ...%>}
ignore symmetric crossings={%<x,y,type; ...%>}
style={%<TikZ keys%>}
at=%<coordinate%>
inner clip=%<integer%>
outer clip=%<integer%>
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
celtic surround/.style={%<TikZ keys%>}
celtic bar/.style={%<TikZ keys%>}
celtic path/.style={%<TikZ keys%>}
celtic path %<⟨n⟩%>/.style={%<TikZ keys%>}
#endkeyvals