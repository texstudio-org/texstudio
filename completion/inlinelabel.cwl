# inlinelabel package
# Matthew Bertucci 2022/06/29 for v1.0

#include:amsmath

#keyvals:\usepackage/inlinelabel#c
circled
#endkeyvals

#ifOption:circled
#include:otf
#include:refcount
\circledref{label}#r
\equationref{label}#r
#endif

\inlinelabel{label}#l
\inlinelabel*{label}#l