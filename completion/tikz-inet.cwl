# tikz-inet package
# Matthew Bertucci 10/8/2021 for v0.1

#include:tikz
#include:ifthen

\inetcell{symbol}#/tikzpicture
\inetcell[options](node name){symbol}[angle]#/tikzpicture

\inetwire(cell1.port1)(cell2.port2)#/tikzpicture
\inetwire[options](cell1.port1)(cell2.port2)#/tikzpicture
\inetloop#/tikzpicture
\inetloop[options]#/tikzpicture
\inetwirecoords(node1)(node2)#/tikzpicture
\inetwirecoords[options](node1)(node2)#/tikzpicture
\inetwirefree(cell.port)#/tikzpicture
\inetwirefree[options](cell.port)#/tikzpicture

\inetbox{%<(cell1) (cell2) ...%>}{%<node name%>}#/tikzpicture
\inetbox[%<options%>]{%<(cell1) (cell2) ...%>}{%<node name%>}#/tikzpicture
\inetprombox{%<(cell1) (cell2) ...%>}{%<node name%>}#/tikzpicture
\inetprombox[%<options%>]{%<(cell1) (cell2) ...%>}{%<node name%>}#/tikzpicture

\inetnofancy#/tikzpicture
\inetfancy#/tikzpicture
\inetcellstyle#*
\inetwirestyle#*
\inetboxstyle#*
\inetcolor#*
\inetsetfancycellstyle{specs}#*
\inetsetfancywirestyle{specs}#*
\inetoptions#*