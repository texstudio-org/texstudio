# lie-hasse package
# Matthew Bertucci 9/10/2021 for v1.0

#include:xcolor
#include:dynkin-diagrams

\hasse{%<letter%>}{%<rank%>}
\hasse[%<options%>]{%<letter%>}{%<rank%>}

#keyvals:\hasse#c
attach Dynkin diagram#true,false
three D#true,false
z shift=##L
top/.style={%<style specs%>}
right/.style={%<style specs%>}
left/.style={%<style specs%>}
#endkeyvals

\hasseDiagrams{type1;type2;...}
\rootSystemHeight{cmd}
\rootSystemHeight[letter][rank]{cmd}
\rootSystemWidthAtGrade{grade}{cmd}
\rootSystemWidthAtGrade[letter][rank]{grade}{cmd}
\rootSum[letter][rank]{first-pos}{second-pos}{cmd}#d
\drawRootAsDynkinSum{arg1}{arg2}#*
\forAllPositiveRootsInHasseDiagram{arg}#/tikzpicture,dynkinDiagram