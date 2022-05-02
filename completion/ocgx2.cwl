# ocgx2 package
# Matthew Bertucci 2022/04/29 for v0.54

#include:l3keys2e
#include:ocgbase

#keyvals:\usepackage/ocgx2#c
dvipdfmx
viewocg=#always,never,ifvisible
printocg=#always,never,ifvisible
exportocg=#always,never,ifvisible
showingui=#true,false,always,never,iffirstuse
listintoolbar=#true,false,always,never,iffirstuse
tikz#true,false
ocgcolorlinks#true,false
#endkeyvals

\begin{ocg}{layer name}{layer id}{initial visibility}
\begin{ocg}[options%keyvals]{layer name}{layer id}{initial visibility}
\end{ocg}

#keyvals:\begin{ocg}
viewocg=#always,never,ifvisible
printocg=#always,never,ifvisible
exportocg=#always,never,ifvisible
showingui=#true,false,always,never,iffirstuse
listintoolbar=#true,false,always,never,iffirstuse
radiobtngrp=
radiobtngrps=
#endkeyvals

\begin{ocmd}{visibility}
\begin{ocmd}[id]{visibility}
\end{ocmd}

\toggleocgs{layerid1 layerid2 ...}{display}
\toggleocgs[option%keyvals]{layerid1 layerid2 ...}{display}
\showocgs{layerid1 layerid2 ...}{display}
\showocgs[option%keyvals]{layerid1 layerid2 ...}{display}
\hideocgs{layerid1 layerid2 ...}{display}
\hideocgs[option%keyvals]{layerid1 layerid2 ...}{display}
\setocgs{tlayerid1 ...}{slayerid1 ...}{hlayerid1 ...}{display}
\setocgs[option%keyvals]{tlayerid1 ...}{slayerid1 ...}{hlayerid1 ...}{display}

#keyvals:\toggleocgs,\showocgs,\hideocgs,\setocgs
triggerocg=#onareaenter,onareaexit,onmousedown,onmouseup,allactions
#endkeyvals

\switchocg{ocg1 ocg2 ...}{display}
\switchocg[trigger]{ocg1 ocg2 ...}{display}
\switchocg*{ocg1 ocg2 ...}{display}
\switchocg*[trigger]{ocg1 ocg2 ...}{display}
\showocg{ocg1 ocg2 ...}{display}
\showocg[trigger]{ocg1 ocg2 ...}{display}
\showocg*{ocg1 ocg2 ...}{display}
\showocg*[trigger]{ocg1 ocg2 ...}{display}
\hideocg{ocg1 ocg2 ...}{display}
\hideocg[trigger]{ocg1 ocg2 ...}{display}
\hideocg*{ocg1 ocg2 ...}{display}
\hideocg*[trigger]{ocg1 ocg2 ...}{display}
\actionsocg{switchocg1 ...}{showocg1 ...}{hideocg1 ...}{display}
\actionsocg[trigger]{switchocg1 ...}{showocg1 ...}{hideocg1 ...}{display}
\actionsocg*{switchocg1 ...}{showocg1 ...}{hideocg1 ...}{display}
\actionsocg*[trigger]{switchocg1 ...}{showocg1 ...}{hideocg1 ...}{display}

\ocglinkprotect{text%plain}

#ifOption:tikz
#include:tikz
# loads calc tikzlibrary
#keyvals:\tikzset#c,\begin{tikzpicture}#c,\begin{scope}#c,\node#c
ocg={%<options%>}
ocmd={%<options%>}
trigger ocg=#onmousenter,onmouseexit,onmousedown,onmouseup,onmouseall
switch ocg={%<ocg list%>}
show ocg={%<ocg list%>}
hide ocg={%<ocg list%>}
actions ocg={%<ocg list1%>}{%<ocg list2%>}{%<ocg list3%>}
switch ocg with mark on={%<ocg ref%>}{%<ocg list%>}
switch ocg with mark off={%<ocg ref%>}{%<ocg list%>}
#endkeyvals
#endif
#ifOption:tikz=true
#include:tikz
# loads calc tikzlibrary
#keyvals:\tikzset#c,\begin{tikzpicture}#c,\begin{scope}#c,\node#c
ocg={%<options%>}
ocmd={%<options%>}
trigger ocg=#onmousenter,onmouseexit,onmousedown,onmouseup,onmouseall
switch ocg={%<ocg list%>}
show ocg={%<ocg list%>}
hide ocg={%<ocg list%>}
actions ocg={%<ocg list1%>}{%<ocg list2%>}{%<ocg list3%>}
switch ocg with mark on={%<ocg ref%>}{%<ocg list%>}
switch ocg with mark off={%<ocg ref%>}{%<ocg list%>}
#endkeyvals
#endif