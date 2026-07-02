# zhlineskip package
# Matthew Bertucci 2026/07/01 for v1.0g

#include:kvoptions
#include:xintexpr
#include:etoolbox
#include:mathtools

#keyvals:\usepackage/zhlineskip#c
bodytextleadingratio=%<number%>
footnoteleadingratio=%<number%>
restoremathleading#true,false
MSWordLineSpacingMultiple=%<number%>
MSWordSinglespaceRatio=%<number%>
quiet
#endkeyvals

\SetMathEnvironmentSinglespace{factor}
\RestoreMathEnvironmentLeading{envname}
\SetTextEnvironmentSinglespace{factor}
\RestoreTextEnvironmentLeading{envname}