# lua-ul package
# Matthew Bertucci 8/10/2021 for v0.1.4

#include:luatex

#keyvals:\usepackage/lua-ul#c
minimal
soul
#endkeyvals

\underLine{text}
\highLight{text}
\highLight[color]{text}
\strikeThrough{text}
\strikeThrough[color]{text}

#ifOption:soul
\ul{text}
\textul{text}#*
\hl{text}
\hl[color]{text}
\texthl{text}#*
\texthl[color]{text}#*
\st{text}
\st[color]{text}
\textst{text}#*
\textst[color]{text}#*
#endif

\LuaULSetHighLightColor{color}
\newunderlinetype{cmd}{leaderscmd}#*d
\newunderlinetype{cmd}[context]{leaderscmd}#*d
