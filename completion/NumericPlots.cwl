# NumericPlots package
# Matthew Bertucci 3/9/2022 for v2.0.1

#include:calc
#include:fp
#include:ifthen
#include:pstricks
#include:pst-node
#include:pst-plot
#include:pstricks-add
#include:xcolor
#include:xkeyval
#include:xkvview

#keyvals:\usepackage/NumericPlots#c
beamer
xAxisStyle=%<style%>
yAxisStyle=%<style%>
LabelOption=%<font commands%>
TickLabelOption=%<font commands%>
BW
#endkeyvals

\begin{NumericDataPlot}{width}{height}#\pictureHighlight
\begin{NumericDataPlot}[options%keyvals]{width}{height}#\pictureHighlight
\end{NumericDataPlot}

#keyvals:\begin{NumericDataPlot}#c
xPicMin=%<value%>
xPicMax=%<value%>
yPicMin=%<value%>
yPicMax=%<value%>
TickLength=%<value%>
llx=##L
lly=##L
urx=##L
ury=##L
#endkeyvals

\setxAxis{keyvals}

#keyvals:\setxAxis#c
xO=%<value%>
xMin=%<value%>
xMax=%<value%>
xCoordMin=%<value%>
xCoordMax=%<value%>
Dx=%<value%>
dx=%<value%>
DDx=%<value%>
xLog
xLogNoSubGrid
#endkeyvals

\setyAxis{keyvals}

#keyvals:\setyAxis#c
yO=%<value%>
yMin=%<value%>
yMax=%<value%>
yCoordMin=%<value%>
yCoordMax=%<value%>
Dy=%<value%>
dy=%<value%>
DDy=%<value%>
yLog
yLogNoSubGrid
#endkeyvals

\plotxAxis{label text}
\plotxAxis[options%keyvals]{label text}
\plotyAxis{label text}
\plotyAxis[options%keyvals]{label text}

#keyvals:\plotxAxis#c,\plotyAxis#c
LabelOption=%<font commands%>
TickLabelOption=%<font commands%>
LabelSep=##L
NoGrid
NoLabel
NoTicks
NoTickLabel
LabelPos=%<factor%>
LabelRefPt=
AxisStyle=#Boxed,Lower,Upper,Right,Left,None
LabelRot=%<degrees%>
TickLabelRot=%<degrees%>
TickLabelSep=##L
LabelOrientation=#l,c,r
TickLabelRefPt=
#endkeyvals

\LegendDefinition{definition}
\LegendDefinition[options%keyvals]{definition}

#keyvals:\LegendDefinition#c
nrCols=%<integer%>
LabelOrientation=#l,c,r
#endkeyvals

\LegLine{\psline keys}
\LegLine[legend options]{\psline keys}
\LegDot{\psdots keys}
\LegDot[legend options]{\psdots keys}

\putN{stuff}
\putS{stuff}
\putW{stuff}
\putE{stuff}
\putNW{stuff}
\putNE{stuff}
\putSW{stuff}
\putSE{stuff}

\NDPput[options%keyvals]{stuff}

#keyvals:\NDPput#c
x=%<value%>
y=%<value%>
RefPoint=
Rot=%<degrees%>
#endkeyvals

\putExpX{stuff}
\putExpY{stuff}

\NDPhline{y}
\NDPhline[options%keyvals]{y}
\NDPvline{x}
\NDPvline[options%keyvals]{x}
\NDPline{x1}{y1}{x2}{y2}
\NDPline[options%keyvals]{x1}{y1}{x2}{y2}

#keyvals:\NDPhline#c,\NDPvline#c,\NDPline#c
linecolor=#%color
linestyle=%<style%>
linewidth=##L
style=%<style%>
#endkeyvals

\NDPhbox{y1}{y2}
\NDPhbox[options%keyvals]{y1}{y2}
\NDPvbox{x1}{x2}
\NDPvbox[options%keyvals]{x1}{x2}
\NDPbox{x1}{y1}{x2}{y2}
\NDPbox[options%keyvals]{x1}{y1}{x2}{y2}

#keyvals:\NDPhbox#c,\NDPvbox#c,\NDPbox#c
fillstyle=%<style%>
fillcolor=#%color
opacity=%<factor%>
linestyle=%<style%>
#endkeyvals

\plotxGrid
\plotyGrid

\multilistplot{options%keyvals}{identifier}

\PutTickLabelXaxis[options%keyvals]{label}

#keyvals:\PutTickLabelXaxis#c
x=%<value%>
TickLabelSep=##L
ax=#lower,upper
#endkeyvals

\PutTickLabelYaxis[options%keyvals]{label}

#keyvals:\PutTickLabelYaxis#c
y=%<value%>
TickLabelSep=##L
ax=#left,right
#endkeyvals

LineColorA#B
LineColorB#B
LineColorC#B
LineColorD#B
LineColorE#B
LineColorF#B
LineColorG#B
LineColorH#B
LineColorX#B
LineColorY#B

# not documented
\CheckIfColumntypeDefined{coltype}#*
\CPicHeight#*
\CPicWidth#*
\ifLegendOrientationCenter#*
\ifLegendOrientationLeft#*
\ifLegendOrientationRight#*
\iSubb#*
\LegLineOld[style]{keyvals}#S#*
\LegLineOld{keyvals}#S#*
\LegLineWidth#*
\LogxAxis#*
\LogxAxisLabel{label}#*
\LogyAxis#*
\LogyAxisLabel{label}#*
\makeXLabel{label}#*
\makeXTickLabel{label}#*
\makeYLabel{label}#*
\makeYTickLabel{label}#*
\NDPputRotation#*
\NDPputXcoord#*
\NDPputXcoordOne#*
\NDPputYcoord#*
\NDPRefPoint#*
\nrAxisStyle#*
\nrLegendCols#*
\nrLegOrient#*
\nrPutAxis#*
\NumDataPlotBaseline#*
\NumDataPlotBuffer#*
\NumDataPlotBufferI#*
\NumDataPlotDDx#*
\NumDataPlotDDy#*
\NumDataPlotDistance#*
\NumDataPlotDx#*
\NumDataPlotdx#*
\NumDataPlotdxLabels#*
\NumDataPlotDy#*
\NumDataPlotdy#*
\NumDataPlotdyLabels#*
\NumDataPlotGxPicMax#*
\NumDataPlotGxPicMin#*
\NumDataPlotGyPicMax#*
\NumDataPlotGyPicMin#*
\NumDataPlotLnTen#*
\NumDataPlotTickPos#*
\NumDataPlotxCoordMax#*
\NumDataPlotxCoordMin#*
\NumDataPlotxCoordRange#*
\NumDataPlotxDataCoordRatio#*
\NumDataPlotxLabelOption#*
\NumDataPlotxLabelOrientation#*
\NumDataPlotxLabelPos#*
\NumDataPlotxMax#*
\NumDataPlotxMin#*
\NumDataPlotxO#*
\NumDataPlotxRange#*
\NumDataPlotxTickBaseline#*
\NumDataPlotxTickDistance#*
\NumDataPlotxTickLabelOption#*
\NumDataPlotxTickLabelRot#*
\NumDataPlotyCoordMax#*
\NumDataPlotyCoordMin#*
\NumDataPlotyCoordRange#*
\NumDataPlotyDataCoordRatio#*
\NumDataPlotyLabelOption#*
\NumDataPlotyLabelOrientation#*
\NumDataPlotyLabelPos#*
\NumDataPlotyMax#*
\NumDataPlotyMin#*
\NumDataPlotyO#*
\NumDataPlotyRange#*
\NumDataPlotyTickBaseline#*
\NumDataPlotyTickDistance#*
\NumDataPlotyTickLabelOption#*
\NumDataPlotyTickLabelRot#*
\OffsetHeight#*
\OffsetWidth#*
\origXLabelSep#*
\origXTickLabelSep#*
\origYLabelSep#*
\origYTickLabelSep#*
\plotxGridLine{value}#*
\plotxSubGridLine{value}#*
\plotxTickLabels{keyvals}#*
\plotyGridBoxed#*
\plotyGridLine{value}#*
\plotySubGridLine{value}#*
\plotyTickLabels{keyvals}#*
\PutLabelXaxis[options%keyvals]{label}#*
\PutLabelXaxis{label}#*
\PutLabelYaxis[options%keyvals]{label}#*
\PutLabelYaxis{label}#*
\repeatxAxis#*
\ScaleAxes#*
\StdLabelOption#*
\StdLLX#*
\StdLLY#*
\StdTickLabelOption#*
\StdURX#*
\StdURY#*
\TempLengthA#*
\TempLengthB#*
\testframe{content}#*
\theBufferCounter#*
\TickLabelsXLeft#*
\TickLabelsXRight#*
\TickLabelsYLeft#*
\TickLabelsYRight#*
\TicksXLeft#*
\TicksXRight#*
\TicksYLeft#*
\TicksYRight#*
\val#*
\xCoordOrig#*
\xLabelRefPt#*
\xLabelRot#*
\xLabelSep#*
\xLogSubGrid{value}#*
\xNrTickLabels#*
\xNrTicks#*
\xScaling#*
\xTickLabelRefPt#*
\xTickLabelSep#*
\xTickLength#*
\yCoordOrig#*
\yLabelRefPt#*
\yLabelRot#*
\yLabelSep#*
\yLogSubGrid{value}#*
\yNrTickLabels#*
\yNrTicks#*
\yScaling#*
\yTickLabelRefPt#*
\yTickLabelSep#*
\yTickLength#*