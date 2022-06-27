# acm-book class
# Matthew Bertucci 2022/06/26 for v2.1

#include:url
#include:class-book
#include:times
#include:mathptm
#include:natbib

#keyvals:\documentclass/acm-book#c
9pt
10pt
11pt
authoryear
cm
computermodern
mathtime
natbib
nonatbib
numberedpars
numbers
preprint
times
#endkeyvals

#ifOption:mathtime
#include:mathtime
#endif

\begin{sidebar}{title}
\end{sidebar}

\balancecolumns#*
\centeroncapheight{content}#*
\chapterauthor{names}
\euro
\mono{text%plain}
\monster
\nocaptionrule
\nut#*
\setpagenumber{number}#*
\setvspace{skip register}{length}#*
\softraggedright#*
\standardtextwidth#*
\standardvspace#*
\stringeql{flag}{string1}{string2}#*
\thesidebarnumber#*
\trimheight#*
\trimwidth#*