# ocgx2 package
# Matthew Bertucci 2022/08/12 for v0.55

#include:ocgbase

#keyvals:\usepackage/ocgx2#c
dvipdfmx
viewocg=#always,never,ifvisible
printocg=#always,never,ifvisible
exportocg=#always,never,ifvisible
showingui=#true,false,always,never,iffirstuse
tikz#true,false
ocgcolorlinks#true,false
#endkeyvals

\begin{ocg}{layer name}{ocg id}{initial visibility}
\begin{ocg}[options%keyvals]{layer name}{ocg id}{initial visibility}
\end{ocg}

#keyvals:\begin{ocg}
viewocg=#always,never,ifvisible
printocg=#always,never,ifvisible
exportocg=#always,never,ifvisible
showingui=#true,false,always,never,iffirstuse
listintoolbar=#true,false,always,never,iffirstuse
radiobtngrps={%<group1,group2,...%>}
#endkeyvals

\begin{ocmd}{visibility policy,visibility expression}
\begin{ocmd}[id]{visibility policy,visibility expression}
\end{ocmd}

\AllOn{ocg1,ocg2,...}
\AnyOn{ocg1,ocg2,...}
\AnyOff{ocg1,ocg2,...}
\AllOff{ocg1,ocg2,...}
\Not{item}
\And{item1,item2,...}
\Or{item1,item2,...}

\switchocg{ocg1,ocg2,...}{link text%text}
\switchocg[trigger%keyvals]{ocg1,ocg2,...}{link text%text}
\switchocg*{ocg1,ocg2,...}{link text%text}
\switchocg*[trigger%keyvals]{ocg1,ocg2,...}{link text%text}
\showocg{ocg1,ocg2,...}{link text%text}
\showocg[trigger%keyvals]{ocg1,ocg2,...}{link text%text}
\showocg*{ocg1,ocg2,...}{link text%text}
\showocg*[trigger%keyvals]{ocg1,ocg2,...}{link text%text}
\hideocg{ocg1,ocg2,...}{link text%text}
\hideocg[trigger%keyvals]{ocg1,ocg2,...}{link text%text}
\hideocg*{ocg1,ocg2,...}{link text%text}
\hideocg*[trigger%keyvals]{ocg1,ocg2,...}{link text%text}
\actionsocg{switchocg1,...}{showocg1,...}{hideocg1,...}{link text%text}
\actionsocg[trigger%keyvals]{switchocg1,...}{showocg1,...}{hideocg1,...}{link text%text}
\actionsocg*{switchocg1,...}{showocg1,...}{hideocg1,...}{link text%text}
\actionsocg*[trigger%keyvals]{switchocg1,...}{showocg1,...}{hideocg1,...}{link text%text}

#keyvals:\switchocg,\switchocg*,\showocg,\showocg*,\hideocg,\hideocg*,\actionsocg,\actionsocg*
onmousenter
onmouseexit
onmousedown
onmouseup
onmouseall
#endkeyvals

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

# deprecated
\toggleocgs{layerid1 layerid2 ...}{link text%text}#*
\toggleocgs[option%keyvals]{layerid1 layerid2 ...}{link text%text}#*
\showocgs{layerid1 layerid2 ...}{link text%text}#*
\showocgs[option%keyvals]{layerid1 layerid2 ...}{link text%text}#*
\hideocgs{layerid1 layerid2 ...}{link text%text}#*
\hideocgs[option%keyvals]{layerid1 layerid2 ...}{link text%text}#*
\setocgs{tlayerid1 ...}{slayerid1 ...}{hlayerid1 ...}{link text%text}#*
\setocgs[option%keyvals]{tlayerid1 ...}{slayerid1 ...}{hlayerid1 ...}{link text%text}#*
