# pstricks-add package
# Matthew Bertucci 2023/04/18 for v3.94

#include:pstricks
#include:pst-plot
#include:pst-node
#include:pst-3d
#include:pst-math
#include:multido
#include:pst-calculate
#include:pst-xkey
#include:pst-arrow

\BeginSaveFinalState
\defineTColor[options%keyvals]{name}{color}#*
\defineTColor{name}{color}
\EndSaveFinalState
\parseRP#*
\psBrace(A)(B)#*
\psbrace(A)(B){text}
\psBrace*(A)(B)#*
\psBrace*[options%keyvals](A)(B)#*
\psBrace[options%keyvals](A)(B)#*
\psbrace[options%keyvals](A)(B){text}
\psCallout(x,y){text}
\psCallout[options%keyvals](x,y){text}
\psCancel*[options%keyvals]{stuff}
\psCancel*{stuff}
\psCancel[options%keyvals]{stuff}
\psCancel{stuff}
\psChart[options%keyvals]{list1}{list2}{radius}
\psChart{list1}{list2}{radius}
\psCircleTangents(x1,y1)(x2,y2){radius}
\psCircleTangents(x1,y1){radius1}(x2,y2){radius2}
\psComment(x0,y0)(x1,y1){text}
\psComment(x0,y0)(x1,y1){text}[line macro][put macro]#*
\psComment*(x0,y0)(x1,y1){text}
\psComment*(x0,y0)(x1,y1){text}[line macro][put macro]#*
\psComment*[options%keyvals](x0,y0)(x1,y1){text}
\psComment*[options%keyvals](x0,y0)(x1,y1){text}[line macro][put macro]
\psComment*[options%keyvals]{arrows}(x0,y0)(x1,y1){text}
\psComment*[options%keyvals]{arrows}(x0,y0)(x1,y1){text}[line macro][put macro]#*
\psComment*{arrows}(x0,y0)(x1,y1){text}
\psComment*{arrows}(x0,y0)(x1,y1){text}[line macro][put macro]#*
\psComment[options%keyvals](x0,y0)(x1,y1){text}
\psComment[options%keyvals](x0,y0)(x1,y1){text}[line macro][put macro]
\psComment[options%keyvals]{arrows}(x0,y0)(x1,y1){text}
\psComment[options%keyvals]{arrows}(x0,y0)(x1,y1){text}[line macro][put macro]#*
\psComment{arrows}(x0,y0)(x1,y1){text}
\psComment{arrows}(x0,y0)(x1,y1){text}[line macro][put macro]#*
\pscurvepoints[options%keyvals]{tmin}{tmax}{function of t%definition}{root}
\pscurvepoints{tmin}{tmax}{function of t%definition}{array root}
\psdice[options%keyvals]{number}
\psdice{number}
\psDiffSumValue
\psEllipseTangents(x0,y0)(a,b)(xp,yp)
\psEllipseTangentsN(x0,y0)(a,b)(xp,yp){node name}#*
\psFormatInt[options%keyvals]{integer}
\psFormatInt{integer}
\psGetDistance(x1,y1)(x2,y2){macro%cmd}#d
\psGetDistance[decimals](x1,y1)(x2,y2){macro%cmd}#d
\psGetSlope(x1,y1)(x2,y2){macro%cmd}#d
\psGTriangle(x1,y1)(x2,y2)(x3,y3){color}{color}{color}#S
\psGTriangle(x1,y1)(x2,y2)(x3,y3){color1}{color2}{color3}
\psHomothetie(x,y){factor}{stuff}
\psHomothetie[options%keyvals](x,y){factor}{stuff}
\psIntersectionPoint(x0,y0)(x1,y1)(x2,y2)(x3,y3){node name}
\psKiviat[options%keyvals]{number of edges}{radius}
\psKiviat{number of edges}{radius}
\psKiviatAxes[options%keyvals]{number of edges}{radius}
\psKiviatAxes{number of edges}{radius}
\psKiviatLine[options%keyvals]{list}
\psKiviatLine{list}
\psKiviatTicklines{n}{radius}
\psKiviatTicklines[options%keyvals]{n}{radius}
\psLeftSumValue
\pslineByHand(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\pslineByHand[%<options%>](%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\psMatrixPlot[options%keyvals]{rows}{columns}{data file%file}
\psMatrixPlot{rows}{columns}{data file%file}
\psMiddleSumValue
\psOlympicRings(x,y)
\psOlympicRings[options%keyvals](x,y)
\psParallelLine(x0,y0)(x1,y1)(x2,y2){length}{end node name}
\psParallelLine[options%keyvals](x0,y0)(x1,y1)(x2,y2){length}{end node name}
\psParallelLine[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2){length}{end node name}
\psParallelLine{arrows}(x0,y0)(x1,y1)(x2,y2){length}{end node name}
\psColorLine(x0,y0)(x1,y1)
\psColorLine{arrows}(x0,y0)(x1,y1)
\psColorLine[options%keyvals](x0,y0)(x1,y1)
\psColorLine[options%keyvals]{arrows}(x0,y0)(x1,y1)
\psparallelogrambox[options%keyvals]{stuff}
\psparallelogrambox{stuff}
\psplotDiffEqn[%<options%>]{%<x0%>}{%<x1%>}{%<y0%>}{%<f(x,y,y',...)%>}
\psplotDiffEqn{%<x0%>}{%<x1%>}{%<y0%>}{%<f(x,y,y',...)%>}
\psplotTangent*[options%keyvals]{x}{dx}{function%definition}
\psplotTangent*{x}{dx}{function%definition}
\psplotTangent[options%keyvals]{x}{dx}{function%definition}
\psplotTangent{x}{dx}{function%definition}
\pspolylineticks[options%keyvals]{root name}{function}{first tick}{tick count}
\pspolylineticks{root name}{function}{first tick}{tick count}
\psRandom(xmin,ymin)(xmax,ymax){clip path}
\psRandom(xmin,ymin){clip path}
\psRandom[options%keyvals](xmin,ymin)(xmax,ymax){clip path}
\psRandom[options%keyvals](xmin,ymin){clip path}
\psRandom[options%keyvals]{}
\psRandom{}
\psRandomPointArea[options%keyvals]{number}{function%definition}
\psRandomPointArea{number}{function%definition}
\psRelLine(x0,y0)(x1,y1){length factor}{end node name}
\psRelLine[options%keyvals](x0,y0)(x1,y1){length factor}{end node name}
\psRelLine[options%keyvals]{arrows}(x0,y0)(x1,y1){length factor}{end node name}
\psRelLine{arrows}(x0,y0)(x1,y1){length factor}{end node name}
\psRiemannSum(x0,x1){n}{function%definition}
\psRightSumValue
\psrotate(x,y){angle}{stuff}
\psrotate[options%keyvals](x,y){angle}{stuff}
\psStartPoint(x,y)
\psStartPoint[node basename](x,y)
\psStep(x,y){n}{function%definition}
\psStep[options%keyvals](x,y){n}{function%definition}
\psTangentLine(x1,y1)(x2,y2)(x3,y3){x}{dx}
\psTangentLine[options%keyvals](x1,y1)(x2,y2)(x3,y3){x}{dx}
\pstContour[options%keyvals]{data file%file}
\pstContour{data file%file}
\pstricksaddFV#S
\PSTricksAddLoaded#S
\psVector(%<x1,y1%>)%<...(xN,yN)%>
\psVector[%<options%>](%<x1,y1%>)%<...(xN,yN)%>
\psVector[%<options%>]<%<x0,y0%>>(%<x1,y1%>)%<...(xN,yN)%>
\psVector<%<x0,y0%>>(%<x1,y1%>)%<...(xN,yN)%>
\psVectorName#*
\pswavelengthToGRAY#*
\pswavelengthToRGB#*
\Put(position){stuff}
\Put*(position){stuff}
\Put*[options%keyvals](position){stuff}
\Put*[options%keyvals]{ref}(position){stuff}
\Put*{ref}(position){stuff}
\Put[options%keyvals](position){stuff}
\Put[options%keyvals]{ref}(position){stuff}
\Put{ref}(position){stuff}
\resetOptions
\rmultiput*[%<options%>]{%<stuff%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\rmultiput*{%<stuff%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\rmultiput[%<options%>]{%<stuff%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\rmultiput{%<stuff%>}(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
