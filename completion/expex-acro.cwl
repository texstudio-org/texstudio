# expex-acro package
# Matthew Bertucci 2022/05/18 for v0.0.2

#include:expex
#include:etoolbox
#include:xspace
#include:l3keys2e
#include:acro
#include:enumitem
# loads inline option of enumitem

#keyvals:\usepackage/expex-acro#c
abbrevs=#leipzig,all
refmode=#expex,latex
#endkeyvals

\exref{tag}
\exref[tag1]{tag2}
\exrefnil{tag}
\exrefnil[tag1]{tag2}
\mexref{tag1,tag2,...}
\mexref[separator]{tag1,tag2,...}
\gl{id}
\newGlossingAbbrev{id}{long form}
\glossingAbbrevsList
\obj{text}
\qu{text}
\rc{text}
\ort{text}
\pnt{text}
\pnm{text}
\dbqu{text}
\ungr{text}
\bad{text}
\lxm{text}
