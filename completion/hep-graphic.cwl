# hep-graphic package
# Matthew Bertucci 2023/07/16 for v1.0

#include:kvoptions
#include:tikz
#include:tikzlibraryexternal
#include:standalone

#keyvals:\usepackage/hep-graphic#c
plot#true,false
feynman#true,false
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
\includetikz{file}
\includetikz[width%plain]{file}
\includetikz*{file}
\includetikz*[width%plain]{file}
\includefeynman{file}