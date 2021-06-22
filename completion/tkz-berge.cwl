# tkz-berge package
# Matthew Bertucci 6/21/2021

#include:tkz-graph

\grEmptyPath[local options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grEmptyPath#c
RA=
RS=
prefix=
Math
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

\EdgeInGraphFromOneToComp[local options%keyvals]{prefix}{number of vertices}{from}#/tikzpicture

\grEmptyCycle[local options%keyvals]{number of vertices}#/tikzpicture
\grCycle[local options%keyvals]{number of vertices}#/tikzpicture
\grComplete[local options%keyvals]{number of vertices}#/tikzpicture
\grCirculant[local options%keyvals]{number of vertices}{step1,step2,...}#/tikzpicture
\grStar[local options%keyvals]{number of vertices}#/tikzpicture
\grSQCycle[local options%keyvals]{number of vertices}#/tikzpicture
\grWheel[local options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\EdgeInGraphFromOneToComp#c,\grEmptyCycle#c,\grCycle#c,\grComplete#c,\grCirculant#c,\grStar#c,\grSQCycle#c,\grWheel#c
x=
y=
rotation=
RA=
prefix=
Math
#endkeyvals

\grLadder[local options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grLadder#c
RA=
RS=
prefix=
prefixx=
Math
#endkeyvals

\grPrism[local options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grPrism#c
RA=
RB=
prefix=
prefixx=
Math
#endkeyvals

\grCompleteBipartite[local options%keyvals]{number1}{number2}#/tikzpicture

#keyvals:\grCompleteBipartite#c
RA=
RB=
RS=
form=
prefix=
prefixx=
Math
#endkeyvals

\grTriangularGrid[local options%keyvals]{number of vertices}#/tikzpicture

#keyvals:\grTriangularGrid#c
RA=
form=
prefix=
Math
#endkeyvals

\grLCF{RA-number}{num1,num2,...}{number}#/tikzpicture

\tkzSetUpColors[[local options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpColors
background=#%color
text=#&color
#endkeyvals

\AssignVertexLabel[local options%keyvals]{prefix}{name1,name2,...}#/tikzpicture

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
\grWriteExplicitLabel#/tikzpicture
\grWriteExplicitLabels#/tikzpicture