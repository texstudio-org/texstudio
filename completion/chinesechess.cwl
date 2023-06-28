# chinesechess package
# Matthew Bertucci 2022/05/11 for v1.2.0

#include:l3keys2e
#include:l3draw

#keyvals:\usepackage/chinesechess#c
draft
#endkeyvals

\cchessboard
\cchessboard[外观选项%keyvals]
\cchessboard*
\cchessboard*[外观选项%keyvals]
\cchessman{棋子列表}
\cchessman[外观选项%keyvals]{棋子列表}
\begin{setcchessman}
\begin{setcchessman}[外观选项%keyvals]
\end{setcchessman}
\begin{setcchessman*}
\begin{setcchessman*}[外观选项%keyvals]
\end{setcchessman*}
\init{棋子列表}
\set{棋子位置}{棋子位置列表}
\del{棋盘坐标}
\mov{棋子编码}{原棋盘坐标}{新棋盘坐标}
\printman{棋子编码%ref}#r
\printman[外观选项%keyvals]{棋子编码%ref}#r
\getpiece{棋子编码}
\getpiece[棋子字号]{棋子编码}
\piecechar{棋子编码}{棋子字符}
\resetpiece
\cchessset{外观选项%keyvals}

#keyvals:\cchessboard,\cchessboard*,\cchessman,\begin{setcchessman},\begin{setcchessman*},\printman,\cchessset
draft
gridsize=##L
boardtype=#x,x+,x+t,x+tn,x+Xtn
boardlinewd=##L
boardlinecolor=#%color
boardbg=%<imagefile%>
piecechar={%<piece%>}{%<symbol%>}
piecefont=%<font commands%>
piecetype=#o,oo,ooo
boxlinewd=##L
boxcolor=#%color
redpiece=#%color
blkpiece=#%color
lower=#%color
donut=#%color
redupper=#%color
blkupper=#%color
shadow=#%color
charstroke=#none,solid,white,bold,invisible
man={%<man options%>}
man/label=##l
man/nums=%<integer%>
resize={%<resize options%>}
resize/type=#none,real
resize/xscale=%<factor%>
resize/yscale=%<factor%>
resize/scale=%<factor%>
resize/width=##L
resize/height=##L
#endkeyvals
