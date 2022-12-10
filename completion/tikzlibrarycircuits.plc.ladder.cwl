# circuits.plc.ladder tikzlibrary
# 2022/12/09 for v1.3

#include:tikzlibrarycircuits

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
circuit plc ladder
ladderrungsep=%<number%>
#endkeyvals

\ladderskip#L
\ladderrungend{number}
\ladderpowerrails

#keyvals:\node#c
symbol=%<symbol%>
symbol color=#%color
clksize=##L
input sep=##L
output sep=##L
inputs={%<input1,input2,...%>}
outputs={%<output1,output2,...%>}
#endkeyvals