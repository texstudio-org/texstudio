# smithchart pgfplotslibrary
# 2022/12/12 for v1.18.1

\begin{smithchart}#/tikzpicture
\begin{smithchart}[options%keyvals]#/tikzpicture
\end{smithchart}

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{smithchart}#c
few smithchart ticks/.style={%<TikZ keys%>}
many smithchart ticks/.style={%<TikZ keys%>}
many smithchart ticks*/.style={%<TikZ keys%>}
dense smithchart ticks/.style={%<TikZ keys%>}
is smithchart cs#true,false
show origin#true,false
show origin code/.code={%<code%>}
yticklabel in circle/.style={%<TikZ keys%>}
yticklabel around circle/.style={%<TikZ keys%>}
yticklabel around circle*/.style={%<TikZ keys%>}
every smithchart axis/.style={%<TikZ keys%>}
xgrid each nth passes y={%<list of stop entries%>}
ygrid each nth passes x={%<list of stop entries%>}
xgrid each nth passes y start=%<integer%>
ygrid each nth passes x start=%<integer%>
xgrid stop at y={%<list of stop entries%>}
ygrid stop at x={%<list of stop entries%>}
#endkeyvals

# not documented
\ifpgfplotspointisinsmithchartCS#S
\pgfplotspointisinsmithchartCStrue#S
\pgfplotspointisinsmithchartCSfalse#S
\pgfplotscoordmathcomplexdivision{Re1}{Im1}{Re2}{Im2}#S
\pgfmathresultim#S
\smithchart#S
\endsmithchart#S
\smithchartaxis#S
\endsmithchartaxis#S