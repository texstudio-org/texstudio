# adigraph package
# Matthew Bertucci 2/15/2022 for v1.7.1

#include:etoolbox
#include:fp
#include:xstring
#include:tikz
#include:tikzlibrarycalc

\NewAdigraph{name}{nodes}
\NewAdigraph{name}{nodes}{edges}
\NewAdigraph{name}{nodes}{edges}[edge style]
\RenewAdigraph{name}{nodes}
\RenewAdigraph{name}{nodes}{edges}
\RenewAdigraph{name}{nodes}{edges}[edge style]
\EnableAdigraphs
\DisableAdigraphs

\AdigraphApplyKleenePlusEdgeBuilder{element}#*
\AdigraphBackwardPathColor#*
\AdigraphBackwardPathWidth#*
\AdigraphBuildEdge{edge nodes}{weight}{label}{label pos}#*
\AdigraphBuildEdgeWrapper{edge nodes}{weight}{label}{label pos}#*
\AdigraphBuildNode{node name}{list of coords}{label}#*
\AdigraphBuildNodeWrapper{node name}{list of coords}{label}#*
\AdigraphBuildPath{nodes}{units}{colors}{widths}#*
\AdigraphCalculateInclination{arg1}{arg2}{arg3}#*
\AdigraphCalculateOrientation{arg1}{arg2}{arg3}#*
\AdigraphCountPaths{arg}#*
\AdigraphCurrentElaboratingEdge#*
\AdigraphCurrentNode#*
\AdigraphCutBuilder{arg}#*
\AdigraphCyan#*
\AdigraphDefaultColor#*
\AdigraphDefaultWidth#*
\AdigraphDrawEdge{nodeID1}{nodeID2}#*
\AdigraphDrawNode{nodeID}#*
\AdigraphEdgeBuilder{arg}#*
\AdigraphEdgeDrawer{arg}#*
\AdigraphEdgeList#*
\AdigraphElaboratePathColors{arg1}{arg2}#*
\AdigraphElaboratePathWidth{forward width}{backward width}#*
\AdigraphElaboratePath{arg1}{arg2}#*
\AdigraphExecuteCutBuilder{arg1}{arg2}{arg3}#*
\AdigraphFirstEdgeRenormalizer{arg}#*
\AdigraphFirstNode#*
\AdigraphForwardPathColor#*
\AdigraphForwardPathWidth#*
\AdigraphGenerateNodeName{arg}#*
\AdigraphKleenePlusEdgeBuilder{arg}#*
\AdigraphKleeneStarEdgeBuilder{arg}#*
\AdigraphLastParsedNode#*
\AdigraphMemorizeEdge{arg1}{arg2}#*
\AdigraphMemorizeNode{arg}#*
\AdigraphNodeBuilder{arg}#*
\AdigraphNodeCounterSecondWrapper{arg}#*
\AdigraphNodeCounterWrapper{arg1}{arg2}{arg3}{arg4}#*
\AdigraphNodeCounter{arg}#*
\AdigraphNodeList#*
\AdigraphNodeName#*
\AdigraphNodesCounter{arg}#*
\AdigraphPathBuilder{node1}{node2}{units}{forward color}{backward color}{forward width}{backward width}#*
\AdigraphProcessAugmentingPathsList{arg}#*
\AdigraphProcessAugmentingPaths{arg}#*
\AdigraphProcessCuts{arg}#*
\AdigraphProcessEdges{arg}#*
\AdigraphProcessNodes{arg}#*
\AdigraphProcessPaths{arg}#*
\AdigraphRed#*
\AdigraphRom{arg}#*
\AdigraphSecondEdgeRenormalizer{arg}#*
\AdigraphSecondNode#*
\AdigraphSimpleSum{num1}{num2}{cmd}#*d
\AdigraphTempList#*
\AdigraphTextualZero#*
\AdigraphTwinEdgeWeight#*
\AdigraphVersionNumber#S
\AdigraphWeightA#*
\AdigraphWeightB#*
\AdigraphZero#*
\Adigraph{vertices}{edges}{paths}{cuts}{current paths}{style}#*
\myCosSum#S
\mySinSum#S
\sumOfOrientations{arg1}#*
\theAdigraphAdjacentNodes#*
\theAdigraphCurrentNodeCounter#*
\theAdigraphCurrentPathNumber#*
\theAdigraphNumberOfPaths#*
\theAdigraphTotalNodeCounter#*
