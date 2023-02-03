# mode: pst-plot.sty
# dani/2006-02-22
# Matthew Bertucci 2022-02-20 for v1.93

#include:pstricks
#include:pst-xkey
#include:multido
#include:pstricks-add
#include:pst-tools

#keyvals:\usepackage/pst-plot#c
97
#endkeyvals

\begin{psgraph}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#\pictureHighlight
\begin{psgraph}[options%keyvals](x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}
\begin{psgraph}[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}
\begin{psgraph}{arrows}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}
\begin{psgraph*}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*\pictureHighlight
\begin{psgraph*}[options%keyvals](x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\begin{psgraph*}[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\begin{psgraph*}{arrows}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\dataplot[options%keyvals]{macro}
\dataplot{macro}
\end{psgraph}
\end{psgraph*}#*
\endpsgraph#*
\fileplot[options%keyvals]{file}
\fileplot{file}
\ifSpecialLabelsDone#*
\listplot[options%keyvals]{list}
\listplot{data}
\parametricplot[options%keyvals]{tmin}{tmax}[PS commands]{function%definition}
\parametricplot[options%keyvals]{tmin}{tmax}{function%definition}
\parametricplot{tmin}{tmax}[PS commands]{function%definition}#*
\parametricplot{tmin}{tmax}{function%definition}
\psaxes(x0,y0)(x1,y1)(x2,y2)
\psaxes(x0,y0)(x1,y1)(x2,y2)[Xlabel,Xangle][Ylabel,Yangle]#*
\psaxes[options%keyvals](x0,y0)(x1,y1)(x2,y2)
\psaxes[options%keyvals](x0,y0)(x1,y1)(x2,y2)[Xlabel,Xangle][Ylabel,Yangle]
\psaxes[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)
\psaxes[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)[Xlabel,Xangle][Ylabel,Yangle]
\psaxes{arrows}(x0,y0)(x1,y1)(x2,y2)
\psaxes{arrows}(x0,y0)(x1,y1)(x2,y2)[Xlabel,Xangle][Ylabel,Yangle]#*
\psBoxplot[options%keyvals]{macro}
\psBoxplot{macro}
\psCoordinates(x,y)
\psCoordinates[options%keyvals](x,y)
\psdataplot[options%keyvals]{macro}#*
\psdataplot{macro}#*
\psfileplot[options%keyvals]{file}#*
\psfileplot{file}#*
\psFixpoint[%<options%>]{%<x0%>}{%<f(x)%>}{%<n%>}
\psFixpoint{%<x0%>}{%<f(x)%>}{%<n%>}
\psgraph(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\psgraph[options%keyvals](x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\psgraph[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\psgraph{arrows}(x0,y0)(x1,y1)(x2,y2){xlength%l}{ylength%l}#*
\psgraphLLx
\psgraphLLy
\psgraphURx
\psgraphURy
\pshlabel
\pslegend[reference](xoffset,yoffset){text}
\pslegend[reference]{text}
\pslegend{text}
\pslistplot[options%keyvals]{list}#*
\pslistplot{data}#*
\psNewton[%<options%>]{%<x_0%>}{%<f(x)%>}{%<n%>}
\psNewton[%<options%>]{%<x0%>}{%<f(x)%>}[%<f'(x)%>]{%<n%>}
\psNewton{%<x0%>}{%<f(x)%>}[%<f'(x)%>]{%<n%>}
\psNewton{%<x0%>}{%<f(x)%>}{%<n%>}
\psparametricplot[options%keyvals]{tmin}{tmax}[PS commands]{function%definition}#*
\psparametricplot[options%keyvals]{tmin}{tmax}{function%definition}#*
\psparametricplot{tmin}{tmax}[PS commands]{function%definition}#*
\psparametricplot{tmin}{tmax}{function%definition}#*
\psPi#*
\psPiFour#*
\psPiH#*
\psPiTwo#*
\psplot[options%keyvals]{xmin}{xmax}[PS commands]{function%definition}
\psplot[options%keyvals]{xmin}{xmax}{function%definition}
\psplot{xmin}{xmax}[PS commands]{function%definition}#*
\psplot{xmin}{xmax}{function%definition}
\psplotinit{arg}#*
\psplotstyle#*
\psPutXLabel{arg}#*
\psPutYLabel{arg}#*
\psreadDataColumn[options%keyvals]{colNo}{delim}{macro%cmd}{file%file}#d
\psreadDataColumn{colNo}{delim}{macro%cmd}{file%file}#d
\psResetPlotValues#*
\psrotatebox{angle}{contents}#*
\PSTplotLoaded#S
\pstRadUnit
\pstRadUnitInv
\pstScalePoints(xscale,yscale){xPS}{yPS}
\pstXPSScale#*
\pstXScale#*
\pstYPSScale#*
\pstYScale#*
\psVectorfield(%<x0,y0%>)(%<x1,y1%>){%<f'(x,y)%>}
\psVectorfield[%<options%>](%<x0,y0%>)(%<x1,y1%>){%<f'(x,y)%>}
\psvlabel
\psxlabelsep#*
\psxsubticklinestyle#*
\psxTick(x value){label}
\psxTick[options%keyvals](x value){label}
\psxTick[options%keyvals]{rotation}(x value){label}
\psxTick{rotation}(x value){label}
\psxticklinestyle#*
\psylabelsep#*
\psysubticklinestyle#*
\psyTick(y value){label}
\psyTick[options%keyvals](y value){label}
\psyTick[options%keyvals]{rotation}(y value){label}
\psyTick{rotation}(y value){label}
\psyticklinestyle#*
\readdata{macro%cmd}{file%file}#d
\readdata[options%keyvals]{macro%cmd}{file%file}#d
\savedata{macro%cmd}[data]#d
\setDefaulthLabels#*
\setDefaultvLabels#*
\setFractionhLabels#*
\setFractionvLabels#*
\setTrighLabels#*
\setTrigvLabels#*
\SpecialLabelsDonefalse#*
\SpecialLabelsDonetrue#*
\stripDecimals#S

#keyvals:\readdata#c
ignoreLines=%<integer%>
nStep=%<integer%>
#endkeyvals
