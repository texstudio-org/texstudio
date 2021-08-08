# biblatex package, available from ctan
# commands for biblatex users
# tbraun, 19.08.2009
# dbitouze, 14.02.2012

\ExecuteBibliographyOptions{key=value, ...}

\bibliography{bib files}

\addbibresource{bibliographic resource}#b
\addbibresource[options]{bibliographic resource}
\addglobalbib{resource}
\addglobalbib[options]{resource}
\addsectionbib{resource}
\addsectionbib[options]{resource}

\printbibliography
\printbibliography[key=value, ...]
\bibbysection
\bibbysection[key=value, ...]
\bibbysegment
\bibbysegment[key=value, ...]
\bibbycategory
\bibbycategory[key=value, ...]
\printshorthands
\printshorthands[key=value, ...]
\begin{refsection}
\begin{refsection}[bib files]
\end{refsection}
\newrefsection[bib files]
\begin{refsegment}
\end{refsegment}
\newrefsegment
\DeclareBibliographyCategory{category}
\addtocategory{category}{bibid}
\defbibenvironment{name}{begincode%text}{endcode%text}{itemcode%text}
\defbibheading{name}[title%text]{code}
\defbibheading{name}{code}
\defbibnote{name}{text}
\defbibfilter{name}{code}
\segment{integer}
\type{type}
\keyword{keyword}
\category{category}

\cite[prenote][postnote]{bibid}#C
\cite[postnote]{bibid}#C
\cite{bibid}#C
\Cite[prenote][postnote]{bibid}#C
\Cite[postnote]{bibid}#C
\Cite{bibid}#C

\parencite[prenote][postnote]{bibid}#C
\parencite[postnote]{bibid}#C
\parencite{bibid}#C
\Parencite[prenote][postnote]{bibid}#C
\Parencite[postnote]{bibid}#C
\Parencite{bibid}#C

\footcite[prenote][postnote]{bibid}#C
\footcite[postnote]{bibid}#C
\footcite{bibid}#C
\Footcite[prenote][postnote]{bibid}#C
\Footcite[postnote]{bibid}#C
\Footcite{bibid}#C

\textcite[prenote][postnote]{bibid}#C
\textcite[postnote]{bibid}#C
\textcite{bibid}#C
\Textcite[prenote][postnote]{bibid}#C
\Textcite[postnote]{bibid}#C
\Textcite{bibid}#C

\cite*[prenote][postnote]{bibid}#C
\cite*[postnote]{bibid}#C
\cite*{bibid}#C

\parencite*[prenote][postnote]{bibid}#C
\parencite*[postnote]{bibid}#C
\parencite*{bibid}#C

\supercite{bibid}#C

\cites{bibid}{bibid}#C
\cites(post){bibid}{bibid}#C
\cites(pre)(post){bibid}{bibid}#C
\cites(pre)(post)[post]{bibid}[post]{bibid}#C
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\cites[post]{bibid}[post]{bibid}#C
\cites[pre][post]{bibid}[pre][post]{bibid}#C
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Cites{bibid}{bibid}#C
\Cites(post){bibid}{bibid}#C
\Cites(pre)(post){bibid}{bibid}#C
\Cites(pre)(post)[post]{bibid}[post]{bibid}#C
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\Cites[post]{bibid}[post]{bibid}#C
\Cites[pre][post]{bibid}[pre][post]{bibid}#C
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\parencites{bibid}{bibid}#C
\parencites(post){bibid}{bibid}#C
\parencites(pre)(post){bibid}{bibid}#C
\parencites(pre)(post)[post]{bibid}[post]{bibid}#C
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\parencites[post]{bibid}[post]{bibid}#C
\parencites[pre][post]{bibid}[pre][post]{bibid}#C
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Parencites{bibid}{bibid}#C
\Parencites(post){bibid}{bibid}#C
\Parencites(pre)(post){bibid}{bibid}#C
\Parencites(pre)(post)[post]{bibid}[post]{bibid}#C
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\Parencites[post]{bibid}[post]{bibid}#C
\Parencites[pre][post]{bibid}[pre][post]{bibid}#C
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\textcites{bibid}{bibid}#C
\textcites(post){bibid}{bibid}#C
\textcites(pre)(post){bibid}{bibid}#C
\textcites(pre)(post)[post]{bibid}[post]{bibid}#C
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\textcites[post]{bibid}[post]{bibid}#C
\textcites[pre][post]{bibid}[pre][post]{bibid}#C
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Textcites{bibid}{bibid}#C
\Textcites(post){bibid}{bibid}#C
\Textcites(pre)(post){bibid}{bibid}#C
\Textcites(pre)(post)[post]{bibid}[post]{bibid}#C
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\Textcites[post]{bibid}[post]{bibid}#C
\Textcites[pre][post]{bibid}[pre][post]{bibid}#C
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\footcites{bibid}{bibid}#C
\footcites(post){bibid}{bibid}#C
\footcites(pre)(post){bibid}{bibid}#C
\footcites(pre)(post)[post]{bibid}[post]{bibid}#C
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\footcites[post]{bibid}[post]{bibid}#C
\footcites[pre][post]{bibid}[pre][post]{bibid}#C
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Footcites{bibid}{bibid}#C
\Footcites(post){bibid}{bibid}#C
\Footcites(pre)(post){bibid}{bibid}#C
\Footcites(pre)(post)[post]{bibid}[post]{bibid}#C
\Footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\Footcites[post]{bibid}[post]{bibid}#C
\Footcites[pre][post]{bibid}[pre][post]{bibid}#C
\Footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\supercites{bibid}{bibid}#C
\supercites(post){bibid}{bibid}#C
\supercites(pre)(post){bibid}{bibid}#C
\supercites(pre)(post)[post]{bibid}[post]{bibid}#C
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\supercites[post]{bibid}[post]{bibid}#C
\supercites[pre][post]{bibid}[pre][post]{bibid}#C
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\autocite[prenote][postnote]{bibid}#C
\autocite[postnote]{bibid}#C
\autocite{bibid}#C

\Autocite[prenote][postnote]{bibid}#C
\Autocite[postnote]{bibid}#C
\Autocite{bibid}#C

\autocite*[prenote][postnote]{bibid}#C
\autocite*[postnote]{bibid}#C
\autocite*{bibid}#C

\Autocite*[prenote][postnote]{bibid}#C
\Autocite*[postnote]{bibid}#C
\Autocite*{bibid}#C

\autocites{bibid}{bibid}#C
\autocites(post){bibid}{bibid}#C
\autocites(pre)(post){bibid}{bibid}#C
\autocites(pre)(post)[post]{bibid}[post]{bibid}#C
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\autocites[post]{bibid}[post]{bibid}#C
\autocites[pre][post]{bibid}[pre][post]{bibid}#C
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Autocites{bibid}{bibid}#C
\Autocites(post){bibid}{bibid}#C
\Autocites(pre)(post){bibid}{bibid}#C
\Autocites(pre)(post)[post]{bibid}[post]{bibid}#C
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\Autocites[post]{bibid}[post]{bibid}#C
\Autocites[pre][post]{bibid}[pre][post]{bibid}#C
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\smartcite[prenote][postnote]{bibid}#C
\smartcite[postnote]{bibid}#C
\smartcite{bibid}#C

\Smartcite[prenote][postnote]{bibid}#C
\Smartcite[postnote]{bibid}#C
\Smartcite{bibid}#C

\smartcites{bibid}{bibid}#C
\smartcites(post){bibid}{bibid}#C
\smartcites(pre)(post){bibid}{bibid}#C
\smartcites(pre)(post)[post]{bibid}[post]{bibid}#C
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\smartcites[post]{bibid}[post]{bibid}#C
\smartcites[pre][post]{bibid}[pre][post]{bibid}#C
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\Smartcites{bibid}{bibid}#C
\Smartcites(post){bibid}{bibid}#C
\Smartcites(pre)(post){bibid}{bibid}#C
\Smartcites(pre)(post)[post]{bibid}[post]{bibid}#C
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\Smartcites[post]{bibid}[post]{bibid}#C
\Smartcites[pre][post]{bibid}[pre][post]{bibid}#C
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C

\svolcite{volume}{bibid}#C
\svolcite[prenote]{volume}{bibid}#C
\svolcite{volume}[page]{bibid}#C
\svolcite[prenote]{volume}[page]{bibid}#C

\Svolcite{volume}{bibid}#C
\Svolcite[prenote]{volume}{bibid}#C
\Svolcite{volume}[page]{bibid}#C
\Svolcite[prenote]{volume}[page]{bibid}#C

\tvolcite{volume}{bibid}#C
\tvolcite[prenote]{volume}{bibid}#C
\tvolcite{volume}[page]{bibid}#C
\tvolcite[prenote]{volume}[page]{bibid}#C

\Tvolcite{volume}{bibid}#C
\Tvolcite[prenote]{volume}{bibid}#C
\Tvolcite{volume}[page]{bibid}#C
\Tvolcite[prenote]{volume}[page]{bibid}#C

\avolcite{volume}{bibid}#C
\avolcite[prenote]{volume}{bibid}#C
\avolcite{volume}[page]{bibid}#C
\avolcite[prenote]{volume}[page]{bibid}#C

\Avolcite{volume}{bibid}#C
\Avolcite[prenote]{volume}{bibid}#C
\Avolcite{volume}[page]{bibid}#C
\Avolcite[prenote]{volume}[page]{bibid}#C

\notecite{volume}{bibid}#C
\notecite[prenote]{volume}{bibid}#C
\notecite{volume}[postnote]{bibid}#C
\notecite[prenote]{volume}[postnote]{bibid}#C

\Notecite{volume}{bibid}#C
\Notecite[prenote]{volume}{bibid}#C
\Notecite{volume}[postnote]{bibid}#C
\Notecite[prenote]{volume}[postnote]{bibid}#C

\pnotecite{volume}{bibid}#C
\pnotecite[prenote]{volume}{bibid}#C
\pnotecite{volume}[postnote]{bibid}#C
\pnotecite[prenote]{volume}[postnote]{bibid}#C

\Pnotecite{volume}{bibid}#C
\Pnotecite[prenote]{volume}{bibid}#C
\Pnotecite{volume}[postnote]{bibid}#C
\Pnotecite[prenote]{volume}[postnote]{bibid}#C

\fnotecite{volume}{bibid}#C
\fnotecite[prenote]{volume}{bibid}#C
\fnotecite{volume}[postnote]{bibid}#C
\fnotecite[prenote]{volume}[postnote]{bibid}#C

\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C

\citedate[prenote][postnote]{bibid}#C
\citedate[postnote]{bibid}#C
\citedate{bibid}#C

\Citeauthor[prenote][postnote]{bibid}#C
\Citeauthor[postnote]{bibid}#C
\Citeauthor{bibid}#C

\citetitle[prenote][postnote]{bibid}#C
\citetitle[postnote]{bibid}#C
\citetitle{bibid}#C

\citetitle*[prenote][postnote]{bibid}#C
\citetitle*[postnote]{bibid}#C
\citetitle*{bibid}#C

\citeyear[prenote][postnote]{bibid}#C
\citeyear[postnote]{bibid}#C
\citeyear{bibid}#C

\citeurl[prenote][postnote]{bibid}#C
\citeurl[postnote]{bibid}#C
\citeurl{bibid}#C

\nocite{bibid}#C

\fullcite[prenote][postnote]{bibid}#C
\fullcite[postnote]{bibid}#C
\fullcite{bibid}#C

\footfullcite[prenote][postnote]{bibid}#C
\footfullcite[postnote]{bibid}#C
\footfullcite{bibid}#C

\citename[prenote][postnote]{bibid}[format]{name list}
\citename[postnote]{bibid}[format]{name list}
\citename[postnote]{bibid}{name list}
\citename{bibid}[format]{name list}
\citename{bibid}{name list}#C

\citelist[prenote][postnote]{bibid}[format]{literallist}
\citelist[postnote]{bibid}[format]{literal list}
\citelist[postnote]{bibid}{literal list}
\citelist{bibid}[format]{literal list}
\citelist{bibid}{literal list}#C

\citefield[prenote][postnote]{bibid}[format]{field}
\citefield[postnote]{bibid}[format]{field}
\citefield[postnote]{bibid}{field}
\citefield{bibid}[format]{field}
\citefield{bibid}{field}#C

\citereset
\citereset*
\mancite

\pno
\ppno
\nopp
\psq
\psqq
\RN{integer}
\Rn{integer}

\DefineBibliographyStrings{language}{definitions}
\DefineBibliographyExtras{language}{code}
\UndefineBibliographyExtras{language}{code}
\DefineHyphenationExceptions{language}{text}
\NewBibliographyString{bibid}#C

\bibsetup
\bibfont
\citesetup
\newblockpunct
\newunitpunct
\finentrypunct
\bibleftparen
\bibrightparen
\bibleftbracket
\bibrightbracket
\bibnamedash
\labelnamepunct
\subtitlepunct
\bibpagespunct
\multinamedelim
\finalnamedelim
\revsdnamedelim
\andothersdelim
\multilistdelim
\finallistdelim
\andmoredelim
\multicitedelim
\supercitedelim
\compcitedelim
\nameyeardelim
\labelalphaothers
\prenotedelim
\postnotedelim
\mkbibnamelast{text}
\mkbibnamefirst{text}
\mkbibnameprefix{text}
\mkbibnameaffix{text}

\bibrangedash
\bibdatelong
\bibdateshort
\biburldatelong
\biburldateshort
\finalandcomma
\mkbibordinal{integer}
\mkbibmascord{integer}
\mkbibfemord{integer}
\bibhang
\biblabelsep
\bibitemsep
\bibitemextrasep
\bibparsep
abbrvpenalty # counter
lownamepenalty
highnamepenalty

\bibellipsis
\hyphenate
\hyphen
\nbhyphen
\noligature
\mknumalph{integer}
\mkbibacro{text}
\autocap{character}

# Formatting Directives
\DeclareFieldFormat[entrytype, ...]{format}{code}#*
\DeclareFieldFormat*{format}{code}#*
\DeclareListFormat[entrytype, ...]{format}{code}#*
\DeclareListFormat*{format}{code}#*
\DeclareNameFormat[entrytype, ...]{format}{code}#*
\DeclareNameFormat*{format}{code}#*
\DeclareIndexFieldFormat[entrytype, ...]{format}{code}#*
\DeclareIndexFieldFormat*{format}{code}#*
\DeclareIndexListFormat[entrytype, ...]{format}{code}#*
\DeclareIndexListFormat*{format}{code}#*
\DeclareIndexNameFormat[entrytype, ...]{format}{code}#*
\DeclareIndexNameFormat*{format}{code}#*
\DeclareFieldAlias[entry type]{alias}[format entry type]{format}#*
\DeclareFieldAlias{alias}{format}#*
\DeclareListAlias[entry type]{alias}[format entry type]{format}#*
\DeclareListAlias{alias}{format}#*
\DeclareNameAlias[entry type]{alias}[format entry type]{format}#*
\DeclareNameAlias{alias}{format}#*
\DeclareIndexFieldAlias[entry type]{alias}[format entry type]{format}#*
\DeclareIndexFieldAlias{alias}{format}#*
\DeclareIndexListAlias[entry type]{alias}[format entry type]{format}#*
\DeclareIndexListAlias{alias}{format}#*
\DeclareIndexNameAlias[entry type]{alias}[format entry type]{format}#*
\DeclareIndexNameAlias{alias}{format}#*

\mkbibemph{text}#*
\mkbibitalic{text}#*
\mkbibbold{text}#*
\mkbibquote{text}#*
\mkbibparens{text}#*
\mkbibbrackets{text}#*
\mkbibfootnote{text}#*
\mkbibfootnotetext{text}#*
\mkbibendnote{text}#*
\mkbibendnotetext{text}#*
\mkbibsuperscript{text}#*

# Localization Strings
\bibstring{string key}#*
\biblstring{string key}#*
\bibsstring{string key}#*
\bibcpstring{string key}#*
\bibcplstring{string key}#*
\bibcpsstring{string key}#*
\bibucstring{string key}#*
\bibuclstring{string key}#*
\bibuscstring{string key}#*
\biblcstring{string key}#*
\biblclstring{string key}#*
\biblcsstring{string key}#*
\bibxstring{string key}#*
\bibxlstring{string key}#*
\bibxsstring{string key}#*
\mainlang{string key}#*

# Adding whitespace
\unspace#*
\addspace#*
\addnbspace#*
\addthinspace#*
\addnbthinspace#*
\addlowpenspace#*
\addhighpenspace#*
\addlpthinspace#*
\addhpthinspace#*
\addabbrvspace#*
\addabthinspace#*
\adddotspace#*
\addslash#*


# spanish
smartand # counter
\forceE
\forceY

# koma-script classes
\ifkomabibtotoc{true}{false}
\ifkomabibtotocnumbered{true}{false}

# memoir class
\ifmemoirbibintoc{true}{false}

#ifOption:natbib
#include:natbib
#endif
