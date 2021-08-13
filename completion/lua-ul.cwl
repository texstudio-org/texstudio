# lua-ul package
# Matthew Bertucci 8/10/2021

\underLine{text}
\highLight{text}
\strikeThrough{text}

#ifOption:soul
\ul{text}
\hl{text}
\st{text}
#endif

\LuaULSetHighLightColor{color}
\newunderlinetype{cmd}[context]{leaderscmd}#*d
