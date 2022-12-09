# ocgx tikzlibrary
# 2022/12/06 for v0.5

#include:ocgx
#include:tikzlibrarycalc

#keyvals:\tikzset#c,\begin{tikzpicture}#c,\begin{scope}#c,\node#c
ocg={%<options%>}
switch ocg={%<ocg list%>}
show ocg={%<ocg list%>}
hide ocg={%<ocg list%>}
actions ocg={%<ocg list1%>}{%<ocg list2%>}{%<ocg list3%>}
switch ocg with mark on={%<ocg ref%>}{%<ocg list%>}
switch ocg with mark off={%<ocg ref%>}{%<ocg list%>}
#endkeyvals