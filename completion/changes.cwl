# package changes
# fkastner 2021/03/17 for changes v4.0.1
# updated 2021/12/16 for v4.2.1
# URL: https://ctan.org/tex-archive/macros/latex/contrib/changes

#include:todonotes
#include:truncate
#include:ulem
#include:xcolor
#include:xkeyval
#include:xstring
#include:etoolbox

#keyvals:\usepackage/changes#c
draft
final
commandnameprefix=#none,ifneeded,always
markup=#default,underlined,bfit,nocolor
addedmarkup=#colored,uline,uuline,uwave,dashuline,dotuline,bf,it,sl,em
deletedmarkup=#sout,xout,colored,uline,uuline,uwave,dashuline,dotuline,bf,it,sl,em
highlightmarkup=#background,uuline,uwave
commentmarkup=#todo,margin,footnote,uwave
authormarkup=#superscript,subscript,brackets,footnote,none
authormarkupposition=#right,left
authormarkuptext=#id,name
defaultcolor=#%color
todonotes={%<todonotes options%>}
truncate={%<truncate options%>}
ulem={%<ulem options%>}
xcolor={%<xcolor options%>}
#endkeyvals

\definechangesauthor[keyvals]{authorid}#s#%authorid
\definechangesauthor{authorid}#s#%authorid
#keyvals:\definechangesauthor
name=%<name%>
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
comment=%<comment%>
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
title=%<title%>
show=#all,added,deleted,replaced,highlight,comment
#endkeyvals

\setaddedmarkup{definition}
\setdeletedmarkup{definition}
\sethighlightmarkup{definition}
\setcommentmarkup{definition}
\setauthormarkup{definition}
\setauthormarkupposition{left/right}
\setauthormarkuptext{id/name}
\setanonymousname{name}
\settruncatewidth{width}
\setsummarywidth{width}
\setsummarytowidth{text}
\setsocextension{ext}
\setlocextension{ext}
