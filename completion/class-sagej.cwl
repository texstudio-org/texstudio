# sagej class
# Matthew Bertucci 2022/08/02 for v1.20

#include:graphicx
#include:latexsym
#include:ifthen
#include:rotating
#include:calc
#include:textcase
#include:booktabs
#include:color
#include:endnotes
#include:amsfonts
#include:amssymb
#include:amsbsy
#include:amsmath
#include:amsthm
#include:tracefnt
#include:caption

#keyvals:\documentclass/sagej#c
times
doublespace
sageh
sagev
sageapa
shortAfour
Afour
MCfour
PCfour
Royal
Crown
Review
#endkeyvals

#ifOption:times
#include:times
#include:helvet
#endif

#ifOption:doublespace
#include:setspace
#endif

#ifOption:sageh
#include:natbib
#endif

#ifOption:sagev
#include:natbib
#endif

#ifOption:sageapa
#include:mslapa
#endif

#ifOption:shortAfour
#include:geometry
#include:ftnright
#endif

#ifOption:Afour
#include:geometry
#include:ftnright
#endif

#ifOption:MCfour
#include:geometry
#include:ftnright
#endif

#ifOption:PCfour
#include:geometry
#include:ftnright
#endif

#ifOption:Royal
#include:geometry
#endif

#ifOption:Crown
#include:geometry
#endif

#ifOption:Review
#include:geometry
#endif

\begin{acks}
\end{acks}
\begin{biog}
\end{biog}
\begin{biogs}
\end{biogs}
\begin{dci}
\end{dci}
\begin{funding}
\end{funding}
\begin{proof}[heading%text]
\begin{sm}
\end{sm}

\absbox#S
\affiliation{affiliation%text}
\affilnum{number}
\corrauth{name and address%text}
\email{email%URL}#U
\endpage#*
\issuenumber#*
\journalclass#*
\journalclassshort#*
\journalname#*
\keywords{word1,word2,...%text}
\refsize#*
\runninghead{text}
\sagesf#S
\startpage#*
\titlesize#*
\update#S
\volumenumber#*
\volumeyear#*