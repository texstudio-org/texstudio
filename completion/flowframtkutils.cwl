# flowframtkutils package
# Matthew Bertucci 2026/05/08 for v2.2

#include:pgf
#include:graphicx

#keyvals:\usepackage/flowframtkutils#c
outline#true,false
textpath#true,false
#endkeyvals

\FlowframTkBeginScopeIfGroup{class name}
\flowframtkencapobject{n}{Java class}{description}{tag}{pgf point}{width}{height}{object}
\flowframtkendobject{n}{Java class}{description}{tag}{pgf point}{width}{height}
\FlowframTkEndScopeIfGroup{class name}
\flowframtkimageinfo{keyvals}
\flowframtkimgtitlechar{char}{PDF replacement}
\flowframtkNoRagged
\FlowframTkScopeIfGroup{class name}{object}
\flowframtkSetCreationDate{PDF date}
\flowframtkSetTitle{title%text}
\flowframtkstartobject{n}{Java class}{description}{tag}{pgf point}{width}{height}
\FlowFramTkUtilsOverlayEncapSetup{keyvals}
\FlowFramTkUtilsSetOverlayEncap
\FlowFramTkUtilsSetOverlayEncap[keyvals]
\includeteximage[keyvals]{file}
\includeteximage{file}
\jdrimagebox{image code}
\jdroutline{pdf-trans code}{pst-char code}{text}

# not documented
\FlowFramTkDeclareKeys{arg}#S
\flowframtkMakeDFHeaderFooter#S
\flowframtkNewDynamicStyle{arg1}{arg2}#S
\flowframtkNewFrameBorder{arg1}{arg2}#S
\flowframtkpdftransmod#S
\flowframtkSetDynamicEvenFoot{arg}#S
\flowframtkSetDynamicEvenHead{arg}#S
\flowframtkSetDynamicOddEvenFoot{arg1}{arg2}#S
\flowframtkSetDynamicOddEvenHead{arg1}{arg2}#S
\flowframtkSetDynamicOddFoot{arg}#S
\flowframtkSetDynamicOddHead{arg}#S
\FlowFramTkSetKey{arg}#S
\flowframtkUseDynamicStyleCsName{arg}#S
\flowframtkUseDynamicStyle{arg}#S
\flowframtkUseFrameBorderCsName{arg}#S
\flowframtkUseFrameBorderCs{arg}#S