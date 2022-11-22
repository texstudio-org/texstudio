# math tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibraryfpu

\tikzmath{statements}

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
evaluate={%<statements%>}
#endkeyvals

\tikzmathfor#S