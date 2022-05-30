# endnotesj package
# Matthew Bertucci 2022/05/02 for v3.0

#include:luatexja-otf

#keyvals:\usepackage/endnotesj#c
tate
yoko
auto-tateyoko
twin
single
utf
otf
ver3
ver2
%<notesname%>
#endkeyvals

#ifOption:otf
#include:otf
#endif

#ifOption:utf
#include:utf
#endif

\endnote{text}
\endnote[number]{text}
\endnotemark
\endnotemark[number]
\endnotetext{text}
\endnotetext[number]{text}
\addtoendnotes{text}
\enotesize
\theendnotes
\theendnote#*
\theenmark#*
\makeenmark#*
\enoteformat#*
\enoteheading#*
\notesname#*
\endnotesep#*
\kcharparline{number}
\linesparpage{number}