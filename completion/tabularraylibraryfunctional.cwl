# functional tabularray library
# 2022/12/15 for v2022D

#include:functional

#keyvals:\begin{tblr}#c,\SetTblrOuter#c
evaluate=%<function%>
#endkeyvals

#keyvals:\SetTblrInner#c,\begin{+matrix}#c,\begin{+bmatrix}#c,\begin{+Bmatrix}#c,\begin{+pmatrix}#c,\begin{+vmatrix}#c,\begin{+Vmatrix}#c,\begin{+cases}#c
process=%<function%>
#endkeyvals

\cellGetText{rownum}{colnum}
\cellSetText{rownum}{colnum}{text}
\cellSetStyle{rownum}{colnum}{style}
\rowSetStyle{rownum}{style}
\columnSetStyle{style}