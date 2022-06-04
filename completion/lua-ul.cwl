# lua-ul package
# Matthew Bertucci 2022/06/03 for v0.2.0

#include:luatex

#keyvals:\usepackage/lua-ul#c
minimal
soul
#endkeyvals

\underLine{text}
\underLine[options%keyvals]{text}

#keyvals:\underLine,\ul,\textul
textcolor#true,false
color=#%color
top=##L
bottom=##L
height=##L
#endkeyvals

\highLight{text}
\highLight[color]{text}
\strikeThrough{text}
\strikeThrough[color]{text}

#ifOption:soul
\ul{text}
\ul[options%keyvals]{text}
\textul{text}#*
\textul[options%keyvals]{text}#*
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
\newunderlinetype{cmd}{leaderscmd%definition}#d
\newunderlinetype{cmd}[context specifier]{leaderscmd%definition}#d
