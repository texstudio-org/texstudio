# lie-hasse package
# Matthew Bertucci 9/10/2021 for v1.0

#include:xcolor
#include:dynkin-diagrams
#include:tikzlibrarypositioning
#include:tikzlibraryfadings
#include:tikzlibraryquotes

\hasse{%<letter%>}{%<rank%>}
\hasse[%<options%>]{%<letter%>}{%<rank%>}

#keyvals:\hasse#c
edge length=##L
edge/.style={%<TikZ options%>}
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
\forAllPositiveRootsInHasseDiagram{command}
\studyHasseDiagramOfRootSystem{%<letter%>}{%<rank%>}#*
\studyHasseDiagramOfRootSystem[%<options%>]{%<letter%>}{%<rank%>}#*
\doRootThing{arg1}{arg2}#*
\drawRootDecomp{first-pos}{second-pos}#*
\backwardsGtwo#*
\attachDynkin#*
\doHasseDiagram{arg}#*
\forscsvlist#*
\drpo#S
\drmo#S
\tdrpt#S
\maxy#S
\lbl#S
\drmt#S
\iD#S
\xxD#S
\maxxD#S
