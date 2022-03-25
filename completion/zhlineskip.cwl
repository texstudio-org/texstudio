# zhlineskip package
# Matthew Bertucci 3/14/2022 for v1.0e

#include:kvoptions
#include:xintexpr
#include:etoolbox
#include:mathtools

#keyvals:\usepackage/zhlineskip#c
bodytextleadingratio=%<number%>
footnoteleadingratio=%<number%>
restoremathleading#true,false
UseMSWordMultipleLineSpacing#true,false
MSWordLineSpacingMultiple=%<number%>
MSWordSinglespaceRatio=%<number%>
#endkeyvals

\SetMathEnvironmentSinglespace{factor}
\RestoreMathEnvironmentLeading{envname}
\SetTextEnvironmentSinglespace{factor}
\RestoreTextEnvironmentLeading{envname}