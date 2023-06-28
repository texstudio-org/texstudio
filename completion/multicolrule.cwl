# multicolrule package
# Matthew Bertucci 9/26/2021 for v1.3a

#include:l3keys2e
#include:xpatch
#include:xcolor
#include:scrlfile
#include:multicol

#keyvals:\usepackage/multicolrule#c
tikz#true,false
twocolumn#true,false
paracol#true,false
#endkeyvals

\SetMCRule{options%keyvals}
\DeclareMCRulePattern{name}{keyvals}

#keyvals:\SetMCRule,\DeclareMCRulePattern
color=#%color
color-model=
custom-pattern={%<pattern%>}{%<shift down%>}{%<shift up%>}
custom-tile={%<pattern%>}{%<space above%>}{%<space below%>}
double=##L
expand=##L
extend-bot=##L
extend-fill#true,false
extend-reserve=##L
extend-top=##L
line-style=#circles,dash-dot,dash-dot-dot,dashed,default,dense-circles,dense-dots,dense-solid-circles,densely-dash-dot,densely-dash-dot-dot,densely-dashed,densely-dotted,dots,dotted,loose-dots,loose-circles,loose-solid-circles,loosely-dash-dot,loosely-dash-dot-dot,loosely-dashed,loosely-dotted,solid,solid-circles,strut
pattern-after=%<integer%>
pattern-for=%<integer%>
patterns=
single=##L
repeat
repeat-distance=##L
shift=##L
triple=##L
width=##L
#endkeyvals

#ifOption:tikz
#include:tikz
#keyvals:\SetMCRule,\DeclareMCRulePattern
custom-line={%<draw command%>}
#endkeyvals
#endif
#ifOption:tikz=true
#include:tikz
#keyvals:\SetMCRule,\DeclareMCRulePattern
custom-line={%<draw command%>}
#endkeyvals
#endif

\columnseprulecolor#*
