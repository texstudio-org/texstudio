# package changes
# fkastner 2021/03/17 for changes v4.0.1
# URL: https://ctan.org/tex-archive/macros/latex/contrib/changes

#include:todonotes
#include:truncate
#include:ulem
#include:xcolor
#include:xifthen
#include:xkeyval
#include:xstring

\definechangesauthor[keyvals]{authorid}#s#%authorid
\definechangesauthor{authorid}#s#%authorid
#keyvals:\definechangesauthor
name=
color=#%color
#endkeyvals

\added[keyvals]{text}
\added{text}
\deleted[keyvals]{text}
\deleted{text}
\replaced[keyvals]{new%text}{old%text}
\replaced{new%text}{old%text}
\highlight[keyvals]{text}
\highlight{text}
#keyvals:\added,\deleted,\replaced,\highlight
id=#%authorid
comment=
#endkeyvals

\comment[keyvals]{text%todo}#D
\comment{text%todo}#D
#keyvals:\comment
id=#%authorid
#endkeyvals

\listofchanges
\listofchanges[keyvals]
#keyvals:\listofchanges
style=#list,summary,compactsummary
title=
show=#all,added,deleted,replaced,highlight,comment
#endkeyvals

\setaddedmarkup{arg1}
\setdeletedmarkup{arg1}
\sethighlightmarkup{arg1}
\setcommentmarkup{arg1}
\setauthormarkup{arg1}
\setauthormarkupposition{left/right}
\setauthormarkuptext{id/name}
\settruncatewidth{width}
\setsummarywidth{width}
\setsummarytowidth{text}
\setsocextension{ext}
\setlocextension{ext}
