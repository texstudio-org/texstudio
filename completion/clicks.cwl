# clicks package
# Matthew Bertucci 2024/12/22 for v0.4.2

#include:pgfopts
#include:etoolbox

#keyvals:\usepackage/clicks#c
static
#endkeyvals

\theminutes#*
\print{text}
\flush[minutes]
\click[minutes]
\plush{text}
\plush[minutes]{text}
\plick{text}
\plick[minutes]{text}
