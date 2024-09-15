# spelatex package
# Matthew Bertucci 2024/09/10 for v0.92

#include:hyperref
#include:xcolor
#include:ifthen
#include:verbatim
#include:fancyvrb
#include:newfile
#include:rotating
#include:babel
#include:kvoptions
#include:xkeyval

#keyvals:\usepackage/spelatex#c
format=%<type%>
server=%URL%>
markervisibility=#none,onlygroups
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
\spelpl#*
\audiodir#S
\chunkdir#S
\linksdir#S
\spelchunkatom{arg}#S
\spelchunkatom[opt]{arg}#S
\begin{spelverbatimwrite}{arg}#S
\end{spelverbatimwrite}#S
