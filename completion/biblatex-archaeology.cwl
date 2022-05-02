# biblatex-archaeology package
# Matthew Bertucci 2022/05/01 for v2.2

#include:xpatch
#include:xstring
#include:array
#include:calc
#include:tabulary

#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
capitalizeprefixinbiblist#true,false
citeshortin#true,false
editionsuperscript=#none,predate,postdate,prelabel,postlabel,preloc,postloc,posttitle
giveninitligatures={%<lig1,lig2,...%>}
idemincitation#true,false
injournal#true,false
journallocation#true,false
maxbooknames=%<integer%>
minbooknames=%<integer%>
minrealdatediff=%<integer%>
maxreviewnames=%<integer%>
minreviewnames=%<integer%>
noseries#true,false
nothesistitlepunct#true,false
notitlepunct#true,false
origfields#true,false
pagesfirst#true,false
positionlabeldate=#both,label,location
preservelastauthor#true,false
repeatlabel=#dashed,false,true
reviewedauthoraftertitle#true,false
seriesorlocation#true,false
shortform=#false,title,true
shortjournal#true,false
shortseries#true,false
subseries#true,false
summarytitle#true,false
tabbedlabeldate#true,false
titlebrackets#true,false
titlenote#true,false
useeventdate#true,false
useeventnumber#true,false
usefestschriftaddon#true,false
useinstitution=#aspublisher,false,locationfirst,omitlocation,omitlocationifurl,pluslocation
uselocation=#false,omitifseries,true
usemultivenue#true,false
usepublisher#true,false
usesourceeditor#true,false
useunpublishedthesis#true,false
volumeafterseries#true,false
#endkeyvals

\citeissue{bibid}#C
\citeissue[postnote]{bibid}#C
\citeissue[prenote][postnote]{bibid}#C

\fciteissue{bibid}#C
\fciteissue[postnote]{bibid}#C
\fciteissue[prenote][postnote]{bibid}#C

\pciteissue{bibid}#C
\pciteissue[postnote]{bibid}#C
\pciteissue[prenote][postnote]{bibid}#C

\citeissues{bibid}{bibid}#C
\citeissues(pre){bibid}{bibid}#*C
\citeissues(pre)(post){bibid}{bibid}#C
\citeissues(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\citeissues[pre]{bibid}[pre]{bibid}#*C
\citeissues[pre][post]{bibid}[pre][post]{bibid}#*C
\citeissues(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\fciteissues{bibid}{bibid}#C
\fciteissues(pre){bibid}{bibid}#*C
\fciteissues(pre)(post){bibid}{bibid}#C
\fciteissues(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\fciteissues[pre]{bibid}[pre]{bibid}#*C
\fciteissues[pre][post]{bibid}[pre][post]{bibid}#*C
\fciteissues(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\pciteissues{bibid}{bibid}#C
\pciteissues(pre){bibid}{bibid}#*C
\pciteissues(pre)(post){bibid}{bibid}#C
\pciteissues(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\pciteissues[pre]{bibid}[pre]{bibid}#*C
\pciteissues[pre][post]{bibid}[pre][post]{bibid}#*C
\pciteissues(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\posscite{bibid}#C
\posscite[postnote]{bibid}#C
\posscite[prenote][postnote]{bibid}#C

\Posscite{bibid}#C
\Posscite[postnote]{bibid}#C
\Posscite[prenote][postnote]{bibid}#C

\posscites{bibid}{bibid}#C
\posscites(pre){bibid}{bibid}#*C
\posscites(pre)(post){bibid}{bibid}#C
\posscites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\posscites[pre]{bibid}[pre]{bibid}#*C
\posscites[pre][post]{bibid}[pre][post]{bibid}#*C
\posscites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Posscites{bibid}{bibid}#C
\Posscites(pre){bibid}{bibid}#*C
\Posscites(pre)(post){bibid}{bibid}#C
\Posscites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Posscites[pre]{bibid}[pre]{bibid}#*C
\Posscites[pre][post]{bibid}[pre][post]{bibid}#*C
\Posscites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\shortformcite{bibid}#C
\shortformcite[postnote]{bibid}#C
\shortformcite[prenote][postnote]{bibid}#C

\shortformcites{bibid}{bibid}#C
\shortformcites(pre){bibid}{bibid}#*C
\shortformcites(pre)(post){bibid}{bibid}#C
\shortformcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\shortformcites[pre]{bibid}[pre]{bibid}#*C
\shortformcites[pre][post]{bibid}[pre][post]{bibid}#*C
\shortformcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\sfcite{bibid}#C
\sfcite[postnote]{bibid}#C
\sfcite[prenote][postnote]{bibid}#C

\sfcites{bibid}{bibid}#C
\sfcites(pre){bibid}{bibid}#*C
\sfcites(pre)(post){bibid}{bibid}#C
\sfcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\sfcites[pre]{bibid}[pre]{bibid}#*C
\sfcites[pre][post]{bibid}[pre][post]{bibid}#*C
\sfcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\reviewcite{bibid}#C
\reviewcite[postnote]{bibid}#C
\reviewcite[prenote][postnote]{bibid}#C

\previewcite{bibid}#C
\previewcite[postnote]{bibid}#C
\previewcite[prenote][postnote]{bibid}#C

\textreviewcite{bibid}#C
\textreviewcite[postnote]{bibid}#C
\textreviewcite[prenote][postnote]{bibid}#C

\Reviewcite{bibid}#C
\Reviewcite[postnote]{bibid}#C
\Reviewcite[prenote][postnote]{bibid}#C

\Previewcite{bibid}#C
\Previewcite[postnote]{bibid}#C
\Previewcite[prenote][postnote]{bibid}#C

\Textreviewcite{bibid}#C
\Textreviewcite[postnote]{bibid}#C
\Textreviewcite[prenote][postnote]{bibid}#C

\reviewcites{bibid}{bibid}#C
\reviewcites(pre){bibid}{bibid}#*C
\reviewcites(pre)(post){bibid}{bibid}#C
\reviewcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\reviewcites[pre]{bibid}[pre]{bibid}#*C
\reviewcites[pre][post]{bibid}[pre][post]{bibid}#*C
\reviewcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\previewcites{bibid}{bibid}#C
\previewcites(pre){bibid}{bibid}#*C
\previewcites(pre)(post){bibid}{bibid}#C
\previewcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\previewcites[pre]{bibid}[pre]{bibid}#*C
\previewcites[pre][post]{bibid}[pre][post]{bibid}#*C
\previewcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\textreviewcites{bibid}{bibid}#C
\textreviewcites(pre){bibid}{bibid}#*C
\textreviewcites(pre)(post){bibid}{bibid}#C
\textreviewcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\textreviewcites[pre]{bibid}[pre]{bibid}#*C
\textreviewcites[pre][post]{bibid}[pre][post]{bibid}#*C
\textreviewcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Reviewcites{bibid}{bibid}#C
\Reviewcites(pre){bibid}{bibid}#*C
\Reviewcites(pre)(post){bibid}{bibid}#C
\Reviewcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Reviewcites[pre]{bibid}[pre]{bibid}#*C
\Reviewcites[pre][post]{bibid}[pre][post]{bibid}#*C
\Reviewcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Previewcites{bibid}{bibid}#C
\Previewcites(pre){bibid}{bibid}#*C
\Previewcites(pre)(post){bibid}{bibid}#C
\Previewcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Previewcites[pre]{bibid}[pre]{bibid}#*C
\Previewcites[pre][post]{bibid}[pre][post]{bibid}#*C
\Previewcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Textreviewcites{bibid}{bibid}#C
\Textreviewcites(pre){bibid}{bibid}#*C
\Textreviewcites(pre)(post){bibid}{bibid}#C
\Textreviewcites(pre)(post)[pre]{bibid}[pre]{bibid}#*C
\Textreviewcites[pre]{bibid}[pre]{bibid}#*C
\Textreviewcites[pre][post]{bibid}[pre][post]{bibid}#*C
\Textreviewcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\DefineGenitiveApostropheChars{language}{csv}
\DeclareGenitiveApostropheChars{csv}
\SuppressAdditiveLbxSuffixes{csv}

\labelnamedatewidth#*
\ifselfcontained{true}{false}#*
\mkbibletterspacing{text}#*
\textls{text}#*
\mkbibrepeatgiven{text}#*
\mkbibrepeatfamily{text}#*
\mkbibrepeatprefix{text}#*
\mkbibrepeatsuffix{text}#*
\mkbibbooknamegiven{text}#*
\mkbibbooknamefamily{text}#*
\mkbibbooknameprefix{text}#*
\mkbibbooknamesuffix{text}#*
\mkbibsourcenamegiven{text}#*
\mkbibsourcenamefamily{text}#*
\mkbibsourcenameprefix{text}#*
\mkbibsourcenamesuffix{text}#*
\mkbiblistnamegiven{text}#*
\mkbiblistnamefamily{text}#*
\mkbiblistnameprefix{text}#*
\mkbiblistnamesuffix{text}#*
\mkbibreviewnamefamily{text}#*
\mkbibreviewnamegiven{text}#*
\mkbibreviewnameprefix{text}#*
\mkbibreviewnamesuffix{text}#*
\ifshortform{name}{true}{false}#*
\nameshortformdelim#*
\ifrepeatlabel{string}{true}{false}#*
\repeatlabeldash#*
\repeatlabeldelim#*
\mkbibfestschriftnamegiven{text}#*
\mkbibfestschriftnamefamily{text}#*
\mkbibfestschriftnameprefix{text}#*
\mkbibfestschriftnamesuffix{text}#*
\multivenuedelim#*
\eventtypepunct#*
\titleseriesdelim#*
\articletitlepunct#*
\inbookbookdelim#*
\ifnothesistitlepunct{true}{false}#*
\articlesubtitlepunct#*
\ifsourceeditor{true}{false}#*
\multisourceeditordelim#*
\finalsourceeditordelim#*
\booklabelnamepunct#*
\volumedatedelim#*
\journalvolumedelim#*
\volumenumberdelim#*
\multireviewdelim#*
\finalreviewdelim#*
\multireviewnamedelim#*
\finalreviewnamedelim#*
\reviewofnamedelim#*
\ifeditionsuperscript{name}{true}{false}#*
\mkbiblocationaddon{text}#*
\finallistdelim#*
\ifuselocation{name}{true}{false}#*
\ifpagesfirst{true}{false}#*
\locationpublisherdelim#*
\iforigfields{true}{false}#*
\ifuseinstitution{name}{true}{false}#*
\institutionlocationdelim#*
\typeinstitutiondelim#*
\ifpositionlabeldate{name}{true}{false}#*
\ifnewspaper{true}{false}#*
\ifbibextrayear{true}{false}#*
\daterealdatedelim#*
\bibdatesubseqesep#*
\bibdaterangesepx{arg}#*
\ifidemincitation{true}{false}#*
\seenotedelim#*
\mkbibandothers{text}#*
\finalnameellipsis#*
\posscitealias#*
\strongcitedelim#*
\ifseenote{true}{false}#*
\iftabbedlabeldate{true}{false}#*
\begin{tabbedlabeldate}#*
\end{tabbedlabeldate}#*
\tabbedlabeldatewidth#*
\seriespunct#*
\noseriespunct#*
\seriesnumberdelim#*
\subnumberseriesdelim#*
\printgiveninitligatureslist#*
\NewValue#S