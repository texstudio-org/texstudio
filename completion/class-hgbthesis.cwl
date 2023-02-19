# hgbthesis class
# Matthew Bertucci 2023/02/13

#include:xifthen
#include:ifpdf
#include:class-book
#include:geometry
#include:hgb
#include:hgbmath
#include:hgbalgo
#include:hgbheadings
#include:hgbabbrev
#include:hgblistings
#include:hgbbib

#keyvals:\documentclass/hgbthesis#c
bachelor
master
diploma
internship
apa
proposal
# options passed to hgb class
english
german
smartquotes
noUpdateCheck
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

\advisor{name}
\cclicense
\companyName{name}
\companyUrl{URL}#U
\dateofsubmission{YYYY}{MM}{DD}
\leadingzero{count}#*
\license{text}
\logofile{imagefile}#g
\makelogo#*
\placeofstudy{place}
\programname{name%text}
\programtype{type%text}
\strictlicense
