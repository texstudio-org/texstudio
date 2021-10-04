# background package
# Matthew Bertucci 10/3/2021 for v2.1

#include:tikz
#include:everypage
#include:afterpage

\backgroundsetup{options%keyvals}

#keyvals:\backgroundsetup
pages=#all,some
firstpage#true,false
placement=#center,top,bottom
contents=
color=#%color
angle=%<degrees%>
opacity=
scale=
position=
nodeanchor=
anchor=
hshift=##L
vshift=##L
#endkeyvals

\BgThispage
\NoBgThispage
\BgMaterial

# Previous version commands for compatibility
\SetBgContents{arg}#S
\SetBgColor{arg}#S
\SetBgAngle{arg}#S
\SetBgOpacity{arg}#S
\SetBgScale{arg}#S
\SetBgPosition{arg}#S
\SetBgAnchor{arg}#S
\SetBgHshift{arg}#S
\SetBgVshift{arg}#S