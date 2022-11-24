# circuits.logic tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibrarycircuits

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
circuit logic
every circuit logic/.style={%<options%>}
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
inputs={%<inputs%>}
and gate
nand gate
or gate
nor gate
xor gate
xnor gate
not gate
buffer gate
#endkeyvals