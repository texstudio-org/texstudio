# pst-uml package
# Matthew Bertucci 2026/09/04 for v0.83

#include:pstricks
#include:pst-node
#include:pst-tree
#include:multido
#include:calc
#include:ifthen
#include:graphicx
#include:pst-xkey

\umlActor[options%keyvals]{text}
\umlActor{text}
\umlCase[options%keyvals]{body}
\umlCasePut[options%keyvals]{coord}{node}{body}
\umlCasePut{coord}{node}{body}
\umlCase{body}
\umlClass[options%keyvals]{title%text}{body}
\umlClass{title%text}{body}
\umlEmptyBox{length}{height}
\umlNote[options%keyvals]{text}
\umlNote{text}
\umlPutStateIn[options%keyvals]{coord}{node}
\umlPutStateIn{coord}{node}
\umlPutStateOut[options%keyvals]{coord}{node}
\umlPutStateOut{coord}{node}
\umlStack[options%keyvals]{body}
\umlStack{body}
\umlState[options%keyvals]{title%text}{body}
\umlStateIn
\umlStateIn[options%keyvals]
\umlStateOut
\umlStateOut[options%keyvals]
\umlState{title%text}{body}
\umlStereoType{type}
\umlTriLeft
\umlTriLeft[options%keyvals]
\umlTriRight
\umlTriRight[options%keyvals]

\incrX#*
\incrY#*
\moveE#*
\moveN#*
\moveS#*
\moveW#*
\ncputicon[options%keyvals]{icon}#*
\ncputicon{icon}#*
\ResetXY#*
\rputXY[options%keyvals]{body}#*
\rputXY{body}#*
\SetXY{arg}#*
\SetX{arg}#*
\SetY{arg}#*

\ShowPosition#S
\ShowPosition[opt]#S
\umlPutCase[options%keyvals]{coord}{node}{body}#S
\umlPutCase{coord}{node}{body}#S
\umlSaveClass[options%keyvals]{arg1}{arg2}#S
\umlSaveClass{arg1}{arg2}#S
\umlUseBox{arg}#S