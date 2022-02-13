# snotez package
# Matthew Bertucci 2/12/2022 for v0.6

#include:etoolbox
#include:pgfopts
#include:marginnote
#include:perpage

\sidenote{text}
\sidenote[mark]{text}
\sidenote(offset){text}#*
\sidenote(offset)[mark]{text}#*

#ifOption:dblarg=true
\sidenote[offset][mark]{text}
#endif

\sidenotemark#*
\sidenotemark[mark]#*

\sidenotetext{text}
\sidenotetext[mark]{text}

\begin{sidefigure}
\end{sidefigure}
\begin{sidetable}
\end{sidetable}

\newsnotezfloat{name}#*
\newsnotezfloat[code]{name}#*

\setsidenotes{options%keyvals}

#keyvals:\setsidenotes
dblarg#true,false
marginnote#true,false
text-format=%<code%>
text-format+=%<code%>
perpage#true,false
perchapter#true,false
note-mark-sep=%<code%>
note-mark-format=%<code%>
text-mark-format=%<code%>
footnote#true,false
sidefloat-format=%<code%>
sidefloat-format+=%<code%>
#endkeyvals
