# heros-otf package
# Matthew Bertucci 2022/10/14 for v0.01

#include:iftex
#include:xkeyval
#include:textcomp
#include:fontspec

#keyvals:\usepackage/heros-otf#c
lining
oldstyle
condensed
default
tabular
proportional
ScaleSF=%<factor%>
defaultfeatures={%<font features%>}
#endkeyvals

\heros
\heroscn
\herosOsF
\heroscnOsF
\herosTLF
\heroscnTLF

\Lctosc{text}
\LCtoSC+
\LCtoSC-
\Lctosmcp{text}
\LCtoSMCP+
\LCtoSMCP-
\Lliga{text}
\LLIGA+
\LLIGA-
\Lhlig{text}
\LHLIG+
\LHLIG-
\Ldlig{text}
\LDLIG+
\LDLIG-
\Lcpsp{text}
\LCPSP+
\LCPSP-
\Lsalt{text}
\LSALT+
\LSALT-
\Lss%<<x><x>%>{%<text%>}
\LSS%<<x><x>%>

# not documented
\sufigures#*
\textsup{text}#*
\textinit{text}#S
\Lsup{text}#*
\Lsinf{text}#*
\Land#*
\Lcase{text}#*
\LCASE+#*
\LCASE-#*
\Lfrac{text}#*
\LFRAC+#*
\LFRAC-#*
