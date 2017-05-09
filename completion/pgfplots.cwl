# mode: pgfplots.sty
# denisbitouze, 26.03.2017
\begin{tikzpicture}% function%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% table%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% coordinates%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot coordinates {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% file%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot file {%<file%>};%\\end{axis}%\\end{tikzpicture}#*n
\begin{tikzpicture}% gnuplot%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}%\\end{tikzpicture}#*n
\end{tikzpicture}#n
\begin{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% function%\\addplot {%|};%\\end{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% table%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% coordinates%\\addplot coordinates {%|};%\\end{axis}#n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% file%\\addplot file {%<file%>};%\\end{axis}#*n
\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]% gnuplot%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}#*n
\end{axis}#n
\begin{semilogxaxis}#n\axis
\end{semilogxaxis}#n
\begin{semilogyaxis}#n\axis
\end{semilogyaxis}#n
\begin{loglogaxis}#n\axis
\end{loglogaxis}#n
\addplot#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot {%|};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot coordinates {%|};#/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot gnuplot {%<gnuplot code%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot file {%<file%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis
\legend#/axis,semilogxaxis,semilogyaxis,loglogaxis
\pgfplotsset{%<settings%>}
\pgfplotsset{compat=%<version number%>,%<other settings%>}
