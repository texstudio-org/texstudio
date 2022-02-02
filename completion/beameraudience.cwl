# beameraudience package
# Matthew Bertucci 2/1/2022 for v0.1

#include:kvoptions 
#include:cprotect 
#include:ifthen

#keyvals:\usepackage/beameraudience#c
audience=%<keyword%>
#endkeyvals

\ifinclude{content%text}#*
\ifshow{content%text}#*
\framefor{audience}{content%text}
\justfor{audience}{content%text}
\showcontentfor{audience}{content%text}

\fileversion#S
\filedate#S