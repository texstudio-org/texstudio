# sizeredc package
# Matthew Bertucci 2022/05/15 for v5.01

#include:epic

\changeunitlength{length}
\ifsizereduction#*
\reducedsizepicture
\reducedsizepicture[unit length]
\sizereductionfalse#*
\sizereductiontrue#*
\substfontsize#*
\thicklines
\thinlines

# not documented
\begin{sfpicture}#S
\DIVIDE{arg1}{arg2}{arg3}#S
\dotorline#S
\end{sfpicture}#S
\ifseifuflag#S
\LineTemp#S
\oldlineslope#S
\RR#S
\seifuflagfalse#S
\seifuflagtrue#S