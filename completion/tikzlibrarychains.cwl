# chains tikzlibrary
# 2022/11/20 for v3.1.9a

#include:tikzlibrarypositioning

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\scoped#c
start chain
chain default direction=%<direction%>
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c,\chainin#c
continue chain
continue chain=%<direction%>
continue chain=%<〈chain name〉〈direction〉%>
on chain
on chain=%<direction%>
on chain=%<〈chain name〉〈direction〉%>
join
join=with %<with%> by {%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every on chain/.style={%<options%>}
every join/.style={%<options%>}
#endkeyvals

\chainin(%<node name%>);
\chainin(%<node name%>)[%<options%>];

\tikzchaincount#*
\tikzchaincurrent#*
\tikzchainprevious#*