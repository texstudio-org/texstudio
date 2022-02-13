# beamerswitch class
# Matthew Bertucci 2/12/2022 for v1.8

#include:xkeyval
#include:xkvltxp
#include:etoolbox
#include:xstring
#include:shellesc
#include:iftex
#include:xparse
#include:class-beamer

#keyvals:\documentclass/beamerswitch#c
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