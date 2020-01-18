# mode: pgfplots.sty
# denisbitouze, 26.03.2017
# muzimuzhi, 9 Aug 2019 and 17 Dec 2019

#include:graphicx
#include:tikz

\begin{tikzpicture}% function%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% table%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% coordinates%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot coordinates {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% file%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot file {%<file%>};%\\end{axis}%\\end{tikzpicture}#*n
\begin{tikzpicture}% gnuplot%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}%\\end{tikzpicture}#*n

\begin{axis}#/tikzpicture
\begin{axis}[options%keyvals]#/tikzpicture
\end{axis}
\begin{groupplot}#/tikzpicture
\begin{groupplot}[options%keyvals]#/tikzpicture
\end{groupplot}
\begin{loglogaxis}#/tikzpicture
\begin{loglogaxis}[options%keyvals]#/tikzpicture
\end{loglogaxis}
\begin{pgfplotsinterruptdatabb}#/tikzpicture
\begin{pgfplotsinterruptdatabb}[options%keyvals]#/tikzpicture
\end{pgfplotsinterruptdatabb}
\begin{polaraxis}#/tikzpicture
\begin{polaraxis}[options%keyvals]#/tikzpicture
\end{polaraxis}
\begin{semilogxaxis}#/tikzpicture
\begin{semilogxaxis}[options%keyvals]#/tikzpicture
\end{semilogxaxis}
\begin{semilogyaxis}#/tikzpicture
\begin{semilogyaxis}[options%keyvals]#/tikzpicture
\end{semilogyaxis}
\begin{smithchart}#/tikzpicture
\begin{smithchart}[options%keyvals]#/tikzpicture
\end{smithchart}
\begin{ternaryaxis}#/tikzpicture
\begin{ternaryaxis}[options%keyvals]#/tikzpicture
\end{ternaryaxis}

\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% function%\\addplot {%|};%\\end{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% table%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% coordinates%\\addplot coordinates {%|};%\\end{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% file%\\addplot file {%<file%>};%\\end{axis}#*n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% gnuplot%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}#*n
\addplot#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot {%|};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot coordinates {%|};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot gnuplot {%<gnuplot code%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot file {%<file%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis
\legend#/axis,semilogxaxis,semilogyaxis,loglogaxis

\pgfplotsset{%<settings%>}
\pgfplotsset{compat=%<version number%>,%<other settings%>}

\usepgfplotslibrary{%<library list%>%keyvals}
#keyvals:\usepgfplotslibrary
clickable
colorbrewer
colormaps
dateplot
decorations.softclip
external
fillbetween
groupplots
patchplots
polar
smithchart
statistics
ternary
units
#endkeyvals
