# blochsphere package
# Matthew Bertucci 12/30/2021 for v3.3

#include:tikz
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.markings
#include:tikzlibrarycalc
#include:tikzlibraryfadings
#include:etoolbox
#include:environ
#include:ifthen
#include:kvsetkeys
#include:kvoptions

\begin{blochsphere}
\begin{blochsphere}[options%keyvals]
\end{blochsphere}

\drawBall
\drawBall[options%keyvals]
\drawBallGrid{lat deg sep}{long deg sep}
\drawBallGrid[options%keyvals]{lat deg sep}{long deg sep}
\setDrawingPlane{tilt angle}{rotation angle}
\setDrawingPlane[options%keyvals]
\setLatitudinalDrawingPlane{latitude}
\setLatitudinalDrawingPlane[options%keyvals]{latitude}
\setLongitudinalDrawingPlane{longitude}
\setLongitudinalDrawingPlane[options%keyvals]{longitude}
\drawCircle{tilt angle}{rotation angle}
\drawCircle[options%keyvals]{tilt angle}{rotation angle}
\drawGreatCircle{tilt angle}{rotation angle}
\drawGreatCircle[options%keyvals]{tilt angle}{rotation angle}
\drawSmallCircle{tilt angle}{rotation angle}{offset latitude}
\drawSmallCircle[options%keyvals]{tilt angle}{rotation angle}{offset latitude}
\drawLatitudeCircle{latitude}
\drawLatitudeCircle[options%keyvals]{latitude}
\drawLongitudeCircle{longitude}
\drawLongitudeCircle[options%keyvals]{longitude}
\drawRotationLeft{tilt angle}{rotation angle}{axis offset}{clear angle}
\drawRotationLeft[options%keyvals]{tilt angle}{rotation angle}{axis offset}{clear angle}
\drawRotationRight{tilt angle}{rotation angle}{axis offset}{clear angle}
\drawRotationRight[options%keyvals]{tilt angle}{rotation angle}{axis offset}{clear angle}
\drawAxis{tilt angle}{rotation angle}
\drawAxis[options%keyvals]{tilt angle}{rotation angle}
\labelPolar{TikZ label}{tilt angle}{rotation angle}
\labelPolar[options%keyvals]{TikZ label}{tilt angle}{rotation angle}
\labelLatLon{TikZ label}{latitude}{longitude}
\labelLatLon[options%keyvals]{TikZ label}{latitude}{longitude}
\drawStatePolar{TikZ label}{tilt angle}{rotation angle}
\drawStatePolar[options%keyvals]{TikZ label}{tilt angle}{rotation angle}
\drawStateLatLon{TikZ label}{latitude}{longitude}
\drawStateLatLon[options%keyvals]{TikZ label}{latitude}{longitude}

#keyvals:\usepackage/blochsphere#c,\begin{blochsphere},\drawBall,\drawBallGrid,\setDrawingPlane,\setLatitudinalDrawingPlane,\setLongitudinalDrawingPlane,\drawCircle,\drawGreatCircle,\drawSmallCircle,\drawLatitudeCircle,\drawLongitudeCircle,\drawRotationLeft,\drawRotationRight,\drawAxis,\labelPolar,\labelLatLon,\drawStatePolar,\drawStateLatLon,\computeOffset,\computeVisibility
radius=##L
tilt=%<degrees%>
rotation=%<degrees%>
color=#%color
opacity=%<factor%>
style={%<TikZ options%>}
scale=%<factor%>
plane=%<name%>
shift={%<x,y,z%>}
ball=#3d,circle,none
statecolor=#%color
statewidth=##L
axisarrow=%<arrow%>
labelmark#true,false
nested#true,false
#endkeyvals

\computeOffset{name}#*
\computeOffset[options%keyvals]{name}#*
\computeVisibility{name1}{name2}{name3}{name4}#*
\computeVisibility[options%keyvals]{name1}{name2}{name3}{name4}#*

\tmp{arg}#S
\aphi#S
\atheta#S
\dot#S
\norm#S
\xx#S
\xy#S
\yx#S
\yy#S
\xshift#S
\yshift#S
\zshift#S
\behind#S
\newphi#S
\newtheta#S
\myval#S
\tatheta#S
\domaintest#S
\domaintesttwo#S
\domaintestthree#S
\agamma#S
\aalpha#S
\aalphatest#S
\abeta#S
