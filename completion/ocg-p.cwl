# ocg-p package
# Matthew Bertucci 2022/04/29 for v0.4

#include:eso-pic
#include:ifpdf
#include:ifxetex
#include:xkeyval

#keyvals:\usepackage/ocg-p#c
ocgtabular
#endkeyvals

#ifOption:ocgtabular
#include:datatool
#include:tikz
#include:listings
\begin{ocgtabular}{cols}{database}{options}#\tabular
\begin{ocgtabular}[pos]{cols}{database}{options}#\tabular
\end{ocgtabular}
\setocgtabularheader{column name}{header%text}
#endif

\begin{ocg}{layer name}{layer id}{initial visibility}
\begin{ocg}[options%keyvals]{layer name}{layer id}{initial visibility}
\end{ocg}

#keyvals:\begin{ocg}
printocg=#always,never,ifvisible
exportocg=#always,never,ifvisible
listintoolbar=#always,never,iffirstuse
#endkeyvals

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

\ocgpversion#S