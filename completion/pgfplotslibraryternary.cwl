# ternary pgfplotslibrary
# 2022/12/12 for v1.18.1

\begin{ternaryaxis}#/tikzpicture
\begin{ternaryaxis}[options%keyvals]#/tikzpicture
\end{ternaryaxis}

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{ternaryaxis}#c
ternary limits relative#true,false
every ternary axis/.style={%<TikZ keys%>}
tieline
tieline={%<options%>}
#endkeyvals

\pgfplotsplothandlertieline#S