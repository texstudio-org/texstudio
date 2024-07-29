# bonum-otf package
# Matthew Bertucci 2024/07/25 for v0.01

#include:iftex
#include:xkeyval
#include:unicode-math

#keyvals:\usepackage/bonum-otf#c
lining
oldstyle
libertinus
tabular
proportional
ScaleRM=%<factor%>
defaultfeatures={%<font features%>}
#endkeyvals

\bonum
\bonumOsF
\bonumTLF

\Lss%<<x><x>%>{%<text%>}
\LSS%<<x><x>%>
\Lctosc{text}
\LCtoSC+
\LCtoSC-
\Lctosmcp{text}
\LCtoSMCP+
\LCtoSMCP-
\Lsalt{text}
\LSALT+
\LSALT-
\Lliga{text}
\LLIGA+
\LLIGA-
\Lhlig{text}
\LHLIG+
\LHLIG-
\Ldlig{text}
\LDLIG+
\LDLIG-

# not documented
\sufigures#*
\textsup{text}#*
\textinit{text}#*
\Lsup{text}#*
\Lsinf{text}#*
\Land#*
\Lcase{text}#*
\LCASE+#*
\LCASE-#*
\Lfrac{text}#*
\LFRAC+#*
\LFRAC-#*
\Lcpsp{text}#*
\LCPSP+#*
\LCPSP-#*