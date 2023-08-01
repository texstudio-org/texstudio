# nfold tikzlibrary
# Matthew Bertucci 2023/07/23 for v1.0.0

# loads nfold pgflibrary, which loads offsetpath pgflibrary, which loads bezieroffset pgflibrary

#keyvals:\draw#c,\ar#c
nfold
nfold=%<integer%>
scaling nfold
scaling nfold=%<integer%>
#endkeyvals

# from offsetpath pgflibrary
\pgfoffsetpath{softpath}{length}#*
\pgfoffsetpathfraction{softpath}{width}{fraction}#*
\pgfoffsetpathqfraction{softpath}{width}{fraction}#*
\pgfoffsetpathindex{softpath}{width}{i}{n}#*

# from bezieroffset pgflibrary
\pgfmathcrossproduct{point1}{point2}#*
\pgfmathdotproduct{point1}{point2}#*
\pgfmathcrossdot{point1}{point2}#*
\pgfpointtaxicabnorm{arg}#*
\pgfoffsetcurve{point1}{point2}{point3}{point4}{distance}#*
\pgfoffsetcurvenomove{point1}{point2}{point3}{point4}{distance}#*
\pgfoffsetcurvecallback{point1}{point2}{point3}{point4}{distance}{num}#*
\pgfoffsetline{point1}{point2}{distance}#*
\pgfoffsetlinenomove{point1}{point2}{distance}#*
