# ps-trees package
# Matthew Bertucci 2022/05/25 for v2.0

#include:tree-dvips

\begin{treetab}{cols%plain}#\tabular
\end{treetab}
\begin{psTree}#*
\end{psTree}#*
\Node{nodename}{object%text}
\Node[n]{nodename}{object%text}
\NodeWidthNo{n}
\NodeNo{n}{nodename}
\NodeZ{nodename}{object%text}
\nodeZ{nodename}{object%text}
\NodeTNo{n}{nodename}
\NodeTZNo{n}{nodename}
\NodeZTNo{n}{nodename}
\MinNodeWidth#*
\NodeTZ{nodename}{object%text}
\NodeT{nodename}{object%text}
\NodeZT{nodename}{object%text}#*
\NodeWidth#*

# not documented
\AddToToks{arg1}{arg2}#*
\AllNodes#*
\CollectedNodes#*
\CollectedTNodes#*
\Compare{arg}#*
\ConnectNode{arg1}{arg2}#*
\ConnectTNode{arg1}{arg2}#*
\EveryNode{arg}#*
\EveryTNode{arg}#*
\ifIsElement#*
\IfIsNodeName{arg}#*
\ifTNode#*
\IsElementfalse#*
\IsElementOf{arg1}{arg2}#*
\IsElementtrue#*
\NoNodeWarning{text}#*
\oldnode{nodename}{object%text}#S
\OptionNode[n]{nodename}{object%text}#*
\OptionNodeNo{n}[opt]{nodename}#*
\TestAndAdd{arg}#*
\TNodefalse#*
\TNodetrue#*
\xx#S
\yy#S