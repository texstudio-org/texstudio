# fistrum package
# Matthew Bertucci 2023/02/28 for v0.1

\setfistrum{options%keyvals}

#keyvals:\usepackage/fistrum#c,\setfistrum#c
nopar#true,false
text=#fistrum-la,fistrum-es
language=%<language%>
auto-lang#true,false
default-range=%<num1-num2%>
#endkeyvals

#keyvals:\setfistrum#c
par-before=%<tokens%>
par-begin=%<tokens%>
par-sep=%<tokens%>
par-end=%<tokens%>
par-after=%<tokens%>
sentence-before=%<tokens%>
sentence-begin=%<tokens%>
sentence-sep=%<tokens%>
sentence-end=%<tokens%>
sentence-after=%<tokens%>
par-before*=%<tokens%>
par-begin*=%<tokens%>
par-sep*=%<tokens%>
par-end*=%<tokens%>
par-after*=%<tokens%>
sentence-before*=%<tokens%>
sentence-begin*=%<tokens%>
sentence-sep*=%<tokens%>
sentence-end*=%<tokens%>
sentence-after*=%<tokens%>
#endkeyvals

\fistrum
\fistrum[par range]
\fistrum[par range][sentence range]
\fistrum*
\fistrum*[par range]
\fistrum*[par range][sentence range]
\unpackfistrum
\unpackfistrum[par range]
\unpackfistrum[par range][sentence range]
\unpackfistrum*
\unpackfistrum*[par range]
\unpackfistrum*[par range][sentence range]
\fistrumexp
\SetFistrumText{name}#*
\SetFistrumDefault{range}#*
\NewFistrumPar{paragraph}#*
\SetFistrumLanguage{language}#*
\fistrumPar{num}#*
\fistrumRestoreParList#*
\fistrumRestoreSentenceList#*
\fistrumRestoreAll#*
\fistrumversion#S
\fistrumdate#S