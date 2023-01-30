# epic package
# Matthew Bertucci 3/8/2022 for v1.2

\multiputlist(x,y)(Δx,Δy){item1,item2,...}#/picture
\multiputlist(x,y)(Δx,Δy)[pos]{item1,item2,...}#/picture
\lop{arg1}\to{arg2}#*
\to{arg}#S
\lopoff#*
\matrixput(x,y)(Δx1,Δy1){n1}(Δx2,Δy2){n2}{object}#/picture
\grid(width,height)(Δwidth,Δheight)
\grid(width,height)(Δwidth,Δheight)[x0,y0]
\dottedline{%<dashgap%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dottedline[%<character%>]{%<dashgap%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashline{%<dashlength%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashline{%<dashlength%>}[%<dashgap%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashline[%<stretch%>]{%<dashlength%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashline[%<stretch%>]{%<dashlength%>}[%<dashgap%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashlinestretch#*
\drawline(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\drawline[%<stretch%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\drawlinestretch#*
\lineslope#*
\jput(x,y){object}#/picture
\begin{dottedjoin}{dotgap}#/picture
\begin{dottedjoin}[character]{dotgap}#/picture
\end{dottedjoin}#/picture
\begin{dashjoin}{dashlength}#/picture
\begin{dashjoin}{dashlength}[dashgap]#/picture
\begin{dashjoin}[stretch]{dashlength}#/picture
\begin{dashjoin}[stretch]{dashlength}[dashgap]#/picture
\end{dashjoin}#/picture
\begin{drawjoin}#/picture
\begin{drawjoin}[stretch]#/picture
\end{drawjoin}#/picture
\picsquare
\putfile{file}{object}
\sqrtandstuff{Δx}{Δy}{dotgap}#*

\dashjoin#S
\dottedjoin#S
\drawjoin#S
\enddashjoin#S
\enddottedjoin#S
\enddrawjoin#S
\splittwoargs#S
\iflistnonempty#S
\listnonemptytrue#S
\listnonemptyfalse#S
