# tkz-berge package
# Matthew Bertucci 9/17/2021 for v2.0

#include:tkz-graph

\grEmptyPath{number of vertices}#/tikzpicture
\grEmptyPath[options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grEmptyPath#c
RA=
RS=
prefix=
Math
form=
#endkeyvals

\EdgeInGraphLoop{prefix}{number of vertices}#/tikzpicture
\EdgeInGraphLoop*{prefix}{number of vertices}#/tikzpicture
\EdgeInGraphSeq{prefix}{start}{end}#/tikzpicture
\EdgeInGraphMod{prefix}{number of vertices}{add}#/tikzpicture
\EdgeInGraphMod*{prefix}{number of vertices}{add}{start}{step}#/tikzpicture
\EdgeInGraphModLoop{prefix}{number of vertices}{add}{start}#/tikzpicture

\EdgeIdentity{prefix1}{prefix2}{number of vertices}#/tikzpicture
\EdgeIdentity*{prefix1}{prefix2}{vertex1,vertex2,...}#/tikzpicture

\EdgeFromOneToAll{prefix1}{prefix2}{from}{number of vertices}#/tikzpicture
\EdgeFromOneToSeq{prefix1}{prefix2}{from}{start}{end}#/tikzpicture
\EdgeFromOneToSel{prefix1}{prefix2}{from}{vertex1,vertex2,...}#/tikzpicture
\EdgeFromOneToComp{prefix1}{prefix2}{from}{number of vertices}#/tikzpicture

\EdgeMod{prefix1}{prefix2}{number of vertices}{step}#/tikzpicture
\EdgeMod*{prefix1}{prefix2}{number of vertices}{step1}{step2}#/tikzpicture
\EdgeDoubleMod{prefix1}{numofvertices1}{start1}{add1}{prefix2}{numofvertices2}{start2}{add2}{end}#/tikzpicture

\EdgeInGraphFromOneToComp{prefix}{number of vertices}{from}#/tikzpicture
\EdgeInGraphFromOneToComp[options%keyvals]{prefix}{number of vertices}{from}#/tikzpicture

\grEmptyCycle{number of vertices}#/tikzpicture
\grEmptyCycle[options%keyvals]{number of vertices}#/tikzpicture
\grCycle{number of vertices}#/tikzpicture
\grCycle[options%keyvals]{number of vertices}#/tikzpicture
\grComplete{number of vertices}#/tikzpicture
\grComplete[options%keyvals]{number of vertices}#/tikzpicture
\grCirculant{number of vertices}{step1,step2,...}#/tikzpicture
\grCirculant[options%keyvals]{number of vertices}{step1,step2,...}#/tikzpicture
\grStar{number of vertices}#/tikzpicture
\grStar[options%keyvals]{number of vertices}#/tikzpicture
\grSQCycle{number of vertices}#/tikzpicture
\grSQCycle[options%keyvals]{number of vertices}#/tikzpicture
\grWheel{number of vertices}#/tikzpicture
\grWheel[options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\EdgeInGraphFromOneToComp#c,\grEmptyCycle#c,\grCycle#c,\grComplete#c,\grCirculant#c,\grStar#c,\grSQCycle#c,\grWheel#c
x=
y=
rotation=
RA=
prefix=
Math
#endkeyvals

\grLadder{number of vertices}#/tikzpicture
\grLadder[options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grLadder#c
RA=
RS=
prefix=
prefixx=
Math
#endkeyvals

\grPrism{number of vertices}#/tikzpicture
\grPrism[options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grPrism#c
RA=
RB=
prefix=
prefixx=
Math
#endkeyvals

\grCompleteBipartite{number1}{number2}#/tikzpicture
\grCompleteBipartite[options%keyvals]{number1}{number2}#/tikzpicture

#keyvals:\grCompleteBipartite#c
RA=
RB=
RS=
form=
prefix=
prefixx=
Math
#endkeyvals

\grTriangularGrid{number of vertices}#/tikzpicture
\grTriangularGrid[options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grTriangularGrid#c
RA=
form=
prefix=
Math
#endkeyvals

\grLCF[RA-number]{num1,num2,...}{number}#/tikzpicture

#keyvals:\grLCF#c
RA=
#endkeyvals

\tkzSetUpColors[options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpColors
background=#%color
text=#%color
#endkeyvals

\AssignVertexLabel{prefix}{name1,name2,...}#/tikzpicture
\AssignVertexLabel[options%keyvals]{prefix}{name1,name2,...}#/tikzpicture

#keyvals:\AssignVertexLabel
size=
color=#%color
Math
#endkeyvals

\grAndrasfai#/tikzpicture
\grBalaban#/tikzpicture
\grChvatal#/tikzpicture
\grCocktailParty#/tikzpicture
\grCrown#/tikzpicture
\grCubicalGraph#/tikzpicture
\grDesargues#/tikzpicture
\grDodecahedral#/tikzpicture
\grDoyle#/tikzpicture
\grEmptyGrid#/tikzpicture
\grEmptyLadder#/tikzpicture
\grEmptyStar#/tikzpicture
\grFolkman#/tikzpicture
\grFoster#/tikzpicture
\grFranklin#/tikzpicture
\grGeneralizedPetersen#/tikzpicture
\grGrotzsch#/tikzpicture
\grHeawood#/tikzpicture
\grIcosahedral#/tikzpicture
\grKonisberg#/tikzpicture
\grLevi#/tikzpicture
\grMcGee#/tikzpicture
\grMobiusKantor#/tikzpicture
\grMobiusLadder#/tikzpicture
\grOctahedral#/tikzpicture
\grPappus#/tikzpicture
\grPath#/tikzpicture
\grPetersen#/tikzpicture
\grRobertson#/tikzpicture
\grRobertsonWegner#/tikzpicture
\grTetrahedral#/tikzpicture
\grTutteCoxeter#/tikzpicture
\grWong#/tikzpicture
\grWriteExplicitLabel#*/tikzpicture
\grWriteExplicitLabels#*/tikzpicture
