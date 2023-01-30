# abc package
# Matthew Bertucci 11/30/2021 for v2.0b

#include:ifluatex
#include:verbatim
#include:keyval
#include:graphicx
#include:ifpdf
#include:shellesc

#keyvals:\usepackage/abc#c
shellescape
noshellescape
generate
nogenerate
ps2epsi
ps2epsidos
ps2eps
nosaveall
saveall
mup
#endkeyvals

\begin{abc}
\begin{abc}[options%keyvals]
\end{abc}

\abcinput{file}
\abcinput[options%keyvals]{file}

#keyvals:\begin{abc},\abcinput,\begin{mup},\mupinput
name=%<name%>
options={%<abcm2ps options%>}
postoptions={%<abcm2ps options%>}
program=%<program%>
width=##L
center#true,false
extension=%<extension%>
#endkeyvals

\abcwidth#*
\normalabcoutputfile#*

#ifOption:mup
\normalmupoutputfile#*
\begin{mup}
\begin{mup}[options%keyvals]
\end{mup}
\mupinput{file}
\mupinput[options%keyvals]{file}
\mupwidth#*
#endif
