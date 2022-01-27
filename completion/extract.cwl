# extract package
# Matthew Bertucci 11/2/2021 for v1.9a

#include:verbatim
#include:xkeyval

#keyvals:\usepackage/extract#c
active#true,false
header#true,false
handles#true,false
copydocumentclass#true,false
generate=%<file%>
extract-env={%<env1,env2,...%>}
extract-cmd=%<cmd%>
extract-cmdline=%<cmd%>
line-nrs=%<number spec%>
line-labels={%<label1,label2,...%>}
extract-nrs=%<number spec%>
extract-labels={%<label1,label2,...%>}
extractskip-nrs=%<number spec%>
extractskip-labels={%<label1,label2,...%>}
#endkeyvals

\extractionlabel{name}
\begin{extract}
\begin{extract}[name]
\end{extract}
\begin{extract*}
\begin{extract*}[name]
\end{extract*}
\extractline
\extractline*
\begin{extractskip}
\begin{extractskip}[name]
\end{extractskip}
