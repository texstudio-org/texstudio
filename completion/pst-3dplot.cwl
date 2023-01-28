# pst-3dplot package
# Matthew Bertucci 2/25/2022 for v0.2

#include:pstricks
#include:pst-3d
#include:pst-plot
#include:pst-node
#include:multido
#include:pst-xkey

\pstThreeDCoor
\pstThreeDCoor[options%keyvals]

#keyvals:\pstThreeDCoor#c
drawing#true,false
Alpha=%<degrees%>
Beta=%<degrees%>
xMin=%<number%>
xMax=%<number%>
yMin=%<number%>
yMax=%<number%>
zMin=%<number%>
zMax=%<number%>
nameX=%<name%>
spotX=%<degrees%>
nameY=%<name%>
spotY=%<degrees%>
nameZ=%<name%>
spotZ=%<degrees%>
IIIDticks#true,false
IIIDlabels#true,false
Dx=%<number%>
Dy=%<number%>
Dz=%<number%>
IIIDxTicksPlane=#xy,xz,yz
IIIDyTicksPlane=#xy,xz,yz
IIIDzTicksPlane=#xy,xz,yz
IIIDticksize=%<number%>
IIIDxticksep=%<number%>
IIIDyticksep=%<number%>
IIIDzticksep=%<number%>
RotX=%<degrees%>
RotY=%<degrees%>
RotZ=%<degrees%>
RotAngle=%<degrees%>
xRotVec=%<degrees%>
yRotVec=%<degrees%>
zRotVec=%<degrees%>
RotSequence=#xyz,xzy,yxz,yzx,zxy,zyx,quaternion
RotSet=#set,concat,keep
eulerRotation#true,false
IIIDOffset={(%<x,y,z%>)}
zlabelFactor=%<text%>
comma#true,false
linewidth=##L
linecolor=#%color
planecorr=#off,normal,xyrot
linestyle=%<style%>
#endkeyvals

\psxyzlabel{text}#*

\pstThreeDPlaneGrid(xmin,ymin)(xmax,ymax)
\pstThreeDPlaneGrid[options%keyvals](xmin,ymin)(xmax,ymax)

#keyvals:\pstThreeDPlaneGrid#c
planeGrid=#xy,xz,yz
subticks=%<integer%>
planeGridOffset=%<number%>
#endkeyvals

\pstThreeDPut(x,y,z){stuff}
\pstThreeDPut[options%keyvals](x,y,z){stuff}
\pstPlanePut(x,y,z){stuff}
\pstPlanePut[options%keyvals](x,y,z){stuff}
\pstThreeDNode(x,y,z){node name}
\pstThreeDDot(x,y,z)
\pstThreeDDot[options%keyvals](x,y,z)
\pstThreeDLine(%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstThreeDLine{%<arrows%>}(%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstThreeDLine[%<options%>](%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstThreeDLine[%<options%>]{%<arrows%>}(%<x1,y1,z1%>)(%<x2,y2,z2%>)%<...(xN,yN,zN)%>
\pstThreeDTriangle(x1,y1,z1)(x2,y2,z2)(x3,y3,z3)
\pstThreeDTriangle[options%keyvals](x1,y1,z1)(x2,y2,z2)(x3,y3,z3)
\pstThreeDSquare(x0,y0,z0)(x1,y1,z1)(x2,y2,z2)
\pstThreeDSquare[options%keyvals](x0,y0,z0)(x1,y1,z1)(x2,y2,z2)
\pstThreeDBox(x0,y0,z0)(x1,y1,z1)(x2,y2,z2)(x3,y3,z3)
\pstThreeDBox[options%keyvals](x0,y0,z0)(x1,y1,z1)(x2,y2,z2)(x3,y3,z3)
\psBox(x,y,z){width}{depth}{height}
\psBox[options%keyvals](x,y,z){width}{depth}{height}
\pstThreeDEllipse(cx,cy,cz)(ux,uy,uz)(vx,vy,vz)
\pstThreeDEllipse[options%keyvals](cx,cy,cz)(ux,uy,uz)(vx,vy,vz)
\pstThreeDCircle(cx,cy,cz)(ux,uy,uz)(vx,vy,vz)
\pstThreeDCircle[options%keyvals](cx,cy,cz)(ux,uy,uz)(vx,vy,vz)
\pstIIIDCylinder(x,y,z){radius}{height}
\pstIIIDCylinder[options%keyvals](x,y,z){radius}{height}
\psCylinder(x,y,z){radius}{height}
\psCylinder[options%keyvals](x,y,z){radius}{height}
\pstParaboloid{height}{radius}
\pstParaboloid[options%keyvals]{height}{radius}
\pstThreeDSphere(x,y,z){radius}
\pstThreeDSphere[options%keyvals](x,y,z){radius}

\psplotThreeD(xmin,xmax)(ymin,ymax){function%definition}
\psplotThreeD[options%keyvals](xmin,xmax)(ymin,ymax){function%definition}
\parametricplotThreeD(t1,t2)(u1,u2){functions x y z%definition}
\parametricplotThreeD[options%keyvals](t1,t2)(u1,u2){functions x y z%definition}
\parametricplotThreeD(t1,t2){functions x y z%definition}
\parametricplotThreeD[options%keyvals](t1,t2){functions x y z%definition}

#keyvals:\psplotThreeD#c,\parametricplotThreeD#c
plotstyle=#dots,line,polygon,curve,ecurve,ccurve,none
showpoints#true,false
xPlotpoints=%<number%>
yPlotpoints=%<number%>
drawStyle=#xLines,yLines,xyLines,yxLines
hiddenLine#true,false
algebraic#true,false
linewidth=##L
fillstyle=%<style%>
linecolor=#%color
#endkeyvals

\fileplotThreeD{datafile%file}#i
\fileplotThreeD[options%keyvals]{datafile%file}#i
\dataplotThreeD{data object}
\dataplotThreeD[options%keyvals]{data object}
\listplotThreeD{data object}
\listplotThreeD[options%keyvals]{data object}
\ScalePointsThreeD#*

\pstRotPointIIID(x,y,z){xmacro%cmd}{ymacro%cmd}{zmacro%cmd}#d
\pstRotPointIIID[options%keyvals](x,y,z){xmacro%cmd}{ymacro%cmd}{zmacro%cmd}#d

#keyvals:\pstRotPointIIID#c
RotX=%<degrees%>
RotY=%<degrees%>
RotZ=%<degrees%>
#endkeyvals

\getThreeDCoor(vector){macro%cmd}#d
\pstaddThreeDVec(vectorA)(vectorB){xmacro%cmd}{ymacro%cmd}{zmacro%cmd}#d
\pstsubThreeDVec(vectorA)(vectorB){xmacro%cmd}{ymacro%cmd}{zmacro%cmd}#d

# not documented
\setIIIDplotDefaults#*
\ABinterCD(A)(B)(C)(D){name}#*
\Arrows(A)(B)#*
\Arrows[options%keyvals](A)(B)#*
\CalculateCos{angle}#*
\CalculateSin{angle}#*
\IIIDplotfiledate#S
\IIIDplotfileversion#S
\NormalIIIDCoor#*
\Parallel(A)(B)(C)(D){name}#*
\Parallel[options%keyvals](A)(B)(C)(D){name}#*
\UseCos{angle}#*
\UseSin{angle}#*
\arrowLine(A)(B){n}#*
\arrowLine[options%keyvals](A)(B){n}#*
\noPT{arg}#*
\nodeBetween(A)(B){name}#*
\psBeforeLine(A)(B){name}#*
\psBeforeLine[options%keyvals](A)(B){name}#*
\psOutLine(A)(B){name}#*
\psOutLine[options%keyvals](A)(B){name}#*
\psplotImpIIID(x1,y1,z1)(x2,y2,z2){function%definition}#*
\psplotImpIIID(x1,y1,z1)(x2,y2,z2)[PS code]{function%definition}#*
\pstAdd{num1}{num2}{macro%cmd}#*d
\pstDiv{num1}{num2}{macro%cmd}#*d
\pstIIIDNode(A)(B)(C)(D)(E)#*
\pstIIIDNode[options%keyvals](A)(B)(C)(D)(E)#*
\pstMul{num1}{num2}{macro%cmd}#*d
\pstRotNodeIIID(x1,y1,z1)(x2,y2,z2){name}#*
\pstSinCos{angle}{sine macro%cmd}{cosine macro%cmd}#*d
\pstSub{num1}{num2}{macro%cmd}#*d
\pstThreeDCone(cx,cy,cz)(ux,uy,uz)(vx,vy,vz){height}#*
\pstThreeDCone[options%keyvals](cx,cy,cz)(ux,uy,uz)(vx,vy,vz){height}#*
\pstThreeDPrism#*
\pstThreeDmoveto(x,y,z)#*
\pstUThreeDPut(x,y,z){stuff}#*
\pstUThreeDPut[refangle](x,y,z){stuff}#*
\rotateFrame(A)(B)(C)(D){angle}
\rotateNode(A){angle}#*
\rotateTriangle(A)(B)(C){angle}#*
\PSTThreeDplotLoaded#S
\pszunit#*

# compatibility
\pstThreeDPlotFunc(xmin,xmax)(ymin,ymax){function%definition}#S
\pstThreeDPlotFunc[options%keyvals](xmin,xmax)(ymin,ymax){function%definition}#S
