# sr-vorl class
# Matthew Bertucci 2022/06/01 for v1.2

#include:class-scrbook
#include:xkeyval
#include:etoolbox
#include:xstring
#include:babel
#include:geometry
#include:scrlayer-scrpage
#include:caption
#include:ragged2e
#include:enumitem
#include:chngcntr
#include:varwidth
#include:onlyamsmath
#include:microtype

#keyvals:\documentclass/sr-vorl#c
no-shorthands
test
deutsch
deutsch-ar
englisch
no-microtype
non-ams
autor-in-toc
schriftgroesse=%<Wert%>
format=#a5-monografie,handbuch-monografie,a5-mehrautorenbuch,vs,autouni
#endkeyvals

#ifOption:format=autouni
#include:mathptmx
#endif

#ifOption:deutsch
# from ngerman option of babel
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

#ifOption:deutsch-ar
# from german option of babel
\captionsgerman#*
\dategerman#*
\extrasgerman#*
\noextrasgerman#*
\dq
\tosstrue#*
\tossfalse#*
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
\ck#*
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
#repl:"ck ck
#repl:"ff ff
#repl:"ll ll
#repl:"mm mm
#repl:"nn nn
#repl:"pp pp
#repl:"rr rr
#repl:"tt tt
#repl:"FF FF
#repl:"LL LL
#repl:"MM MM
#repl:"NN NN
#repl:"PP PP
#repl:"RR RR
#repl:"TT TT
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

#ifOption:englisch
# passes ngerman and british options to babel
# from ngerman option of babel
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

# from british option of babel (repeats with ngerman removed)
\captionsbritish#*
\datebritish#*
\extrasbritish#*
\noextrasbritish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
#endif

\begin{widmung}
\begin{widmung}[Überschrift%text]
\end{widmung}
\begin{zusammenfassung}
\begin{zusammenfassung}[Überschrift%text]
\end{zusammenfassung}

\AutorinTOCFormatierung#*
\chaptermituntertitel{Titel%text}{Untertitel%text}
\chaptermituntertitel[Kurztitel%text]{Titel%text}{Untertitel%text}
\chaptermituntertitel{title}{Untertitel%text}#SL1
\chaptermituntertitel[short title]{title}{Untertitel%text}#SL1
\geleitwort
\GeleitwortTitel#*
\kapitel{Titel%text}{Autor}
\kapitel[Kurztitel%text]{Titel%text}{Autor}
\kapitel{title}{Autor}#SL1
\kapitel[short title]{title}{Autor}#SL1
\KapitelAutor#*
\KapitelAutor#*
\KapitelimTOC#*
\KapitelKurztitel#*
\kapitelmituntertitel{Titel%text}{Untertitel%text}{Autor}
\kapitelmituntertitel[Kurztitel%text]{Titel%text}{Untertitel%text}{Autor}
\kapitelmituntertitel{title}{Untertitel%text}{Autor}#SL1
\kapitelmituntertitel[short title]{title}{Untertitel%text}{Autor}#SL1
\KapitelTitel#*
\KapitelUntertitel#*
\verfasser[Ortbreite,Namebreite]{Ort%text}{Name}
\verfasser{Ort%text}{Name}
\vorwort
\VorwortTitel#*

#keyvals:\pagestyle#c,\thispagestyle#c
sr-frontmatter
sr-standard
#endkeyvals

\ifMicrotype#*
\Microtypetrue#*
\Microtypefalse#*
\ifAMS#*
\AMStrue#*
\AMSfalse#*
\ifautorintoc#*
\autorintoctrue#*
\autorintocfalse#*
\ifGermanshorthands#*
\Germanshorthandstrue#*
\Germanshorthandsfalse#*
