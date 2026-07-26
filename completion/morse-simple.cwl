# morse-simple package
# Matthew Bertucci 2026/07/26 for v1.0

#include:graphicx
#include:color

#keyvals:\usepackage/morse-simple#c
thickness=##L
height=##L
ditwidth=##L
dahwidth=##L
intracharfactor=%<factor%>
intercharfactor=%<factor%>
interwordfactor=%<factor%>
grayshade=%<factor%>
ditdot
dotscale=%<factor%>
dotraise=##L
#endkeyvals

\cwMessage{text}
\cwWord{word%text}
\morse{text}

\cwDah#*
\cwDit#*
\cwDitDash#*
\cwDitDot#*
\cwEnlargeDah#*
\cwEnlargeDah[factor]#*
\cwEnlargeDit#*
\cwEnlargeDit[factor]#*

\cwGetLetter{arg}#S
\getMathAxisHgt{arg}#S
\mathAxisHgt#S
\rectangle{arg1}{arg2}#S