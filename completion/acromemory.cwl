# acromemory package
# Matthew Bertucci 2022/05/11 for v2.0

#include:xkeyval
#include:eforms
#include:aeb-comment
#include:icon-appr
#include:multido
#include:graphicx

#keyvals:\usepackage/acromemory#c
acromemory1
acromemory2
includehelp
draft
#endkeyvals

\isPackage
\amEmbedTiles{name}{n-tiles}{imagefile}#g
\insertTiles{name}{width}{n-rows}{n-cols}
\messageBox{width}{height}
\messageBox[eforms parameters]{width}{height}
\playItAgain{width}{height}
\playItAgain[eforms parameters]{width}{height}

\insertTilesL{name}{width}{n-rows}{n-cols}
\insertTilesR{name}{width}{n-rows}{n-cols}
\tryItAgain{width}{height}
\tryItAgain[eforms parameters]{width}{height}
\helpImage{width}{height}
\helpImage[eforms parameters]{width}{height}
\rolloverHelpButton{width}{height}
\rolloverHelpButton[eforms parameters]{width}{height}

\initFirstiMsg#*
\initFirstiiMsg#*

# not documented
\acromemoryifalse#*
\acromemoryitrue#*
\amIconObjs#*
\amIconPic{arg1}{arg2}{arg3}{arg4}#*
\amImageHt#*
\amImageWd#*
\AMIndxList#*
\amNumImages#*
\amTileHt#*
\amtileKVs{arg1}#*
\amTileWd#*
\bDebug#*
\iconPresets#*
\ifacromemoryi#*
\ifincludehelp#*
\imageImportPath#*
\includehelpfalse#*
\includehelptrue#*
\insertTilesii{arg1}{arg2}{arg3}{arg4}{arg5}#*
\memDebug#*
\muAction#*
\nTotalTiles#*
\RanIdentifier#*
\theHelpCaption{arg1}#*