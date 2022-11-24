# backgrounds tikzlibrary
# 2022/11/20 for v3.1.9a

#keyvals:\begin{scope}#c,\scoped#c
on background layer={%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every on background layer/.style={%<options%>}
inner frame xsep=##L
inner frame ysep=##L
inner frame sep=##L
tight background
loose background
background rectangle/.style={%<options%>}
background grid/.style={%<options%>}
outer frame xsep=##L
outer frame ysep=##L
outer frame sep=##L
background top/.style={%<options%>}
background bottom/.style={%<options%>}
background left/.style={%<options%>}
background right/.style={%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c
show background rectangle
framed
show background grid
gridded
show background top
show background bottom
show background left
show background right
#endkeyvals