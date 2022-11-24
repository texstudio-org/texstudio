# circuits tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibrarycalc
#include:tikzlibrarydecorations.marking

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
circuits
huge circuit symbols
large circuit symbols
medium circuit symbols
small circuit symbols
tiny circuit symbols
circuit declare symbol=%<name%>
every circuit symbol/.style={%<options%>}
circuit declare unit={%<name%>}{%<unit%>}
circuit declare annotation={%<name%>}{%<distance%>}{%<path%>}
circuit symbol open/.style={%<options%>}
circuit symbol filled/.style={%<options%>}
circuit symbol lines/.style={%<options%>}
circuit symbol wires/.style={%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c
circuit symbol unit=##L
circuit symbol size=width %<〈width〉%> height %<〈height〉%>
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
point up
point down
point left
point right
info=%<text%>
info=%<〈angle〉%>:%<〈text〉%>
info=[%<options%>]%<〈angle〉%>:%<〈text〉%>
info'=%<text%>
info'=%<〈angle〉%>:%<〈text〉%>
info'=[%<options%>]%<〈angle〉%>:%<〈text〉%>
info sloped=%<text%>
info sloped=%<〈angle〉%>:%<〈text〉%>
info sloped=[%<options%>]%<〈angle〉%>:%<〈text〉%>
info' sloped=%<text%>
info' sloped=%<〈angle〉%>:%<〈text〉%>
info' sloped=[%<options%>]%<〈angle〉%>:%<〈text〉%>
#endkeyvals

\tikzcircuitssizeunit#S