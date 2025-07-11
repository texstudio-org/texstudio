# ffcode package
# Matthew Bertucci 2025/07/09 for v0.11.0

#include:pgfopts
#include:xcolor
#include:listings
#include:tcolorbox
#include:fancyvrb

#keyvals:\usepackage/ffcode#c
noframes
nobars
nonumbers
nocn
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
