# otf package
# Matthew Bertucci 2023/02/23 for v1.7b8

#include:platex
#include:keyval
#include:ajmacros

#keyvals:\usepackage/otf#c
nomacros
noreplace
bold
expert
deluxe
multi
burasage
platex
uplatex
autodetect
jis2004
scale=%<factor%>
#endkeyvals

#ifOption:expert
\rubydefault#*
\rubyfamily
\rubykatuji
#endif

#ifOption:deluxe
\mgdefault#*
\propdefault#*
\ebdefault#*
\ltdefault#*
\mathmg{text%plain}#m
\mgfamily
\textmg{text}
\propshape
\ebseries
\ltseries
#endif

#ifOption:multi
#include:mlutf
#include:mlcid
#endif

#ifOption:uplatex
#include:uplatex
#endif

\UTF{hex number}
\CID{number}

\ajKunoji
\ajKunojiwithBou
\ajDKunoji
\ajDKunojiwithBou
\ajNinoji
\ajvarNinoji
\ajYusuriten
\ajMasu
\ajYori
\ajKoto
\ajUta
\ajCommandKey
\ajReturnKey
\ajCheckmark
\ajVisibleSpace
\ajSenteMark
\ajGoteMark
\ajClub
\ajHeart
\ajSpade
\ajDiamond
\ajvarClub
\ajvarHeart
\ajvarSpade
\ajvarDiamond
\ajPhone
\ajPostal
\ajvarPostal
\ajSun
\ajCloud
\ajUmbrella
\ajSnowman
\ajJIS
\ajJAS
\ajBall
\ajHotSpring
\ajWhiteSesame
\ajBlackSesame
\ajWhiteFlorette
\ajBlackFlorette
\ajRightBArrow
\ajLeftBArrow
\ajUpBArrow
\ajDownBArrow
\ajRightHand
\ajLeftHand
\ajUpHand
\ajDownHand
\ajRightScissors
\ajLeftScissors
\ajUpScissors
\ajDownScissors
\ajRightWArrow
\ajLeftWArrow
\ajUpWArrow
\ajDownWArrow
\ajRightDownArrow
\ajLeftDownArrow
\ajLeftUpArrow
\ajRightUpArrow
