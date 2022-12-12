# groupplots pgfplotslibrary
# 2022/12/12 for v1.18.1

#include:tikzlibrarycalc

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c
group style={%<options%>}
group/group size=%<columns%> by %<rows%>
group/columns=%<integer%>
group/rows=%<integer%>
group/horizontal sep=##L
group/vertical sep=##L
group/every plot/.style={%<TikZ keys%>}
group/xlabels at=#all,edge top,edge bottom
group/ylabels at=#all,edge left,edge right
group/xticklabels at=#all,edge top,edge bottom
group/yticklabels at=#all,edge left,edge right
group/x descriptions at=#all,edge top,edge bottom
group/y descriptions at=#all,edge left,edge right
group/group name=%<name%>
group/empty plot/.style={%<TikZ keys%>}
#endkeyvals

\begin{groupplot}#/tikzpicture
\begin{groupplot}[options%keyvals]#/tikzpicture
\end{groupplot}

\nextgroupplot
\nextgroupplot[options%keyvals]

\groupplot#S
\endgroupplot#S