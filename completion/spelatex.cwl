# spelatex package
# Matthew Bertucci 2024/06/21 for v0.91

#include:hyperref
#include:xcolor
#include:ifthen
#include:fancyvrb
#include:newfile
#include:rotating
#include:babel
#include:kvoptions
#include:xkeyval
#include:marginnote

#keyvals:\usepackage/spelatex#c
format=%<type%>
disabled#true,false
extramath#true,false
#endkeyvals

#ifOption:extramath
\setenum{arg}#m
\setdesc{arg}#m
#endif
#ifOption:extramath=true
\setenum{arg}#m
\setdesc{arg}#m
#endif

\spelitem{text}
\spelitem[label%text]{text}
\begin{spelchunk}
\begin{spelchunk}[options%keyvals]
\end{spelchunk}
\begin{spelchunkad}
\end{spelchunkad}
\spelmacpp{csname}{action}
\spelmacpp{csname}[args]{action}
\spelmacpp{csname}[args][default]{action}
\spelenvpp{envname}{action}
\spelenvpp{envname}[args]{action}
\spelenvpp{envname}[args][default]{action}
\spelmacad{csname}{text}
\spelmacad{csname}[args]{text}
\spelmacad{csname}[args][default]{text}
\spelenvad{envname}{begin text%text}{end text%text}
\spelenvad{envname}[args]{begin text%text}{end text%text}
\spelenvad{envname}[args][default]{begin text%text}{end text%text}

#keyvals:\begin{spelchunk}
arealink
#endkeyvals

\spelatex#*
\spelbox#*
\spelpl#*
\audiodir#*
\chunkdir#*