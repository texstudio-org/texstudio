# moloch beamertheme
# Matthew Bertucci 2025/04/03 for v1.0.1

#include:etoolbox
#include:pgfopts
#include:calc
#include:tikz

#keyvals:\usetheme/moloch#c,\molochset
titleformat=#regular,smallcaps,allsmallcaps,allcaps
titleformat plain=#regular,smallcaps,allsmallcaps,allcaps
sectionpage=#none,simple,progressbar
subsectionpage=#none,simple,progressbar
standoutnumbering=#none,hide,show
progressbar=#none,head,frametitle,foot
progressbar linewidth=##L
block=#transparent,fill
background=#dark,light
titleformat title=#regular,smallcaps,allsmallcaps,allcaps
titleformat subtitle=#regular,smallcaps,allsmallcaps,allcaps
titleformat section=#regular,smallcaps,allsmallcaps,allcaps
titleformat frame=#regular,smallcaps,allsmallcaps,allcaps
titleseparator linewidth=##L
#endkeyvals

\molochset{options%keyvals}
\mreducelistspacing#S

mDarkBrown#B
mDarkTeal#B
mLightBrown#B
mLightGreen#B
