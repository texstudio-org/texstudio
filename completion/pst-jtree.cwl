# pst-jtree package
# Matthew Bertucci 2022/08/15 for v2.6

#include:pstricks
#include:pst-node
#include:pst-xkey

\jtree
\jtree[options%keyvals]
\endjtree
\begin{jtree}#*
\begin{jtree}[options%keyvals]#*
\end{jtree}#*

\defbranch<name>(height)(slope)
\deftriangle<name>(height)(slopeA)(slopeB)
\triline{text%plain}
\triwd
\defvartriangle<name>(height)
\jtlong
\jtshort
\jtwide
\jtbig
\jtjot
\jteverytree={%<code%>}
\jtEverytree={%<code%>}
\jteverylabel={%<code%>}
\blank
\brokenbranch
\etcbranch
\etc
\stuff[tag]
\defstuff[tag]{code}
\multiline
\endmultiline
\begin{multiline}#*
\end{multiline}#*
\psinterpolate(node1)(node2){num}{node name}#*
\elc{text%plain}
\elc[options%keyvals]{text%plain}
\adjoinop#*

# not documented
\expandaftertwice#S
\filedate#S
\fileversion#S
\jRestoreCat{arg}#S
\jStoreCat{arg}#S
\jTempChangeCat{arg1}{arg2}#S
\JTreeLoaded#S
\jtreevalue{arg1}{arg2}{arg3}#*
\NormalLabelStrut#*
\OtherAt#S
\testlabel{arg}#S

# deprecated
\start#S
\adjoin#S