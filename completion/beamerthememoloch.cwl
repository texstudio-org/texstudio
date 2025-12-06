# moloch beamertheme
# Matthew Bertucci 2025/12/05 for v2.0.0

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
titleformat title=#regular,smallcaps,allsmallcaps,allcaps
titleformat subtitle=#regular,smallcaps,allsmallcaps,allcaps
titleformat section=#regular,smallcaps,allsmallcaps,allcaps
titleformat frame=#regular,smallcaps,allsmallcaps,allcaps
titleseparator linewidth=##L
colortheme=#default,highcontrast,tomorrow,paper,catppuccin
#endkeyvals

\molochset{options%keyvals}
\mreducelistspacing#S

mNormaltextFg#B
mNormaltextBg#B
mAlertFg#B
mFrametitleFg#B
mFrametitleBg#B
mProgressbarFg#B
mProgressbarBg#B
mTitleseparatorFg#B
mStandoutFg#B
mStandoutBg#B
mFootnoteFg#B

mDarkBrown#B
mDarkTeal#B
mLightBrown#B
mLightGreen#B

\molochcolors{keyvals}
#keyvals:\molochcolors
variant=#dark,light
theme=#default,highcontrast,tomorrow,paper,catppuccin
alerted text=#%color
example text=#%color
normal text fg=#%color
normal text bg=#%color
frametitle fg=#%color
frametitle bg=#%color
progressbar fg=#%color
progressbar bg=#%color
standout fg=#%color
standout bg=#%color
light/alerted text=#%color
light/example text=#%color
light/normal text fg=#%color
light/normal text bg=#%color
light/frametitle fg=#%color
light/frametitle bg=#%color
light/progressbar fg=#%color
light/progressbar bg=#%color
light/standout fg=#%color
light/standout bg=#%color
dark/alerted text=#%color
dark/example text=#%color
dark/normal text fg=#%color
dark/normal text bg=#%color
dark/frametitle fg=#%color
dark/frametitle bg=#%color
dark/progressbar fg=#%color
dark/progressbar bg=#%color
dark/standout fg=#%color
dark/standout bg=#%color
#endkeyvals

\mitemover#*
\mitem#*
\overhangSquare#*
\overhangCircle#*
\overhangTriangle#*