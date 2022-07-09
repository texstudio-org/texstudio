# inlinelabel package
# Matthew Bertucci 2022/07/09 for v1.2.1

#include:amsmath

#keyvals:\usepackage/inlinelabel#c
nospace
circled
luacircled
#endkeyvals

#ifOption:circled
#include:otf
#include:refcount
\circledref{label}#r
\equationref{label}#r
#endif

#ifOption:luacircled
#include:luatexja-otf
#include:refcount
\circledref{label}#r
\equationref{label}#r
#endif

\inlinelabel{label}#l
\inlinelabel*{label}#l
\equationreset
