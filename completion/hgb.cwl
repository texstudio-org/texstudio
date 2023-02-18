# hgb package
# Matthew Bertucci 2023/02/13

#include:xifthen
#include:lmodern
#include:cmap
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:babel
# loads english and ngerman options of babel
#include:xstring
#include:datetime2
# loads calc option of datetime2
#include:upquote
#include:eurosym
#include:graphicx
#include:overpic
#include:pict2e
#include:xcolor
#include:url
#include:verbatim
#include:moreverb
#include:ifpdf
#include:epstopdf
#include:breakurl
#include:hyperref
#include:hypcap
#include:float
#include:caption
#include:enumitem
#include:tocbasic
#include:pdfpages
#include:booktabs
#include:longtable
#include:multirow

#keyvals:\usepackage/hgb#c
english
german
ngerman
smartquotes
noUpdateCheck
#endkeyvals

#ifOption:smartquotes
#include:csquotes
#endif

\begin{block}
\end{block}
\begin{english}
\end{english}
\begin{FileList}{path%URL}
\end{FileList}
\begin{german}
\end{german}
\begin{NarrowList}
\end{NarrowList}
\begin{nowidows}
\end{nowidows}

\calibrationbox{width in mm}{height in mm}
\email{email%URL}#U
\fitem{path%URL}
\getcurrentlabel
\hgbAge#*
\hgbDate#*
\hgbWarnOldPackage{number}#*
\oldand#S
\PackageToDTMdate{YYYY/MM/DD}{name}#*
\ShowParameter{param}#*
\thehgbAgeLimit#*
\trennstrich#*
\widedotfill#*

# deprecated
\Messbox{arg1}{arg2}#S

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*

# from ngerman option of babel (repeats removed)
\captionsngerman
\datengerman
\extrasngerman
\noextrasngerman
\dq
\ntosstrue#*
\ntossfalse#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »

# from calc option of datetime2
#include:datetime2-calc
