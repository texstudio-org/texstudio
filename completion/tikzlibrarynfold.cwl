# nfold tikzlibrary
# Matthew Bertucci 2023/03/27 for v0.0.1

#include:tikzlibrarydecorations
# loads bezieroffset pgflibrary

#keyvals:\draw#c,\ar#c
nfold
nfold=%<integer%>
#endkeyvals

\ifpgfsegmentvisible{arg}#*

# from bezieroffset pgflibrary
\pgfstorepoint{cmd}#*d
\pgfglobalstorepoint{cmd}#*d
\pgfcrossproduct{point1}{point2}#*
\pgfdotproduct{point1}{point2}#*
\pgfcrossdot{point1}{point2}#*
\pgfoffsetcurve{point1}{point2}{point3}{point4}{distance}#*
\pgfoffsetcurvenomove{point1}{point2}{point3}{point4}{distance}#*
\pgfoffsetcurvecallback{point1}{point2}{point3}{point4}{distance}{num}#*
\pgfoffsetline{point1}{point2}{distance}#*
\pgfoffsetlinenomove{point1}{point2}{distance}#*