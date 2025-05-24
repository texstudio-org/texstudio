# scontents package
# Matthew Bertucci 2025/05/16 for v2.4

\setupsc{options%keyvals}

#keyvals:\setupsc,\usepackage/scontents#c
store-env=%<seq name%>
store-cmd=%<seq name%>
print-env#true,false
print-cmd#true,false
print-all#true,false
store-all=%<seq name%>
overwrite#true,false
width-tab=%<integer%>
force-eol#true,false
verb-font=%<font family%>
#endkeyvals

\begin{scontents}
\begin{scontents}[options%keyvals]
\end{scontents}

#keyvals:\begin{scontents}
store-env=%<seq name%>
print-env#true,false
write-env=%<file.ext%>
write-out=%<file.ext%>
overwrite#true,false
force-eol#true,false
#endkeyvals

\newenvsc{envname}#N
\newenvsc{envname}[initial keys%keyvals]#N

#keyvals:\newenvsc
store-env=%<seq name%>
print-env#true,false
#endkeyvals

\Scontents{argument}
\Scontents[options%keyvals]{argument}

#keyvals:\Scontents
store-cmd=%<seq name%>
print-cmd#true,false
#endkeyvals

\Scontents*{argument}
\Scontents*[options%keyvals]{argument}

#keyvals:\Scontents*
store-cmd=%<seq name%>
print-cmd#true,false
write-cmd=%<file.ext%>
write-out=%<file.ext%>
overwrite#true,false
force-eol#true,false
#endkeyvals

\getstored{seq name}
\getstored[index]{seq name}

\foreachsc{seq name}
\foreachsc[options%keyvals]{seq name}

#keyvals:\foreachsc
sep={%<code%>}
step=%<integer%>
start=%<integer%>
stop=%<integer%>
before={%<code%>}
after={%<code%>}
wrapper={%<code%>}
#endkeyvals

\typestored{seq name}
\typestored[options%keyvals]{seq name}
\meaningsc{seq name}
\meaningsc[options%keyvals]{seq name}

#keyvals:\typestored#c,\meaningsc#c
%<index%>
print-cmd#true,false
write-out=%<file.ext%>
overwrite#true,false
width-tab=%<integer%>
#endkeyvals

\mergesc[%<options%>]{%<{seqA}[index],{seqB}[start-stop],{seqC}[1-end]%>}

#keyvals:\mergesc
print-cmd#true,false
write-out=%<file.ext%>
overwrite#true,false
width-tab=%<integer%>
typestored
meaningsc
#endkeyvals

\begin{verbatimsc}#V
\end{verbatimsc}

\countsc{seq name}
\cleanseqsc{seq name}

\ScontentsFileDate#S
\ScontentsFileVersion#S
\ScontentsFileDescription#S
