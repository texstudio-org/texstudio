# beamerappendixnote package
# Matthew Bertucci 2/10/2022 for v1.2.0

#include:expl3
#include:l3keys2e
#include:xparse

#keyvals:\usepackage/beamerappendixnote#c
backposition=#top,bottom,title
#endkeyvals

\appxnote{title}{content%text}
\appxnote[frame options]{title}{content%text}
\printappxnotes

\options#S