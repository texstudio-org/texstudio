# ffcode package
# Matthew Bertucci 2026/07/22 for v0.13.0

#include:pgfopts
#include:xcolor
#include:listings
#include:tcolorbox
#include:fancyvrb
#include:shellesc

#keyvals:\usepackage/ffcode#c
noframes
nobars
nonumbers
nocn
tmpfile=%<file%>
bold
sf
samepage
#endkeyvals

\ff{code%definition}
\begin{ffcode}#V
\begin{ffcode}[listings options]#V
\end{ffcode}
\ffinput{file}
\ffinput[listings options]{file}
\begin{ffsave}#V
\begin{ffsave}[file]#V
\end{ffsave}
\ffcolumnbreak