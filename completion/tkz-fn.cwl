# tkz-fn package
# Matthew Bertucci 2026/10/24 for v1.00c

#include:iftex
#include:tikz
#include:tikzlibraryplotmarks

#keyvals:\usepackage/tkz-fn#c
us
fr
#endkeyvals

\tkzFnArea(function)
\tkzFnArea[options%keyvals](function)
\tkzFnAxes
\tkzFnAxes[options%keyvals]
\tkzFnAxisX
\tkzFnAxisX[options%keyvals]
\tkzFnAxisY
\tkzFnAxisY[options%keyvals]
\tkzFnClip
\tkzFnClip[margin]
\tkzFnDefPoint(function){point}
\tkzFnDefPoint[options%keyvals](function){point}
\tkzFnDefPointXY(x,y){point}
\tkzFnDefPointXY[options%keyvals](x,y){point}
\tkzFnDef{name}}{expression%definition}
\tkzFnDraw(name)
\tkzFnDraw[options%keyvals](name)
\tkzFnDraw[options%keyvals]{expression%definition}
\tkzFnDrawData[options%keyvals]{x1/y1,x2/y2,...}
\tkzFnDrawData{x1/y1,x2/y2,...}
\tkzFnDrawPoints(point1,point2,...)
\tkzFnDrawPoints[options%keyvals](point1,point2,...)
\tkzFnDraw{expression%definition}
\tkzFnGrid(x1,y1)(x2,y2)
\tkzFnGrid[options%keyvals](x1,y1)(x2,y2)
\tkzFnHLine[options%keyvals]{list}
\tkzFnHLines[options%keyvals]{list}
\tkzFnHLines{list}
\tkzFnHLine{list}
\tkzFnInit
\tkzFnInit[options%keyvals]
\tkzFnLabelPoint(point)
\tkzFnLabelPoint[options%keyvals](point)
\tkzFnLabelPoints(point1,point2,...)
\tkzFnLabelPoints[options%keyvals](point1,point2,...)
\tkzFnMarkPoints(function)(x values)
\tkzFnMarkPoints[options%keyvals](function)(x values)
\tkzFnParam[%<options%>]{%<x(t)%>}{%<y(t)%>}
\tkzFnParam{%<x(t)%>}{%<y(t)%>}
\tkzFnPolar[%<options%>]{%<ρ(t)%>}
\tkzFnPolar{%<ρ(t)%>}
\tkzFnPrint[decimals]{Lua expr}
\tkzFnPrintCoord(point)
\tkzFnPrintCoord[decimals](point)
\tkzFnPrintInterval[type]{a}{b}
\tkzFnPrintInterval{a}{b}
\tkzFnPrint{Lua expr}
\tkzFnRep
\tkzFnRep[options%keyvals]
\tkzFnRiemann(function)
\tkzFnRiemann[options%keyvals](function)
\tkzFnSetup{options%keyvals}
\tkzFnShowCoord(point)
\tkzFnShowCoord[options%keyvals](point)
\tkzFnTangent(function,x)
\tkzFnTangent[options%keyvals](function,x)
\tkzFnText(x,y){text}
\tkzFnText[options%keyvals](x,y){text}
\tkzFnVLine[options%keyvals]{list}
\tkzFnVLines[options%keyvals]{list}
\tkzFnVLines{list}
\tkzFnVLine{list}