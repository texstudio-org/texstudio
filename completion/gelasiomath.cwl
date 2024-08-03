# gelasiomath package
# Matthew Bertucci 2024/07/07 for v1.0

#include:iftex
#include:etoolbox
#include:xkeyval
#include:ifthen
#include:newtx

#keyvals:\usepackage/gelasiomath#c
scale=%<factor%>
scosf
# other options passed to newtx
#endkeyvals

\textSC{text}
\textsmde{text}

# not documented
\capsescape{text}#S
\geltextfrac{arg1}{arg2}#S
\geltextfrac[opt]{arg1}{arg2}#S
\textULC{text}#S