# dsptricks package
# Matthew Bertucci 4/9/2022 for v1.0

#include:pstricks
#include:pstricks-add
#include:pst-xkey
#include:calc
#include:fp
#include:ifthen

\begin{dspPlot}{xmin,xmax}{ymin,ymax}#\pictureHighlight
\begin{dspPlot}[options%keyvals]{xmin,xmax}{ymin,ymax}
\end{dspPlot}
\dspW
\dspH
\begin{dspClip}
\end{dspClip}
\dspPlotFrame
\dspCustomTicks{pos1 label1 pos2 label2 ...}
\dspCustomTicks[options%keyvals]{pos1 label1 pos2 label2 ...}
\dspText(x,y){label}
\dspTaps{data}
\dspTaps[options%keyvals]{data}
\dspTapsAt{start}{data}
\dspTapsAt[options%keyvals]{start}{data}
\dspTapsFile{file}
\dspTapsFile[options%keyvals]{file}
\dspSignal{PS code}
\dspSignal[options%keyvals]{PS code}
\dspSignalOpt{init}{PS code}
\dspSignalOpt[options%keyvals]{init}{PS code}
\dspFunc{PS code}
\dspFunc[options%keyvals]{PS code}
\dspFuncData{data}
\dspFuncData[options%keyvals]{data}
\dspFuncFile{file}
\dspFuncFile[options%keyvals]{file}
\dspDiracs{pos1 label1 pos2 label2 ...}
\dspDiracs[options%keyvals]{pos1 label1 pos2 label2 ...}
\dspPeriodize
\begin{dspPZPlot}{M}#\pictureHighlight
\begin{dspPZPlot}[options%keyvals]{M}
\end{dspPZPlot}
\dspPZ{a,b}
\dspPZ[options%keyvals]{a,b}

# not documented
\PZAROC#*
\PZCROC#*
\PZLP#*
\PZLabel#*
\action#*
\begin{dspCP}#*
\end{dspCP}#*
\dirac#*
\doOnPairs{arg1}{arg2}#*
\dspAxisColor#*
\dspBU#*
\dspCA#*
\dspCPArcn{arg1}{arg2}{arg3}{arg4}{arg5}#*
\dspCPArc{arg1}{arg2}{arg3}{arg4}{arg5}#*
\dspCPCirclePoint{arg1}{arg2}{arg3}{arg4}#*
\dspCPCircle{arg1}{arg2}{arg3}#*
\dspCPPointSC{arg1}{arg2}{arg3}#*
\dspCPPoint{arg1}{arg2}{arg3}#*
\dspCPW#*
\dspCircle#*
\dspCircleLabel#*
\dspDotSize#*
\dspFrameLineWidth#*
\dspFuncDataAt{arg1}{arg2}{arg3}#*
\dspFuncOpt{arg1}{arg2}{arg3}#*
\dspHeight#*
\dspImageFile{arg1}#*
\dspLabels#*
\dspLegend#*
\dspLineWidth#*
\dspMainPeriod{arg1}#*
\dspMakeTicks#*
\dspMaxActX#*
\dspMinActX#*
\dspMkTk#*
\dspPeriod{arg1}#*
\dspPointValueSC{arg1}{arg2}{arg3}#*
\dspPointValue{arg1}{arg2}{arg3}#*
\dspPoints{arg1}{arg2}#*
\dspSetDims{arg1}#*
\dspSetupAxes#*
\dspShowImage[opt]{arg1}#*
\dspShowImage{arg1}#*
\dspStemWidth#*
\dspTickLabelX#*
\dspTickLabelY#*
\dspTickLabelYR#*
\dspTickLen#*
\dspTickLineWidth#*
\dspTickX#*
\dspTickY#*
\dspTmpLen#*
\dspUnitX#*
\dspUnitY#*
\dspWidth#*
\dspXLabel#*
\dspXTickGap#*
\dspXlabel#*
\dspXmax#*
\dspXmin#*
\dspYLabel#*
\dspYLabelR#*
\dspYTickGap#*
\haY#*
\incX#*
\incY#*
\outTicks#*
\pcorps#*
\removeFactor{arg1}#*
\sg#*
\sideGap#*
\simplifyPiFrac{arg1}{arg2}#*
\thisTickLabelX#*
\thisTickX#*
\tickColor#*
\twoArgSplit{arg1}#*
\xt#*
\yt#*
