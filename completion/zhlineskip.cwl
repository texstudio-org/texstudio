# zhlineskip package
# Matthew Bertucci 2026/06/29 for v1.0f

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
#endkeyvals

\SetMathEnvironmentSinglespace{factor}
\RestoreMathEnvironmentLeading{envname}
\SetTextEnvironmentSinglespace{factor}
\RestoreTextEnvironmentLeading{envname}