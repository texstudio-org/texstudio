# tikzscale package
# Matthew Bertucci 1/29/2022 for v0.2.6

#include:graphicx
#include:etoolbox
#include:pgfkeys
#include:letltxmacro
#include:xstring

\pgfmathsetglobalmacro{cmd}{math expr}#*d
\ifTikzLibraryLoaded{library}{true}{false}#*
\ifExternalizationLoaded{true}{false}#*
\ifedefequal{expr1}{expr2}{true}{false}#*
\edocsvlist{csvlist}#*
\eforcsvlist{handler}{csvlist}#*
\forgrouplist{handler}{grouplist}#*
\grouplistbreak#*
\eforgrouplist{handler}{grouplist}#*
\elseif{%<expr%>}{%<true%>}%<{false}...%>#*
\IfNoValueOrSplitEmptyTF{arg}{true}{false}#*
\maxTestIterations#*
\requestedSize#S
\requestedWidth#S
\requestedHeight#S
\measuredFirst#S
\measuredSecond#S
\fixedSize#S
\measuredFinal#S
\pgfexternalsize#S
\pgfexternalwidth#S
\pgfexternalheight#S
\originalRequestedSize#S
\fileName#S
\content#S
\widthDifference#S
\heightDifference#S
\dimension#S
\variable#S
\measuredSize#S
\sizeDifference#S