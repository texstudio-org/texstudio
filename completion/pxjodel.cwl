# pxjodel package
# Matthew Bertucci 2022/07/22 for v0.3

#include:xkeyval
#include:ifuptex
#include:otf

#keyvals:\usepackage/pxjodel#c
prefix=%<string%>
# options passed to otf package
nomacros
noreplace
bold
expert
deluxe
multi
burasage
uplatex
autodetect
jis2004
scale=%<factor%>
#endkeyvals

#ifOption:expert
\rubydefault#*
\rubyfamily
\rubykatuji
#endif

#ifOption:deluxe
\mgdefault#*
\propdefault#*
\ebdefault#*
\ltdefault#*
\mathmg{text%plain}#m
\mgfamily
\textmg{text}
\propshape
\ebseries
\ltseries
#endif

#ifOption:multi
#include:mlutf
#include:mlcid
#endif

#ifOption:uplatex
#include:uplatex
#endif

\bxDebug{arg}#S