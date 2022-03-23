# authorindex package
# Matthew Bertucci 3/22/2022 for release 2005/03/22

#keyvals:\usepackage/authorindex#c
all
avoideditors
biblabels
editors
firstabbrev
fullname
lastname
miniindex
nocompress
normal
onlyauthors
onlyfirst
pages
small
withbib
#endkeyvals

\aialso{before}{separator}
\aialsostrings#*
\aibibcite#*
\aibibindex{pages}
\aibibpage{page}
\aicite[postnote]{bibid}#C
\aicite{bibid}#C
\aiexplicit#*
\aifilename{file}#*
\aifirst{author name}
\aifirstpage{page}
\aiinbibflag#*
\aimaxauthors[trunc]{max}
\aimaxauthors{max}
\aimention{author name}
\ainame{text}
\ainamefmt{fmt spec}
\ainocite{bibid}#*C
\ainocompressflag#*
\aionly{bibid}#C
\aioptions#*
\aipages{pages}
\aipagetypeorder{order}
\airep{author name}
\aisee{string}
\aiseestring#*
\aisize#*
\aistyle#*
\aitop{author name}
\aitwostring#*
\aitwosuffix{string}
\authorindexstyle{style}
\begin{theauthorindex}
\bibindex{pages}
\bibpage#*
\citationpage#*
\end{theauthorindex}
\pagetypeorder#*
\printauthorindex
\theaipage#*