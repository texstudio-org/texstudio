# jlreq-deluxe package
# Matthew Bertucci 2022/07/26 for v0.4.0

#include:l3keys2e
#include:pxjodel

#keyvals:\usepackage/jlreq-deluxe#c
hanging_punctuation#true,false
zenkakunibu_nibu#true,false
# options passed to pxjodel pcakage
prefix=%<string%>
# options passed to otf package
nomacros
noreplace
bold
expert
deluxe=false
multi
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

#ifOption:multi
#include:mlutf
#include:mlcid
#endif

#ifOption:uplatex
#include:uplatex
#endif

# from deluxe option of otf
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