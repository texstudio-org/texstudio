# macrolist package
# Matthew Bertucci 9/21/2021 for v2.1.0

#include:pgffor

\macronewlist{listname}
\macrolistexists{listname}{true}{false}
\macrolistelement{listname}{position}
\macrolistindexof{listname}{element}
\macrolistcontains{listname}{element}{true}{false}
\macrolistadd{listname}{element}
\macrolistadd{listname}[position]{element}
\macrolisteadd{listname}{element}
\macrolisteadd{listname}[position]{element}
\macrolistremove{listname}{position}
\macrolistremovelast{listname}
\macrolistclear{listname}
\macrolistsize{listname}
\macrolistforeach{listname}{cmd}{action}#d
\macrolistforeach{listname}{cmd}[begin][end]{action}#d
\macrolistjoin{listname}{joiner}
