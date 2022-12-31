# circuits.plc.sfc tikzlibrary
# 2022/12/09 for v1.0.1

#include:tikzlibrarycircuits
#include:tikzlibraryshapes.gates.ee

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
circuit plc sfc
sfcaqw=##L
sfcanw=##L
sfcah=##L
time=%<time%>
qualifier=#N,R,S,L,D,P,SD,DS,SL,P1,P0
every sfcstep/.style={%<TikZ keys%>}
every sfcstepi/.style={%<TikZ keys%>}
every info/.style={%<TikZ keys%>}
every info'/.style={%<TikZ keys%>}
every sfctransition/.style={%<TikZ keys%>}
every sfcaction/.style={%<TikZ keys%>}
every sfcqualifier/.style={%<TikZ keys%>}
every sfctime/.style={%<TikZ keys%>}
every sfcactionname/.style={%<TikZ keys%>}
#endkeyvals

#keyvals:\node#c
sfcstep={%<options%>}
sfcstepi={%<options%>}
sfctransition={%<options%>}
sfcstar={%<options%>}
#endkeyvals