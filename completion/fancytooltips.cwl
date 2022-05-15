# fancytooltips package
# Matthew Bertucci 2022/05/13 for v1.12

#include:graphicx
#include:xkeyval
#include:atbegshi
#include:eforms
#include:ocg
#include:transparent
#include:eso-pic

#keyvals:\usepackage/fancytooltips#c
createtips
dvips
noextratext
movetips
mouseover
inactive
active
fg
filename=%<file name%>
pages=%<number%>
blur
blur=%<factor%>
fixcolor
preview
previewall
nosoap
tooltipmark=#1,2,3,4
debug
#endkeyvals

\keytip{keyword}
\tooltip{text}{keyword or pagenumber}
\tooltip*{text}{keyword or pagenumber}
\TooltipExtratext#*
\TooltipFilename#*
\tooltipanim{text}{start}{end}
\tooltipanim*{text}{start}{end}
\delayinterval#*
\TooltipRefmark#*

# not documented
\FindTipNumber{arg1}#*
\SaveTooltipExtratext#*
\TipNumber#*
\TipNumberA#*
\TipNumberB#*
\TooltipHidden#*
\TooltipPages#*
\TooltipPage{arg1}{arg2}#*
\act#S
\checkTipNumber{arg1}#*
\eqIconDefaults#*
\eqIconFTT{arg1}{arg2}{arg3}{arg4}#*
\everyeqIcon{arg1}#*
\fancytempA#S
\fancytempAA#S
\fancytempAAA#S
\fancytempB#S
\fancytooltipsdebugmsg#*
\frametip#*
\oldref{label}#Sr
\templabel#S
\tooltipname{arg1}{arg2}#*
\tooltippage#*