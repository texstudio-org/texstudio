# colophon package
# Matthew Bertucci 10/5/2021 for v1.1

#include:xkeyval

#keyvals:\usepackage/colophon#c
title={%<text%>}
titlestyle=%<font csname%>
titlesize=##L
aftertitle=##L
titlealign=#l,c,r
parstyle=%<font csname%>
parsize=##L
parlead=##L
nofullpage
noclrdblpg
clrpg
topspace=##L
botspace=##L
nofirstindent
#endkeyvals

\begin{colophon}
\end{colophon}
\colophon#*
\endcolophon#*
\colophontitle{title}
\colophontitlestyle{style cmds}
\colophontitlesize{size%l}
\colophonmidspace{length%l}
\colophonpagestyle{style}
\colophontitlealign{alignment%keyvals}
#keyvals:\colophontitlealign
c
l
r
#endkeyvals
\colophonpretitlehook#*
\colophonposttitlehook#*
\colophonparstyle#*
\colophonparsize#*
\colophonparlead#*
\colophonnofirstindent#*
\colophonpreparhook#*
\colophonpostparhook#*
\colophonparalign#*
\colophonnofullpage#*
\colophonnoclrdblpg#*
\colophonclrpg#*
\colophontopspace#*
\colophonbotspace#*
