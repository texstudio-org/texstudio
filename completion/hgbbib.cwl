# hgbbib package
# Matthew Bertucci 2023/02/13

#include:xifthen
#include:biblatex
#include:csquotes

#keyvals:\usepackage/hgbbib#c
apa
#endkeyvals

#ifOption:apa
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
\nptextcites(post){bibid}{bibid}#*C
\nptextcites(pre)(post){bibid}{bibid}#*C
\nptextcites(pre)(post)[post]{bibid}[post]{bibid}#*C
\nptextcites[post]{bibid}[post]{bibid}#*C
\nptextcites[pre][post]{bibid}[pre][post]{bibid}#*C
\nptextcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#*C
#endif

\AddBibFile{bib file}#*
\MakeBibliography
\MakeBibliography[nosplit]%|
\begin{bibhyphenation}#*
\end{bibhyphenation}#*
\mcite{bibid}{bibid}#C
\mcite(post){bibid}{bibid}#*C
\mcite(pre)(post){bibid}{bibid}#C
\mcite(pre)(post)[post]{bibid}[post]{bibid}#*C
\mcite[post]{bibid}[post]{bibid}#*C
\mcite[pre][post]{bibid}[pre][post]{bibid}#*C
\mcite(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

# deprecated
\citenobr{bibid}#SC
\citenobr[postnote]{bibid}#SC
\citenobr[prenote][postnote]{bibid}#SC
