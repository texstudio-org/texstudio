# amsrefs package
# Matthew Bertucci 2022/06/23 for v2.14

#include:url
#include:pcatcode
#include:ifoption
#include:rkeyval
#include:textcmds
#include:mathscinet

#keyvals:\usepackage/amsrefs#c
alphabetic
shortalphabetic
author-year
y2k
non-compressed-cites
non-sorted-cites
abbrev
initials
short-journals
short-months
short-publishers
backrefs
bibtex-style
citation-order
lite
msc-links
nobysame
#endkeyvals

#ifOption:backrefs
#include:backref
#endif

#ifOption:msc-links
#include:hyperref
#endif

#ifOption:bibtex-style
#include:amsbst
#endif

\begin{bibchapter}
\begin{bibchapter}[heading%text]
\end{bibchapter}
\begin{bibdiv}
\begin{bibdiv}[heading%text]
\end{bibdiv}
\begin{biblist}
\begin{biblist}[before-code]
\begin{biblist}*{keyvals}
\begin{biblist}[before-code]*{keyvals}
\end{biblist}
\begin{bibsection}
\begin{bibsection}[heading%text]
\end{bibsection}

\bib{citekey}{type}{fields%keyvals}
# starred version not for citing, hence the %plain
\bib*{citekey%plain}{type}{fields%keyvals}

#keyvals:\bib,\bib*
accessdate={%<date%>}
address={%<address%>}
booktitle={%<title%>}
date={%<date%>}
edition={%<edition%>}
eprint={%<eprint info%>}
hyphenation={%<language%>}
journal={%<journal%>}
label={%<label%>}
language={%<language%>}
note={%<text%>}
number={%<issue number%>}
organization={%<organization%>}
pages={%<page range%>}
part={%<part%>}
publisher={%<publisher%>}
series={%<series%>}
status={%<text%>}
subtitle={%<subtitle%>}
title={%<title%>}
type={%<thesis type%>}
volume={%<volume number%>}
xref={%<citekey%>}
author={%<name%>}
editor={%<name%>}
translator={%<name%>}
isbn={%<isbn%>}
issn={%<issn%>}
review={%<review number%>}
book={%<keyvals%>}
conference={%<keyvals%>}
contribution={%<keyvals%>}
partial={%<keyvals%>}
reprint={%<keyvals%>}
translation={%<keyvals%>}
#endkeyvals

\bibselect{.ltb files%file}
\bibselect*{.ltb files%file}

\resetbiblist{widest label}
\bibname
\MR{number}

\cite{bibid}*{postfix%text}#c
\citelist{cite commands}
\cites{bibid}#c
\ycite{bibid}#c
\ycites{bibid}#c
\ocite{bibid}#c
\ocites{bibid}#c
\citeauthor{bibid}#c
\citeauthory{bibid}#c
\citeyear{bibid}#c
\fullcite{bibid}#c
\fullocite{bibid}#c

\DefineName{citekey%plain}{name}
\DefineJournal{citekey%plain}{issn}{shortjournal}{journal}
\DefinePublisher{citekey%plain}{shortpublisher}{publisher}{address}

\parenthesize{text}#*
\bibquotes{text}#*
\voltext#*
\issuetext#*
\editiontext#*
\DashPages{page ranges}#*
\nopunct#*
\PrintPrimary#*
\PrintAuthors{authors}#*
\PrintEditorsA{editors}#*
\PrintEditorsB{editors}#*
\PrintEditorsC{editors}#*
\PrintTranslatorsA{translators}#*
\PrintTranslatorsB{translators}#*
\PrintTranslatorsC{translators}#*
\sameauthors{name}#*
\bysame#*
\Plural{text%plain}#*
\SingularPlural{text%plain}#*
\PrintReviews{review numbers}#*
\BibField{field}#*
\IfEmptyBibField{field}{true}{false}#*
\PrintEdition{edition}#*
\CardinalNumeric{arg}#*
\PrintDate{date}#*
\PrintYear{year}#*

# not documented
\BackCite{arg}#S
\bblname#S
\BibAbbrevWarning{text}#S
\bibcite#S
\BibItem{arg1}{arg2}#S
\BibLabel#S
\biblanguagedefault#S
\biblanguageEnglish#S
\biblistfont#S
\BibSelect[bblname]{.ltb files}#S
\BibSelect{.ltb files}#S
\BibSpec{type}{specs}#S
\BibSpecAlias{arg1}{arg2}#S
\citeAltPunct#S
\citedest{arg1}#S
\citeform#S
\citeleft#S
\citemid#S
\citen{bibid}#Sc#S
\CiteNames{arg1}#S
\CiteNamesFull{arg1}#S
\CitePrintUndefined#S
\CitePrintUndefined{arg1}#S
\citepunct#S
\citeright#S
\citesel#S
\CloseBBLFile#S
\CurrentBib#S
\CurrentBibType#S
\DeclareNameAccent#S
\DeclareNameSymbol{arg1}{arg2}#S
\deferredquotes#S
\deferredquoteslogical#S
\DuplicateBibKeyWarning#S
\DuplicateBibLabelWarning#S
\EmptyNameWarning#S
\EmptyPrimaryWarning#S
\eprint{arg1}#S
\eprintpages{arg1}#S
\etalchar{arg1}#S
\etaltext#S
\InnerCite{arg1}#S
\macrotext{arg}#S
\MessageBreakNS#S
\ModifyBibLabel{arg1}#S
\MRhref{arg1}{arg2}#S
\MultipleBibSelectWarning{arg1}{arg2}#S
\MultipleCiteKeyWarning#S
\MultipleCiteKeyWarning{arg1}{arg2}#S
\NoBibDBFile{arg1}#S
\NonNumericCiteWarning#S
\ObsoleteCiteOptionWarning#S
\OpenBBLFile#S
\OtherCite{arg1}#S
\othercitelist{cite commands}#S
\othercites{bibid}#Sc
\PrintBackRefs#S
\PrintBook#S
\PrintCiteNames{arg1}#S
\PrintCNY{arg1}{arg2}#S
\PrintConference#S
\PrintConferenceDetails{arg1}#S
\PrintContributions{arg1}#S
\PrintDateB{arg1}#S
\PrintDateField{arg1}#S
\PrintDatePosted{arg1}#S
\PrintDatePV{arg1}#S
\PrintDOI{arg1}#S
\PrintISBNs{arg1}#S
\PrintNameList#S
\PrintNames#S
\PrintPartials{arg1}#S
\PrintReprint#S
\PrintSeries{arg1}{arg2}{arg3}{arg4}{arg5}#S
\PrintThesisType{arg1}#S
\PrintTranslation#S
\ReadBibData{arg1}#S
\ReadBibLoop#S
\ResetCapSFCodes#S
\SentenceSpace#S
\SubEtal{arg1}#S
\SwapBreak{arg1}#S
\thebib#S
\TrailingHyphenWarning#S
\UndefinedCiteWarning{arg1}#S
\upn{text}#S
\vdef{cmd}{def}#Sd
\XRefWarning{arg1}#S
