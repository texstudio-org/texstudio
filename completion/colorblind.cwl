# colorblind package
# Matthew Bertucci 2024/05/14 for v1.0

#include:xcolor
#include:ifthen
#include:tikz
#include:tikzlibrarymath
#include:pgfplots

#keyvals:\usepackage/colorblind#c
Tol
OkabeIto
#endkeyvals

\drawScheme{scheme}
\drawSchemeC{scheme}
\drawSchemeC[width]{scheme}

# not documented
\theColorNum#S