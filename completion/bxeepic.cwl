# bxeepic package
# Matthew Bertucci 2022/07/26 for v0.2

#include:pict2e

#keyvals:\usepackage/bxeepic#c
safe
nosafe
# option passed to pict2e
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
pdftex
luatex
xetex
dvipsone
dviwindo
oztex
textures
pctexps
pctex32
vtex
original
ltxarrows
pstarrows
debug
hide
#endkeyvals

\bxGridLabelForm{real}#*
\dashlines
\dottedlines
\drawlines
\eepicdottedlines#*
\epicbottomgridlabelsep#*
\epicsidegridlabelsep#*
\epictopgridlabelsep#*
\flushjoin
\noeepicdottedlines#*
\spacewidth#*

# from epic (commented out lines not supported)
\multiputlist(x,y)(Δx,Δy){item1,item2,...}#/picture
\multiputlist(x,y)(Δx,Δy)[pos]{item1,item2,...}#/picture
\matrixput(x,y)(Δx1,Δy1){n1}(Δx2,Δy2){n2}{object}#/picture
\grid(width,height)(Δwidth,Δheight)
\grid(width,height)(Δwidth,Δheight)[x0,y0]
\dottedline{%<dashgap%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
## \dottedline[%<character%>]{%<dashgap%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashline{%<dashlength%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
## \dashline{%<dashlength%>}[%<dashgap%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashline[%<stretch%>]{%<dashlength%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
## \dashline[%<stretch%>]{%<dashlength%>}[%<dashgap%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\dashlinestretch#*
\drawline(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\drawline[%<stretch%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\drawlinestretch#*
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
\dashjoin#S
\dottedjoin#S
\drawjoin#S
\enddashjoin#S
\enddottedjoin#S
\enddrawjoin#S

# from eepic
\line(x,y){length}#/picture
\circle{diameter}#/picture
\circle*{diameter}#/picture
\oval(width,height)#/picture
\oval(width,height)[portion]#/picture
\maxovaldiam#*
\allinethickness{dimen}
\Thicklines#/picture
\path(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\spline(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\ellipse{x diameter}{y diameter}#/picture
\ellipse*{x diameter}{y diameter}#/picture
\arc{diameter}{start angle}{end angle}#/picture
## \filltype{type%keyvals}#/picture
## #keyvals:\filltype
## black
## white
## shade
## #endkeyvals
## \blacken#*/picture
## \whiten#*/picture
## \shade#*/picture
## \texture{hex nums}#*/picture
