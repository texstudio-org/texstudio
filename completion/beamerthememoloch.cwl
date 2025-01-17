# moloch beamertheme
# Matthew Bertucci 2025/01/17 for v0.6.0

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
numbering=#none,counter,fraction
progressbar=#none,head,frametitle,foot
block=#transparent,fill
background=#dark,light
titleformat title=#regular,smallcaps,allsmallcaps,allcaps
titleformat subtitle=#regular,smallcaps,allsmallcaps,allcaps
titleformat section=#regular,smallcaps,allsmallcaps,allcaps
titleformat frame=#regular,smallcaps,allsmallcaps,allcaps
#endkeyvals

\molochset{options%keyvals}
\mreducelistspacing#S

mDarkBrown#B
mDarkTeal#B
mLightBrown#B
mLightGreen#B
