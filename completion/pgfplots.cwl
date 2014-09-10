# mode: pgfplots.sty
# denisbitouze, 25.10.2013
\begin{tikzpicture}% table%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% coordinates%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot coordinates {%|};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% file%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot file {%<file%>};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot {%|};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% gnuplot%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot gnuplot {%<gnuplot code%>};%n\end{axis}%n\end{tikzpicture}#n
\end{tikzpicture}#n
\begin{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot {%|};%n\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% gnuplot%n\addplot gnuplot {%<gnuplot code%>};%n\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% coordinates%n\addplot coordinates {%|};%n\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% file%n\addplot file {%<file%>};%n\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% table%n\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%n\end{axis}#
\end{axis}
\begin{semilogxaxis}#n\axis
\end{semilogxaxis}
\begin{semilogyaxis}#n\axis
\end{semilogyaxis}
\begin{loglogaxis}#n\axis
\end{loglogaxis}
\addplot#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot {%|};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot gnuplot {%<gnuplot code%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot coordinates {%|};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot file {%<file%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\legend#/axis,semilogxaxis,semilogyaxis,loglogaxis
\pgfplotsset{%<settings%>}
\pgfplotsset{compat=%<version number%>,%<other settings%>}
