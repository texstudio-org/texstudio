# lua-ul package
# Matthew Bertucci 8/10/2021 for v0.1.4

#include:luatex

\underLine{text}
\highLight{text}
\strikeThrough{text}

#ifOption:soul
\ul{text}
\hl{text}
\st{text}
#endif

\LuaULSetHighLightColor{color}
\newunderlinetype{cmd}{leaderscmd}#*d
\newunderlinetype{cmd}[context]{leaderscmd}#*d
