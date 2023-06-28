# beamerswitch class
# Matthew Bertucci 2022/08/24 for v1.9

#include:xkeyval
#include:xkvltxp
#include:etoolbox
#include:xstring
#include:shellesc
#include:iftex
#include:class-beamer

#keyvals:\documentclass/beamerswitch#c
articleclass=%<class%>
articleoptions={%<article class options%>}
beameroptions={%<beamer class options%>}
article
beamer
handout
trans
alsoarticle
alsobeamer
alsohandout
alsotrans
also={%<modes%>}
nohyperref
#endkeyvals

## cannot list all classes...
#ifOption:articleclass=book
#include:class-book
#endif
#ifOption:articleclass=report
#include:class-report
#endif
#ifOption:articleclass=memoir
#include:class-memoir
#endif

#ifOption:article
#include:beamerarticle
#endif

#ifOption:handout
#include:pgfpages
#endif

\ArticleSuffix
\BeamerSuffix
\HandoutSuffix
\TransSuffix

\BeamerswitchSpawn{suffix}
\SpawnedCompiler
\SpawnedPDFTeX
\SpawnedLuaTeX
\SpawnedXeTeX
\SpawnedTeX

\handoutlayout{options%keyvals}

#keyvals:\handoutlayout
paper=%<paper size%>
nup=#1,1plus,2,3,3plus,4,4plus,6,8
pnos
border=##L
margin=##L
align
#endkeyvals

\articlelayout{options%keyvals}

#keyvals:\articlelayout
frametitles=#para,margin,none
maketitle
instbreak=%<definition%>
#endkeyvals

\JobName#*
\handoutpnobaseline#*
\pgfpageoptionborder#*
\pgfpageoptionfirstshipout#*
\pgfpageoptionheight#*
\pgfpageoptionwidth#*
\thehandoutpno#*
