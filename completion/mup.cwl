# mup package
# Matthew Bertucci 11/30/2021 for v2.0b

# this is same as loading package abc with option mup

#include:abc

#keyvals:\usepackage/mup#c
shellescape
noshellescape
generate
nogenerate
ps2epsi
ps2epsidos
ps2eps
nosaveall
saveall
#endkeyvals

\normalmupoutputfile#*
\begin{mup}
\begin{mup}[options%keyvals]
\end{mup}
\mupinput{file}
\mupinput[options%keyvals]{file}
\mupwidth#*