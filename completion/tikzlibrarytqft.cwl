# tqft tikzlibrary
# 2022/12/09 for v2.1

#include:tikzlibraryshapes.geometric

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every tqft/.style={%<TikZ keys%>}
tqft/every boundary component/.style={%<TikZ keys%>}
tqft/every incoming boundary component/.style={%<TikZ keys%>}
tqft/every outgoing boundary component/.style={%<TikZ keys%>}
tqft/every lower boundary component/.style={%<TikZ keys%>}
tqft/every incoming lower boundary component/.style={%<TikZ keys%>}
tqft/every outgoing lower boundary component/.style={%<TikZ keys%>}
tqft/every upper boundary component/.style={%<TikZ keys%>}
tqft/every incoming upper boundary component/.style={%<TikZ keys%>}
tqft/every outgoing upper boundary component/.style={%<TikZ keys%>}
#endkeyvals

#keyvals:\node#c,\coordinate#c,\pic#c
tqft/pair of pants
tqft/reverse pair of pants
tqft/cylinder to prior
tqft/cylinder to next
tqft/cylinder
tqft/cap
tqft/cup
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\pic#c
tqft/view from=#incoming,outgoing
tqft/cobordism height=##L
tqft/boundary separation=##L
tqft/circle x radius=##L
tqft/circle y radius=##L
tqft/incoming boundary components=%<integer%>
tqft/skip incoming boundary components=%<integer%>
tqft/outgoing boundary components=%<integer%>
tqft/skip outgoing boundary components=%<integer%>
tqft/offset=%<number%>
tqft/genus=%<integer%>
tqft/incoming boundary component %<<n>%>/.style={%<TikZ keys%>}
tqft/outgoing boundary component %<<n>%>/.style={%<TikZ keys%>}
tqft/incoming lower boundary component %<<n>%>/.style={%<TikZ keys%>}
tqft/outgoing lower boundary component %<<n>%>/.style={%<TikZ keys%>}
tqft/cobordism/.style={%<TikZ keys%>}
tqft/genus upper/.style={%<TikZ keys%>}
tqft/genus lower/.style={%<TikZ keys%>}
tqft/hole %<<n>%>/.style={%<TikZ keys%>}
tqft/hole %<<n>%> upper/.style={%<TikZ keys%>}
tqft/hole %<<n>%> lower/.style={%<TikZ keys%>}
tqft/cobordism edge/.style={%<TikZ keys%>}
tqft/cobordism outer edge/.style={%<TikZ keys%>}
tqft/between incoming/.style={%<TikZ keys%>}
tqft/between outgoing/.style={%<TikZ keys%>}
tqft/between incoming and outgoing/.style={%<TikZ keys%>}
tqft/between incoming %<<n>%> and %<<n+1>%>/.style={%<TikZ keys%>}
tqft/between outgoing %<<n>%> and %<<n+1>%>/.style={%<TikZ keys%>}
tqft/between first incoming and first outgoing/.style={%<TikZ keys%>}
tqft/between first incoming and first outgoing/.style={%<TikZ keys%>}
tqft/between last incoming and last outgoing/.style={%<TikZ keys%>}
tqft/between first and last incoming/.style={%<TikZ keys%>}
tqft/between first and last outgoing/.style={%<TikZ keys%>}
tqft/incoming upper boundary component %<<n>%>/.style={%<TikZ keys%>}
tqft/outgoing upper boundary component %<<n>%>/.style={%<TikZ keys%>}
#endkeyvals