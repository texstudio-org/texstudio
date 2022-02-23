# tikz-among-us-watermark-eso-pic package
# Matthew Bertucci 2/22/2022 for v1.0.1

#include:tikz-among-us
#include:eso-pic
#include:kvoptions

#keyvals:\usepackage/tikz-among-us-watermark-eso-pic#c
cor=#%color
type=#0,1
FG#true,false
BG#true,false
#endkeyvals

\ifFG#*
\FGtrue#*
\FGfalse#*
\myboxAmongUs