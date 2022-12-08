# commutative-diagrams package
# Matthew Bertucci 2/3/2022 for v1.0.1

#include:tikz
#include:tikzlibrarycommutative-diagrams

\begin{codi}#\math
\begin{codi}[options%keyvals]#\math
\end{codi}#\math

#keyvals:\begin{codi}#c
prompter
expand=#none,once,full
replace character=%<character1%> with %<character2%>
replace charcode=%<charcode%> with %<character%>
remove characters=%<characters%>
remove character=%<character%>
remove charcode=%<charcode%>
overwrite=#false,alias,true
every diagram/.append style={%<TikZ options%>}
every layout/.append style={%<TikZ options%>}
every object/.append style={%<TikZ options%>}
every arrow/.append style={%<TikZ options%>}
every label/.append style={%<TikZ options%>}
tetragonal
tetragonal=base %<<length>%> height %<<length>%>
hexagonal
hexagonal=%<<direction>%> side %<<length>%> angle %<<angle>%>
square=##L
golden=##L
arrows/crossing over
arrows/crossing over/clearance=##L
arrows/crossing over/color=#%color
arrows/slide=##L
arrows/shove=##L
# some common tikz options
%color
x=##L
y=##L
node distance=##L
#endkeyvals
