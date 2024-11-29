# hep-graphic package
# Matthew Bertucci 2024/11/29 for v1.3

#include:kvoptions
#include:tikz
#include:tikzlibraryexternal
#include:tikzscale

#keyvals:\usepackage/hep-graphic#c
plot#true,false
feynman#true,false
extern=
#endkeyvals

#ifOption:plot
#include:hep-plot
#endif
#ifOption:plot=true
#include:hep-plot
#endif

#ifOption:feynman
#include:hep-feynman
#endif
#ifOption:feynman=true
#include:hep-feynman
#endif

\graphicpath{path%definition}
\includepgf{file}
\includepgf[width%plain]{file}
\includepgf*{file}
\includepgf*[width%plain]{file}
\includefeynman{file}
