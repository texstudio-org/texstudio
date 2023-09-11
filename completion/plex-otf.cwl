# plex-otf package
# Matthew Bertucci 2023/09/09 for v0.08

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:fontspec

#keyvals:\usepackage/plex-otf#c
usefilenames#true,false
mono#true,false
sans#true,false
serif#true,false
RMstyle={%<style list%>}
SSstyle={%<style list%>}
SSconstyle={%<style list%>}
TTstyle={%<style list%>}
Style={%<style list%>}
RMSCfont=%<font name%>
SSSCfont=%<font name%>
RM={%<fontspec options%>}
SS={%<fontspec options%>}
SScon={%<fontspec options%>}
TT={%<fontspec options%>}
DefaultFeatures={%<fontspec options%>}
#endkeyvals

\slshapeRM
\PlexExtraLightRM
\PlexExtraLightRM
\PlexLightRM
\PlexThinRM
\PlexMediumRM
\PlexTextRM
\PlexSemiBoldRM
\slshapeSS
\PlexExtraLightSS
\PlexLightSS
\PlexThinSS
\PlexMediumSS
\PlexTextSS
\PlexSemiBoldSS
\sffamilyCon
\slshapeSScon
\PlexExtraLightSScon
\PlexLightSScon
\PlexThinSScon
\PlexMediumSScon
\PlexTextSScon
\PlexSemiBoldSScon
\slshapeTT
\PlexExtraLightTT
\PlexLightTT
\PlexThinTT
\PlexMediumTT
\PlexTextTT
\PlexSemiBoldTT

\CE
\FCC
\upleftarrow
\uprightarrow
\downleftarrow
\downrightarrow
\leftturn
\rightturn
\fullleftturn
\fullrightturn
