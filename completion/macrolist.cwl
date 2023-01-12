# macrolist package
# Matthew Bertucci 4/17/2022 for v2.1.0

#include:pgffor

\macronewlist{listname%specialDef}#s#%macrolist
\macrolistexists{listname%keyvals}{true}{false}
\macrolistelement{listname%keyvals}{position}
\macrolistindexof{listname%keyvals}{element}
\macrolistcontains{listname%keyvals}{element}{true}{false}
\macrolistadd{listname%keyvals}{element}
\macrolistadd{listname%keyvals}[position]{element}
\macrolisteadd{listname%keyvals}{element}
\macrolisteadd{listname%keyvals}[position]{element}
\macrolistremove{listname%keyvals}{position}
\macrolistremovelast{listname%keyvals}
\macrolistclear{listname%keyvals}
\macrolistsize{listname%keyvals}
\macrolistforeach{listname%keyvals}{cmd}{action}#d
\macrolistforeach{listname%keyvals}{cmd}[begin][end]{action}#d
\macrolistjoin{listname%keyvals}{joiner}

#keyvals:\macrolistexists#c,\macrolistelement#c,\macrolistindexof#c,\macrolistcontains#c,\macrolistadd#c,\macrolisteadd#c,\macrolistremove#c,\macrolistremovelast#c,\macrolistclear#c,\macrolistsize#c,\macrolistforeach#c,\macrolistjoin#c
%macrolist
#endkeyvals
