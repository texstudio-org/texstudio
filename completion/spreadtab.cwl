# spreadtab package
# Matthew Bertucci 2025/03/15 for v0.61

#include:xstring
#include:simplekv

\begin{spreadtab}{{envname}{preamble}}#\array
\begin{spreadtab}[options%keyvals]{{envname}{preamble}}#\array
\end{spreadtab}

\STset{keyvals}
\STreset

#keyvals:\begin{spreadtab},\STset
tabline sep=%<separator%>
text mark=%<mark%>
numeric mark=%<mark%>
freeze char=%<char%>
pretab code=%<code%>
posttab code=%<code%>
dec sep=%<separator%>
autoround=%<integer%>
save list={%<macro=abs ref,...%>}
aux save list={%<macro=abs ref,...%>}
display marks=%<marks%>
copy char=%<char%>
tag to aux#true,false
messages#true,false
debug={%<options%>}
#endkeyvals

\STxp{code}
\STrep{n}{code}

\STcopy{>x,vy}{formula}#t
\SThiderow#t
\SThidecol#t
\STtag{name}

\STprintnum{arg}#*
\STdatetonum{cmd}{jj}{mm}{aa}#*d

\STname#S
\STver#S
\STdate#S
