# automata tikzlibrary
# 2022/11/20 for v3.1.9a

#include:tikzlibraryshapes.multipart

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
state without output
state with output
state
initial
initial by arrow
initial above
initial below
initial left
initial right
initial by diamond
accepting
accepting by double
accepting by arrow
accepting above
accepting below
accepting left
accepting right
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
initial text=%<text%>
initial where=#above,below,left,right
initial distance=##L
accepting text=%<text%>
accepting where=#above,below,left,right
accepting distance=##L
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every state/.style={%<options%>}
every initial by arrow/.style={%<options%>}
every accepting by arrow/.style={%<options%>}
#endkeyvals