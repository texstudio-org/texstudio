# thumb package
# Matthew Bertucci 1/28/2022 for v1.0

#include:fancyhdr

#keyvals:\usepackage/thumb#c
minitoc
box
filledbox
oval
filledoval
#endkeyvals

#ifOption:minitoc
#include:minitoc
\thumbmini#S
#endif

\Overviewpage
\thumbwidth
\thumbheight
\thumbskip
\overviewskip

\thumbchap#*
\thumbHskip#*
\thethumbheight#*
\thethumbwidth#*
\thelthumbskip#*
\therthumbskip#*
\theoverviewskip#*
\Prefacename#*
\ifPreface#*
\Prefacetrue#*
\Prefacefalse#*
\preface#*
\preface[text]#*
\thumbfilledbox#*
\rthumb#*
\lthumb#*
\ovrthumb#*
\thumbbox#*
\ovrthumb#*
\thumbfilledoval#*
\thumboval#*
\thumbheaderfont#*
\Overviewtitlefont#*
\Overviewauthorfont#*
\Overviewdatefont#*
\thumbtitlefont#*
\thumbauthorfont#*
\thumbdatefont#*
\thumbtitle#*
\thumbauthor#*
\thumbdate#*
\Overviewtitle#*
\ifAppendix#*
\Appendixtrue#*
\Appendixfalse#*
\theappendix#*
\thumbspace#*
\thumbsecnum#*
\Overviewname#*
\Overviewfont#*
\secname{arg1}{arg2}{arg3}#*
\thumboverview#*
\thethumbhskip#*
\theOverviewnumber#*
\theline#*
\thethumbline#*
\ifOverview#*
\Overviewtrue#*
\Overviewfalse#*
\OverviewPage#*
\thethumbovrwidth#*

\thumbtmp#S
\ovrout#S
\HOLD#S
\tmptitlefont#S
\tmpauthorfont#S
\tmpdatefont#S
\tmpand#S
\thumbovr#S
\tempa#S
\thethumbtmp#S
\filedate#S
\fileversion#S