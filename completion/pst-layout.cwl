# pst-layout package
# Matthew Bertucci 2/26/2022 for v.95

#include:graphicx
#include:ifthen
#include:pstricks-add
#include:arrayjobx

\NumGraphics=%<max index%>
\NumFragments=%<max index%>
\NumLines=%<max index%>
\NumFrames=%<max index%>
\NumPoints=%<max index%>
\NumDots=%<max index%>

\Graphic(index)={filename}
\GraphicPos(index)={position}
\GraphicOpts(index)={options}
\GraphicRefPt(index)={ref pt}
\Frag(index)={text fragment}
\FragPos(index)={position}
\FragRefPt(index)={ref pt}
\FragRotation(index)={angle}
\FragBlankBG(index)={value}
\PointName(index)={name}
\PointPos(index)={position}
\PointSeries(index)={min;max}
\PointInc(index)={increment}
\DotPos(index)={position}
\DotOpts(index)={options}
\DotType(index)={type}
\FrameStart(index)={position}
\FrameEnd(index)={position}
\FrameDelta(index)={position}
\FrameOpts(index)={options}
\FrameSolid(index)={value}
\FrameType(index)={type}
\LOpts(index)={options}
\LArrow(index)={arrow spec}
\LStart(index)={position}
\LEnd(index)={position}
\LDelta(index)={position}
\LType(index)={type}

\begin{pslayout}#\pictureHighlight
\end{pslayout}
\begin{pslayout*}#\pictureHighlight
\end{pslayout*}
\pslayout#S
\pslayout*#S
\endpslayout#S

\showRC

\xmin#S
\ymin#S
\parsedelta#S
\MaxR#S
\MaxC#S
\parseFragRP#S
\parseSeries#S
\PSTLayoutLoaded#S