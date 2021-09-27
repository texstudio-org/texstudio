# snotez package
# Matthew Bertucci 9/26/2021 for v0.5a

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
note-mark-sep=%<code%>
note-mark-format=%<code%>
text-mark-format=%<code%>
footnote#true,false
sidefloat-format=%<code%>
sidefloat-format+=%<code%>
#endkeyvals