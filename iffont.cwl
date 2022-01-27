# iffont package
# Matthew Bertucci 1/25/2022 for v1.0.0

#include:fontspec
#include:etoolbox

\settofirstfound{font cmd}{font1,font2,...}

\iffontsexist{font list}{true}{false}#*
\ifxfontsexist{font list}{true}{false}#*
\iffontexists{font}{true}{false}#*
\ifxfontexists{font}{true}{false}#*