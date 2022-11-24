# shadows tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibraryfadings

#keyvals:\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
general shadow
general shadow={%<options%>}
drop shadow
drop shadow={%<options%>}
copy shadow
copy shadow={%<options%>}
double copy shadow
double copy shadow={%<options%>}
circular drop shadow
circular drop shadow={%<options%>}
circular glow
circular glow={%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every shadow/.style={%<options%>}
#endkeyvals