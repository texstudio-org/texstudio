# leadsheet class
# Matthew Bertucci 12/22/2021 for v0.5c

#include:class-scrartcl
#include:etoolbox
#include:leadsheets
#include:scrlayer-scrpage
#include:translations
#include:zref-totpages

\begin{prechorus}
\begin{prechorus}[options%keyvals]
\end{prechorus}

#keyvals:\begin{prechorus}
format={%<code%>}
label-format={%<code%>}
class={%<class name%>}
after-label={%<code%>}
name=%<name%>
template=%<template%>
numbered#true,false
named#true,false
recall-chords={%<env-class%>}
verses-format={%<code%>}
verses-label-format={%<code%>}
verses-after-label={%<code%>}
#endkeyvals

\instruction{text}
\choir{text}
\lsenparen{text}

\mkinstruction{text}#*
\mkchoir{text}#*
\mklsenparens#*
\mklsenparen{open paren}{closing paren}{text}#*