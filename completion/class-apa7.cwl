# apa7 class
# Matthew Bertucci 3/16/2022 for v2.15

#include:etoolbox
#include:lmodern
#include:fontenc
# loads T1 option of fontenc
#include:txfonts
#include:geometry
#include:graphicx
#include:scalerel
#include:tikz
#include:tikzlibrarysvg.path
#include:hyperref
#include:booktabs
#include:threeparttable
#include:caption
#include:bm
#include:fancyhdr
#include:flushend
#include:ftnright

#keyvals:\documentclass/apa7
10pt
11pt
12pt
a4paper
apacite
babel
biblatex
doc
donotrepeattitle
draftall
draftfirst
fignum
floatsintext
helv
jou
longtable
man
mask
natbib
nobf
nofontenc
nolmodern
nosf
notab
notimes
notxfonts
stu
tt
#endkeyvals

#ifOption:apacite
#include:apacite
#endif

#ifOption:babel
#include:babel
#endif

#ifOption:biblatex
#include:biblatex
#endif

#ifOption:draftall
#include:draftwatermark
#endif

#ifOption:draftfirst
#include:draftwatermark
#endif

#ifOption:floatsintext
#include:float
#endif

#ifOption:longtable
#include:array
#include:longtable
#endif

#ifOption:man
#include:endfloat
\footmark{mark}#*
#endif

#ifOption:mask
#include:substr
#endif

#ifOption:natbib
#include:apacite
#endif

#ifOption:notxfonts
#include:pslatex
#include:mathptm
#endif

#ifOption:stu
#include:endfloat
\ifnextchar#*
#endif

\shorttitle{short title%text}
\leftheader{author last names}
\journal{journal name}
\volume{volume}
\ccoppy{copyright notice%text}
\copnum{more copyright info%text}
\affiliation{affiliation}
\authorsnames{author names}
\authorsnames[superscripts]{author names}
\authorsaffiliations{affiliations}
\course{course name}
\professor{professor name}
\duedate{date}
\abstract{abstract text%text}
\keywords{keywords%text}
\authornote{text}
\addORCIDlink{author}{ORCID%URL}#U
\note{text}
\begin{seriate}
\end{seriate} 
\begin{APAenumerate}
\end{APAenumerate}
\begin{APAitemize}
\end{APAitemize}
\figurenote{text}
\tablenote
\fitfigure{EPS file}
\fitfigure[height]{EPS file}
\fitfigure{imagefile}#Sg
\fitfigure[height]{imagefile}#Sg
\fitbitmap{EPS file}
\fitbitmap[height]{EPS file}
\fitbitmap{imagefile}#Sg
\fitbitmap[height]{imagefile}#Sg
\tabfnm{id}
\tabfnt{id}{text}
\apaSevenvector{symbol%formula}
\apaSevenmatrix{symbol%formula}#*

\maskcite[prenote][postnote]{bibid}#C
\maskcite[postnote]{bibid}#C
\maskcite{bibid}#C
\maskCite[prenote][postnote]{bibid}#C
\maskCite[postnote]{bibid}#C
\maskCite{bibid}#C
\maskparencite[prenote][postnote]{bibid}#C
\maskparencite[postnote]{bibid}#C
\maskparencite{bibid}#C
\maskParencite[prenote][postnote]{bibid}#C
\maskParencite[postnote]{bibid}#C
\maskParencite{bibid}#C
\masktextcite[prenote][postnote]{bibid}#C
\masktextcite[postnote]{bibid}#C
\masktextcite{bibid}#C
\maskTextcite[prenote][postnote]{bibid}#C
\maskTextcite[postnote]{bibid}#C
\maskTextcite{bibid}#C
\maskciteauthor[prenote][postnote]{bibid}#C
\maskciteauthor[postnote]{bibid}#C
\maskciteauthor{bibid}#C
\maskCiteauthor[prenote][postnote]{bibid}#C
\maskCiteauthor[postnote]{bibid}#C
\maskCiteauthor{bibid}#C
\maskciteyear[prenote][postnote]{bibid}#C
\maskciteyear[postnote]{bibid}#C
\maskciteyear{bibid}#C
\maskfootcite[prenote][postnote]{bibid}#C
\maskfootcite[postnote]{bibid}#C
\maskfootcite{bibid}#C
\maskfootcitetext[prenote][postnote]{bibid}#C
\maskfootcitetext[postnote]{bibid}#C
\maskfootcitetext{bibid}#C
		
\acksname#*
\addperi#*
\apaSevenappeq#*
\apaSevenappfig#*
\apaSevenapptab#*
\apaSevensmash{arg}#*
\authorsep#*
\displayaffiliations#*
\displayauthors#*
\ifapamodedoc{true}{false}#*
\ifapamodejou{true}{false}#*
\ifapamodeman{true}{false}#*
\ifapamode{man}{jou}{doc}#*
\keywordname#*
\lastauthor#*
\lastauthorseparator#*
\listaffiliations#*
\listauthors#*
\listsuperscripts#*
\mspart#*
\notelabel#*
\notesname#*
\prelastauthor#*
\prelastauthorsep#*
\processfigures#*
\processtables#*
\rightheader{text}#*
\stiny{text}#*
\theAPAenum#*
\theAffiliationNumber#*
\theNumberOfAffiliations#*
\theNumberOfAuthors#*
\theNumberOfSuperscripts#*
\theappendix#*
\themaskedRefs#*
\thickline#*t
\typesectitle{title%text}#*
\uprightlowercasegreek#*

\TPToverlap#S
\bibsection#S
\dotwo{arg1}{arg2}#S
\eatarg{arg}#S
\ignore#S
\looptwo{arg1}{arg2}#S
\savefootnoterule#S
\xtwo{arg}#S

orcidlogocol#B

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
