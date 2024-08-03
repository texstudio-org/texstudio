# lie-hasse package
# Matthew Bertucci 2024/07/09 for v1.01

#include:xcolor
#include:dynkin-diagrams
#include:contour
#include:tikzlibrarypositioning
#include:tikzlibraryfadings
#include:tikzlibraryquotes

\hasse{%<letter%>}{%<rank%>}
\hasse[%<options%>]{%<letter%>}{%<rank%>}

#keyvals:\hasse#c
edge length=##L
edge/.style={%<TikZ options%>}
edge length=##L
edge quotes/.style={%<TikZ options%>}
compact edge/.style={%<TikZ options%>}
noncompact edge/.style={%<TikZ options%>}
attach Dynkin diagram#true,false
three D#true,false
z shift=%<factor%>
top/.style={%<TikZ options%>}
right/.style={%<TikZ options%>}
left/.style={%<TikZ options%>}
show ordering#true,false
show name#true,false
show widths#true,false
show height#true,false
show Levi#true,false
show unipotent radical#true,false
#endkeyvals

\hasseDiagrams{type1;type2;...}
\rootSystemHeight{count register}
\rootSystemHeight[letter][rank]{count register}
\rootSystemWidthAtGrade{grade}{count register}
\rootSystemWidthAtGrade[letter]{grade}{count register}
\rootSystemWidthAtGrade[letter][rank]{grade}{count register}
\rootSum{first-pos}{second-pos}{cmd}#d
\rootSum[letter]{first-pos}{second-pos}{cmd}#d
\rootSum[letter][rank]{first-pos}{second-pos}{cmd}#d
\drawRootAsDynkinSum{arg1}{arg2}#*
\edgeQuote{arg}#*
\forAllPositiveRoots{command}#*
\studyHasseDiagramOfRootSystem{%<letter%>}{%<rank%>}#S
\studyHasseDiagramOfRootSystem[%<options%>]{%<letter%>}{%<rank%>}#S
\doRootThing{arg1}{arg2}#S
\drawRootDecomp{first-pos}{second-pos}#S
\hasseAttachGtwo#S
\attachDynkin#S
\doHasseDiagram{arg}#S
\forscsvlist#S
