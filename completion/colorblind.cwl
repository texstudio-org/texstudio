# colorblind package
# Matthew Bertucci 2024/12/23 for v1.1

#include:xcolor
#include:ifthen
#include:tikz
#include:tikzlibrarymath

#keyvals:\usepackage/colorblind#c
Tol
OkabeIto
pgf
no-tikz
keep-defaults
#endkeyvals

#ifOption:pgf
#include:pgfplots
#endif

\drawScheme{scheme}
\drawSchemeC{scheme}
\drawSchemeC[width]{scheme}

# not documented
\theColorNum#S
