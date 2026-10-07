# tikzphysics.thermodynamics tikzlibrary
# Matthew Bertucci 2026/10/01 for v1.7.0

#include:tikzlibrarytikzphysics.core
#include:tikzlibrarypatterns
#include:tikzlibrarycalc

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
reservoir width=##L
reservoir height=##L
chamber width=##L
chamber height=##L
thermal wall width=##L
thermal wall height=##L
thermal device size=##L
pv show axes#true,false
pv width=##L
pv height=##L
pv max volume=%<number%>
pv max pressure=%<number%>
pv start volume=%<number%>
pv start pressure=%<number%>
pv end volume=%<number%>
pv end pressure=%<number%>
pv exponent=%<number%>
pv low volume=%<number%>
pv high volume=%<number%>
pv low pressure=%<number%>
pv high pressure=%<number%>
carnot hot constant=%<number%>
carnot temperature ratio=%<number%>
carnot expansion ratio=%<number%>
pv gamma=%<number%>
thermo diagram separation=##L
thermo diagram work length=##L
thermo hot label=%<text%>
thermo cold label=%<text%>
thermo engine label=%<text%>
thermo refrigerator label=%<text%>
thermo hot heat label=%<text%>
thermo cold heat label=%<text%>
thermo work label=%<text%>
#endkeyvals

#keyvals:\node#c
thermal reservoir
gas chamber
thermal wall
heat engine
refrigerator
isothermal process
isobaric process
isochoric process
adiabatic process
polytropic process
rectangular cycle
carnot cycle
pv diagram
heat engine diagram
refrigerator diagram
#endkeyvals