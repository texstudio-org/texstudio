# curves package
# Matthew Bertucci 11/13/2021 for v1.55

#keyvals:\usepackage/curves#c
dvips
emtex
xdvi
WML
#endkeyvals

\csdiameter#*
\curvelength#*
\overhang#*

\ifcurvewarn#*
\curvewarntrue
\curvewarnfalse
\ifstraight#*
\straighttrue
\straightfalse

\curvesymbol{symbol}
\curvedashes{dash pattern}
\curvedashes[length]{dash pattern}

\diskpitchstretch#*
\patternresolution#*
\xscale#*
\xscaley#*
\yscale#*
\yscalex#*

\arc(x,y){angle}#/picture
\arc[n](x,y){angle}#/picture
\bigcircle{diameter}#/picture
\bigcircle[n]{diameter}#/picture
\closecurve(coords)#/picture
\closecurve[n](coords)#/picture
\curve(coords)#/picture
\curve[n](coords)#/picture
\scaleput(x,y){object}#/picture
\tagcurve(coords)#/picture
\tagcurve[n](coords)#/picture