# autoaffil package
# Matthew Bertucci 2026/06/09 for v1.0

#include:etoolbox

#keyvals:\usepackage/autoaffil#c
ranges
superaftercomma
nobreak
manual
#endkeyvals

\aafauthorfont{name}#*
\aafauthorsep#*
\aafauthorspace#*
\autoaffil{text}
\autoauthor[symbols]{name}
\autoauthor{name}
\autoremark{symbol}{text}
\printaffils
\printauthors
\printremarks