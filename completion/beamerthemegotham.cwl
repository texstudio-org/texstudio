# gotham beamertheme
# Matthew Bertucci 2026/01/05 for v1.2.4.a

\gothamset{options%keyvals}

\gothamreset{arg}#S
\mreducelistspacing#S

# from color theme
#include:xcolor
gLightOrange#B
gLightGreen#B
gDeepBlue#B
gDeepYellOr#B
gAnthracite#B
gLightTeal#B
gPaleYell#B
gDarkBlack#B
gDarkGrey#B
gMidGrey#B
gLightGrey#B
colorPale#B
colorDark#B
colorA#B
colorAreversed#B
colorB#B
colorC#B
colorD#B
colorE#B
colorBG#B
colorFG#B
colorFrametitle#B
colorStandout#B
colorStandin#B
colorTitlepage#B
colorFiligrane#B
colorBackElement#B
colorProgBar#B
colorAlert#B
colorExample#B
colorFrametitle#B
colorTitlepage#B

\gothamHookPostColorBGSet#*

# from font theme
#include:ifxetex
#include:ifluatex
\iffontsavailable{list of fonts}{true code}{false code}#S

# from inner theme
#include:calc
#include:tikz
\gothamtitlepagelogo
\gothamtitlepagebg
\partContentName#*
\secContentName#*
\subsecContentName#*
\subsubsecContentName#*
\sectionhoffset#*
\gothamProgressSectionHeight#*
\partpageOptions#*
\sectionpageOptions#*
\subsectionpageOptions#*
\subsubsectionpageOptions#*
\partpageTocOptions#*
\sectionpageTocOptions#*
\subsectionpageTocOptions#*
\partTocOptions#*
\sectionTocOptions#*
\subsectionTocOptions#*
\gothamDividedPicTop#*
\gothamDividedPicBottomIncr#*
\gothamDividedPicTextWidth#*

# from outer theme
\gothamInstituteLogoCircle#*
\gothamInstituteLogoSquare#*
\gothamFrameSubtitleSep#*
\gothamRightFiligrane#*
\gothamLeftFiligrane#*
\gothamHookFooter#*
\gothamFrametitleToppading#*
\gothamFrametitleBottompading#*
\gothamFrametitleLeftpading#*
\gothamFrametitleRightpading#*
\gothamFramesubtitleStrutend#*
\sidebarRightHOffset#*
\sidebarLeftHOffset#*
\gothamFootlineRuleLeftPadding#*
\gothamFootlineRuleHeight#*
\gothamFootlineRuleLength#*
\gothamFootlineHRightOffset#*
\gothamFootlineVOffset#*
\gothamFootlineHeight#*
\gothamFootlineDepth#*
\gothamLeftFooterPadding#*
\gothamRightFooterPadding#*
\gothamFooterHOffset#*
\gothamHposLeftRotFooter#*
\gothamHposRightRotFooter#*
\gothamVposLeftRotFooter#*
\gothamVposRightRotFooter#*
\gothamProgressCircHeight#*
\gothamCounterCircleRadius#*
\gothamProgressCircBorderWidth#*
\gothamProgressHeadFootLineheight#*
\gothamCircleNumberingVshift#*
\gothamCircleNumberingHshift#*
