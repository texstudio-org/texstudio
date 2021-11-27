# splitidx package
# Matthew Bertucci 11/26/2021 for v1.2c

#keyvals:\usepackage/splitidx#c
split
makeindex
useindex
allintoone
protected
idxcommands
#endkeyvals

\newindex{shortcut}
\newindex[index name]{shortcut}

\sindex{entry}
\sindex[shortcut]{entry}

#ifOption:useindex
\index[shortcut]{entry}
#endif

\AtWriteToIndex{shortcut}{code}
\AtNextWriteToIndex{shortcut}{code}

\newprotectedindex{shortcut}#*
\newprotectedindex[index name]{shortcut}#*

\printindex
\printindex[shortcut]
\printindex[shortcut][index name]
\printindex*

\printsubindex
\printsubindex*

\setindexpreamble{preamble%text}
\setindexpreamble[shortcut]{preamble%text}

\useindexpreamble
\useindexpreamble[commands]

\indexshortcut#*
\extendtheindex{before begin}{after begin}{before end}{after end}#*

\printindices#*
\see{text}{page number}#*
\seealso{text}{page number}#*
\seename#*
\alsoname#*
