# paracolrule package
# Matthew Bertucci 2026/08/23 for v0.1.0

#include:paracol
#include:etoolbox

#keyvals:\usepackage/paracolrule#c
tikz#true,false
#endkeyvals

#ifOption:tikz
#include:tikz
#endif
#ifOption:tikz=true
#include:tikz
#endif

\ParacolRuleSetup{keyvals}
\ParacolRuleSetRenderer{macro}