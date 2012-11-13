# mode: pgfplots.sty
# denisbitouze, 13.11.2012
\begin{tikzpicture}%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot {%|};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% gnuplot%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot gnuplot {%<gnuplot code%>};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% coordinates%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot coordinates {%|};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% file%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot file {%<file%>};%n\end{axis}%n\end{tikzpicture}#n
\begin{tikzpicture}% table%n\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%n\end{axis}%n\end{tikzpicture}#n
\end{tikzpicture}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%n\addplot {%|};%n\end{axis}#n/tikzpicture
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% gnuplot%n\addplot gnuplot {%<gnuplot code%>};%n\end{axis}#n/tikzpicture
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% coordinates%n\addplot coordinates {%|};%n\end{axis}#n/tikzpicture
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% file%n\addplot file {%<file%>};%n\end{axis}#n/tikzpicture
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% table%n\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%n\end{axis}#n/tikzpicture
\end{axis}
\begin{semilogxaxis}#n\axis
\end{semilogxaxis}
\begin{semilogyaxis}#n\axis
\end{semilogyaxis}
\begin{loglogaxis}#n\axis
\end{loglogaxis}
\addplot#n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot {%|};#n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot gnuplot {%<gnuplot code%>};#n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot coordinates {%|};#n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot file {%<file%>};#n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};#n/axis,semilogxaxis,semilogyaxis,loglogaxis
\legend#n/axis,semilogxaxis,semilogyaxis,loglogaxis