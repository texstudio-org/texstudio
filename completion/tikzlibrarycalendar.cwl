# calendar tikzlibrary
# 2022/11/20 for v3.1.9a

#include:pgfcalendar

\calendar %<〈calendar spec〉%>;
\calendar[%<options%>] %<〈calendar spec〉%>;

#keyvals:\calendar#c
dates=%<start%> to %<end%>
day xshift=##L
day yshift=##L
month xshift=##L
month yshift=##L
day code={%<code%>}
day text=%<text%>
month code={%<code%>}
month text=%<text%>
year code={%<code%>}
year text=%<text%>
if=(%<conditions%>) %<〈code or options〉%>
if=(%<conditions%>) %<〈code or options〉%> else %<〈else code or options〉%>
execute before day scope={%<code%>}
execute at begin day scope={%<code%>}
execute at end day scope={%<code%>}
execute after day scope={%<code%>}
day list downward
day list upward
day list right
day list left
week list
month list
month label left
month label left vertical
month label right
month label right vertical
month label above left
month label above centered
month label above right
month label below left
month label below centered
#endkeyvals

\tikzdaycode#*
\tikzdaytext#*
\tikzmonthcode#*
\tikzmonthtext#*
\tikzyearcode#*
\tikzyeartext#*

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
every calendar/.style={%<options%>}
every month/.style={%<options%>}
every year/.style={%<options%>}
#endkeyvals