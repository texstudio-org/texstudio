# tkz-berge package
# Matthew Bertucci 2026/10/24 for v2.20c

#include:tkz-graph

\grEmptyPath{number of vertices}
\grEmptyPath[options%keyvals]{number of vertices}
\grCrown{number of vertices}
\grCrown[options%keyvals]{number of vertices}

#keyvals:\grEmptyPath
RA=##L
RS=##L
prefix=%<prefix%>
Math#true,false
form=%<integer%>
#endkeyvals

\EdgeInGraphLoop{prefix}{number of vertices}
\EdgeInGraphLoop*{prefix}{number of vertices}
\EdgeInGraphSeq{prefix}{start}{end}
\EdgeInGraphMod{prefix}{number of vertices}{add}
\EdgeInGraphMod*{prefix}{number of vertices}{add}{start}{step}
\EdgeInGraphModLoop{prefix}{number of vertices}{add}{start}

\EdgeIdentity{prefix1}{prefix2}{number of vertices}
\EdgeIdentity*{prefix1}{prefix2}{vertex1,vertex2,...}

\EdgeFromOneToAll{prefix1}{prefix2}{from}{number of vertices}
\EdgeFromOneToSeq{prefix1}{prefix2}{from}{start}{end}
\EdgeFromOneToSel{prefix1}{prefix2}{from}{vertex1,vertex2,...}
\EdgeFromOneToComp{prefix1}{prefix2}{from}{number of vertices}

\EdgeMod{prefix1}{prefix2}{number of vertices}{step}
\EdgeMod*{prefix1}{prefix2}{number of vertices}{step1}{step2}
\EdgeDoubleMod{prefix1}{numofvertices1}{start1}{add1}{prefix2}{numofvertices2}{start2}{add2}{end}

\EdgeInGraphFromOneToComp{prefix}{number of vertices}{from}
\EdgeInGraphFromOneToComp[options%keyvals]{prefix}{number of vertices}{from}

\grAndrasfai[options%keyvals]{number}
\grAndrasfai{number}
\grBalaban
\grBalaban[options%keyvals]
\grChvatal
\grChvatal[options%keyvals]
\grCirculant[options%keyvals]{number of vertices}{step1,step2,...}
\grCirculant{number of vertices}{step1,step2,...}
\grComplete[options%keyvals]{number of vertices}
\grComplete{number of vertices}
\grCubicalGraph
\grCubicalGraph[options%keyvals]
\grCycle[options%keyvals]{number of vertices}
\grCycle{number of vertices}
\grDodecahedral
\grDodecahedral[options%keyvals]
\grDoyle
\grDoyle[options%keyvals]
\grEmptyCycle[options%keyvals]{number of vertices}
\grEmptyCycle{number of vertices}
\grEmptyGrid[options%keyvals]{m}{n}
\grEmptyGrid{m}{n}
\grEmptyLadder[options%keyvals]{number of vertices}
\grEmptyLadder{number of vertices}
\grEmptyStar[options%keyvals]{number of vertices}
\grEmptyStar{number of vertices}
\grGeneralizedPetersen[options%keyvals]{number1}{number2}
\grGeneralizedPetersen{number1}{number2}
\grGrid[options%keyvals]{m}{n}
\grGrid{m}{n}
\grGrotzsch
\grGrotzsch[options%keyvals]
\grHeawood
\grHeawood[options%keyvals]
\grIcosahedral
\grIcosahedral[options%keyvals]
\grKonisberg
\grKonisberg[options%keyvals]
\grLevi
\grLevi[options%keyvals]
\grMobiusKantor
\grMobiusKantor[options%keyvals]
\grMobiusLadder[options%keyvals]{number of vertices}
\grMobiusLadder{number of vertices}
\grOctahedral
\grOctahedral[options%keyvals]
\grPappus
\grPappus[options%keyvals]
\grPetersen
\grPetersen[options%keyvals]
\grRobertson
\grRobertson[options%keyvals]
\grRobertsonWegner
\grRobertsonWegner[options%keyvals]
\grSQCycle[options%keyvals]{number of vertices}
\grSQCycle{number of vertices}
\grStar[options%keyvals]{number of vertices}
\grStar{number of vertices}
\grTetrahedral
\grTetrahedral[options%keyvals]
\grWheel[options%keyvals]{number of vertices}
\grWheel{number of vertices}

#keyvals:\EdgeInGraphFromOneToComp,\grAndrasfai,\grBalaban,\grChvatal,\grCubicalGraph,\grDodecahedral,\grDoyle,\grCycle,\grComplete,\grCirculant,\grEmptyCycle,\grEmptyGrid,\grEmptyLadder,\grEmptyStar,\grGeneralizedPetersen,\grGrid,\grGrotzsch,\grHeawood,\grIcosahedral,\grKonisberg,\grLevi,\grMobiusKantor,\grMobiusLadder,\grOctahedral,\grPappus,\grPetersen,\grRobertson,\grRobertsonWegner,\grSQCycle,\grStar,\grTetrahedral,\grWheel
rotation=%<degrees%>
RA=%<number%>
prefix=%<prefix%>
Math#true,false
#endkeyvals

#keyvals:\grEmptyCycle,\grCycle,\grComplete,\grCirculant,\grStar,\grSQCycle,\grWheel
x=%<number%>
y=%<number%>
#endkeyvals

\grLadder{number of vertices}
\grLadder[options%keyvals]{number of vertices}

#keyvals:\grLadder
RA=%<number%>
RS=%<number%>
prefix=%<prefix%>
prefixx=%<prefix%>
Math#true,false
#endkeyvals

\grCocktailParty{number of vertices}
\grCocktailParty[options%keyvals]{number of vertices}
\grPath{number of vertices}
\grPath[options%keyvals]{number of vertices}

#keyvals:\grPath,\grCocktailParty
RA=%<number%>
RS=%<number%>
prefix=%<prefix%>
prefixx=%<prefix%>
Math#true,false
#endkeyvals

\grPrism{number of vertices}
\grPrism[options%keyvals]{number of vertices}

#keyvals:\grPrism
RA=%<number%>
RB=%<number%>
prefix=%<prefix%>
prefixx=%<prefix%>
Math#true,false
#endkeyvals

\grCompleteBipartite{number1}{number2}
\grCompleteBipartite[options%keyvals]{number1}{number2}

#keyvals:\grCompleteBipartite
RA=%<number%>
RB=%<number%>
RS=%<number%>
prefix=%<prefix%>
prefixx=%<prefix%>
Math#true,false
#endkeyvals

\grTriangularGrid{number of vertices}
\grTriangularGrid[options%keyvals]{number of vertices}

#keyvals:\grTriangularGrid
RA=%<number%>
form=%<integer%>
prefix=%<prefix%>
Math#true,false
#endkeyvals

\grDesargues
\grDesargues[options%keyvals]
\grDick
\grDick[options%keyvals]
\grFolkman
\grFolkman[options%keyvals]
\grFoster
\grFoster[options%keyvals]
\grFranklin
\grFranklin[options%keyvals]
\grHarries
\grHarries[options%keyvals]
\grLCF[options%keyvals]{num1,num2,...}{number}
\grMcGee
\grMcGee[options%keyvals]
\grNauru
\grNauru[options%keyvals]
\grTutteCoxeter
\grTutteCoxeter[options%keyvals]
\grWong
\grWong[options%keyvals]

#keyvals:\grDesargues,\grDick,\grFolkman,\grFoster,\grFranklin,\grHarries,\grLCF,\grMcGee,\grNauru,\grWong,\grTutteCoxeter
RA=%<number%>
#endkeyvals

\AssignVertexLabel{prefix}{name1,name2,...}
\AssignVertexLabel[options%keyvals]{prefix}{name1,name2,...}

#keyvals:\AssignVertexLabel
size=%<size command%>
color=#%color
Math#true,false
#endkeyvals

\grHypercube{number of vertices}
\grHypercube[options%keyvals]{number of vertices}
\grTree{k}{depth}
\grTree[options%keyvals]{k}{depth}

#keyvals:\grHypercube,\grTree
RA=%<number%>
RB=%<number%>
RS=%<number%>
prefix=%<prefix%>
prefixx=%<prefix%>
Math#true,false
#endkeyvals

\grWriteExplicitLabel
\grWriteExplicitLabels

# not documented
\EdgeIdentityNoStar#S
\EdgeIdentityStar#S
\EdgeInGraphLoopNoStar#S
\EdgeInGraphLoopStar#S
\EdgeInGraphModLoop#S
\EdgeInGraphModNoStar#S
\EdgeInGraphModStar#S
\EdgeModNoStar#S
\EdgeModStar#S
\EdgeSequence#S
\grEdgeForTree#S
\grEmptyCycleNoStar#S
\grEmptyCycleStar#S
\grEmptyPathNoStar#S
\grEmptyPathStar#S
\grLabelSep#S
\grMathSep#S
\grStartwo#S
\grSubtreeOfCage#S