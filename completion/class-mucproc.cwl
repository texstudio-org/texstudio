# mucproc class
# Matthew Bertucci 4/19/2022 for v1.06

#include:scrbase
#include:class-scrartcl
#include:graphicx
#include:babel
#include:csquotes
#include:geometry
#include:biblatex
# loads bibstyle=apa option of biblatex
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:txfonts
#include:scrlayer-scrpage

#keyvals:\documentclass/mucproc#c
ngerman
english
anonymous#true,false
forcefinal#true,false
headline#true,false
copyrightinfo#true,false
pagestyle#true,false

#endkeyvals

#ifOption:ngerman
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
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
#endif

#ifOption:english
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
#endif

#ifOption:anonymous
#include:comment
#endif
#ifOption:anonymous=true
#include:comment
#endif

#ifOption:forcefinal
#include:pdfx
#endif
#ifOption:forcefinal=true
#include:pdfx
#endif

\thanks[label]{text}#l
\thanksref{label}#r
\begin{authoraddendum}{author name}
\begin{authoraddendum}[imagefile]{author name}#g
\end{authoraddendum}
\mucprocVersion#S

# from bibstyle=apa option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
apamaxprtauth=%<number%>
#endkeyvals
# from apa.bbx
\foreverunspace#*
\printtexte{text}#*
\printtexte[format]{text}#*
\maxprtauth#*
\apanum{num}#*
\mkdaterangeapalong{datetype}#*
\mkdaterangeapalongextra{datetype}#*
\begrelateddelimcommenton#*
\begrelateddelimreviewof#*
\begrelateddelimreprintfrom#*
\urldatecomma#*
# from apa.cbx
\apashortdash#*
\citeresetapa#*
\fullcitebib[prenote][postnote]{bibid}#*C
\fullcitebib[postnote]{bibid}#*C
\fullcitebib{bibid}#*C
\nptextcite[prenote][postnote]{bibid}#C
\nptextcite[postnote]{bibid}#C
\nptextcite{bibid}#C
\nptextcites{bibid}{bibid}#*C
\nptextcites(pre){bibid}{bibid}#*C
\nptextcites(pre)(post){bibid}{bibid}#*C
\nptextcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\nptextcites[pre]{bibid}[pre]{bibid}#*C
\nptextcites[pre][post]{bibid}[pre][post]{bibid}#*C
\nptextcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C

# from T1 option of fontenc option of biblatex
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



