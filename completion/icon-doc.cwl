# icon-doc package
# Matthew Bertucci 2022/05/10 for v1.0

#include:ifxetex
#include:shellesc
#include:web
#include:eforms

#keyvals:\usepackage/icon-doc#c
useacrobat
!useacrobat
twice
#endkeyvals

\ifdpsuseacrobat#S
\dpsuseacrobattrue#S
\dpsuseacrobatfalse#S
\ifdpscomptwice#S
\dpscomptwicetrue#S
\dpscomptwicefalse#S
\wrtPkg#*
\wrticonbody#*
\IWB{arg}#*
\IWP{arg}#*
\begin{verbatimwrite}#S
\end{verbatimwrite}#S
\begin{icondoc}#*
\end{icondoc}#*
\addToPageList{arg}#*
\createRequiredIcons{number}{file}#i
\dpsInputContent
\defineJSjsR#*
\execExplode#*
\wrtPageList#*
\pagelist#*