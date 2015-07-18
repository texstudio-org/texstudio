# mode: pgfplots.sty
# denisbitouze, 25.10.2013
\begin{tikzpicture}% table%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% coordinates%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot coordinates {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% file%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot file {%<file%>};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% gnuplot%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}%\\end{tikzpicture}#n
\end{tikzpicture}#n
\begin{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot {%|};%\\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% gnuplot%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% coordinates%\\addplot coordinates {%|};%\\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% file%\\addplot file {%<file%>};%\\end{axis}#
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% table%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}#
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
