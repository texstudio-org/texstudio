# gentium-otf package
# Matthew Bertucci 2025/07/15 for v1.01

#include:iftex
#include:xkeyval
#include:fontspec

#keyvals:\usepackage/gentium-otf#c
book
medium
ScaleRM=%<factor%>
math=%<font name%>
mathFeatures={%<fontspec features%>}
sans=%<font name%>
sansFeatures={%<fontspec features%>}
mono=%<font name%>
monoFeatures={%<fontspec features%>}
defaultfeatures={%<fontspec features%>}
#endkeyvals

\GentiumRegular
\GentiumMedium
\ExtraBold

\Lctosc{text}
\LCtoSC-
\LCtoSC+
\Lctosmcp{text}
\LCtoSMCP-
\LCtoSMCP+
\Lliga{text}
\LLIGA-
\LLIGA+
\Lss{num1}{num2}{text}
\LSS{num1}{num2}
\Lcv{num1}{num2}{text}
\LCV{num1}{num2}
\Lcv[opt]{num1}{num2}{text}
\LCV[opt]{num1}{num2} 
\Lsup{text}
\LSUP-
\LSUP+
\Lsub{text}
\LSUB-
\LSUB+
\Lfrac{fraction}
\LFRAC-
\LFRAC+

# not documented
\Llang{arg}#S
