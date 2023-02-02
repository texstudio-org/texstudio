# pst-2dplot package
# Matthew Bertucci 2022/08/06 for v1.5

#include:pstricks
#include:pst-plot
#include:multido
#include:xkeyval

\begin{pstgraph}(x0,y0)#\pictureHighlight
\begin{pstgraph}[options%keyvals](x0,y0)
\end{pstgraph}

\setpstgraph{options%keyvals}

#keyvals:\begin{pstgraph},\setpstgraph
xmin=%<number%>
xmax=%<number%>
ymin=%<number%>
ymax=%<number%>
xgriddiv=%<number%>
ygriddiv=%<number%>
gridstyle=%<style%>
gridcolor=#%color
gridwidth=##L
xticksize=%<number%>
yticksize=%<number%>
xtagsep=%<number%>
ytagsep=%<number%>
xtagformat=%<format commands%>
ytagformat=%<format commands%>
xlabel=%<text%>
ylabel=%<text%>
xlabelsep=%<number%>
ylabelsep=%<number%>
framewidth=##L
framecolor=#%color
#endkeyvals

\pstlabel{x-label}{y-label}
\pstfileplot{file}
\pstfileplot[pstricks options]{file}
