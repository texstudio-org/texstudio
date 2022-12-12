# fillbetween pgfplotslibrary
# 2022/12/11 for v1.18.1

#include:pgfplotslibrarydecorations.softclip
# loads fillbetween tikzlibrary

\addplot fill between [%<fill between options%>];#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis

#keyvals:\addplot#c,\addplot+#c
name path=%<name%>
#endkeyvals

#keyvals:\path#c,\draw#c,\fill#c
intersection segments={%<options%>}
#endkeyvals

\pgfplotslibraryfillbetweenpreparecurrentlayer#S

# from fillbetween tikzlibrary
\tikzsegmentindex#*

\tikzfillbetween[options%keyvals]{draw style}#*

#keyvals:\tikzfillbetween#c
split#true,false
soft clip={%<specification%>}
soft clip first={%<specification%>}
soft clip second={%<specification%>}
every segment/.style={%<TikZ keys%>}
every odd segment/.style={%<TikZ keys%>}
every even segment/.style={%<TikZ keys%>}
every segment no %<<n>%>/.style={%<TikZ keys%>}
every last segment/.style={%<TikZ keys%>}
of=%<first%> and %<second%>
reverse=#auto,true,false
on layer=%<layer name%>
inner moveto=#connect,keep
#endkeyvals

\tikzgetnamedpath{path name}#*
\tikznamecurrentpath{name}#*

\tikzpathintersectionsegments[options%keyvals]#*

#keyvals:\tikzpathintersectionsegments#c
of=%<first%> and %<second%>
sequence={%<series spec%>}
reverse#true,false
#endkeyvals

\tikzsegmentlastindex#S