# pdfrender package
# Matthew Bertucci 11/13/2021 for v1.6

#include:iftex
#include:infwarerr
#include:ltxcmds
#include:kvsetkeys

\pdfrender{keyvals}
\textpdfrender{keyvals}{text}

#keyvals:\pdfrender,\textpdfrender
TextRenderingMode=#0,1,2,3,4,5,6,7,Fill,Stroke,FillStroke,Invisible,FillClip,StrokeClip,FillStrokeClip,Clip
LineWidth=
LineCapStyle=#0,1,2,Butt,Round,ProjectingSquare
LineJoinStyle=#0,1,2,Miter,Round,Bevel
MiterLimit=%<number%>
Flatness=%<number%>
LineDashPattern=
RenderingIntent=#AbsoluteColorimetric,RelativeColorimetric,Saturation,Perceptual
FillColor=
StrokeColor=
#endkeyvals