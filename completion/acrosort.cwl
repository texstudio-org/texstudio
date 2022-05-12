# acrosort package
# Matthew Bertucci 2022/05/11 for v1.6.1

#include:eforms
#include:icon-appr
#include:multido
#include:graphicx

\isPackage
\asEmbedTiles{name}{n-tiles}{imagefile}#g
\asEmbedTiles[ext]{name}{n-tiles}{imagefile}#g
\insertTiles{name}{width}{n-rows}{n-cols}
\StartSort{name}{width}{height}
\StartSort[eforms parameters]{name}{width}{height}
\StopSort{name}{width}{height}
\StopSort[eforms parameters]{name}{width}{height}
\ClearSort{name}{width}{height}
\ClearSort[eforms parameters]{name}{width}{height}

\customStartJS{script%definition}
\customFinishJS{script%definition}
\appendStartSortJS{script%definition}
\appendStopSortJS{script%definition}
\appendClearSortJS{script%definition}

# not documented
\asGrphWd#*
\asIconObjs#*
\asIconPic{arg1}{arg2}{arg3}{arg4}#*
\asNumSideShowPics#*
\asTileHt#*
\asTileWd#*
\asTtlGrphHt#*
\astileKVs{arg1}#*
\iconPresets#*
\sortCustomFinishJS#*
\sortCustomStartJS#*