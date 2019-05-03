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

\cite[prenote][postnote]{bibid}#c
\cite[postnote]{bibid}#c
\cite{bibid}#c
\Cite[prenote][postnote]{bibid}#c
\Cite[postnote]{bibid}#c
\Cite{bibid}#c

\parencite[prenote][postnote]{bibid}#c
\parencite[postnote]{bibid}#c
\parencite{bibid}#c
\Parencite[prenote][postnote]{bibid}#c
\Parencite[postnote]{bibid}#c
\Parencite{bibid}#c

\footcite[prenote][postnote]{bibid}#c
\footcite[postnote]{bibid}#c
\footcite{bibid}#c
\Footcite[prenote][postnote]{bibid}#c
\Footcite[postnote]{bibid}#c
\Footcite{bibid}#c

\textcite[prenote][postnote]{bibid}#c
\textcite[postnote]{bibid}#c
\textcite{bibid}#c
\Textcite[prenote][postnote]{bibid}#c
\Textcite[postnote]{bibid}#c
\Textcite{bibid}#c

\cite*[prenote][postnote]{bibid}#c
\cite*[postnote]{bibid}#c
\cite*{bibid}#c

\parencite*[prenote][postnote]{bibid}#c
\parencite*[postnote]{bibid}#c
\parencite*{bibid}#c

\supercite{bibid}#c

\cites{bibid}{bibid}#c
\cites(post){bibid}{bibid}#c
\cites(pre)(post){bibid}{bibid}#c
\cites(pre)(post)[post]{bibid}[post]{bibid}#c
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\cites[post]{bibid}[post]{bibid}#c
\cites[pre][post]{bibid}[pre][post]{bibid}#c
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\Cites{bibid}{bibid}#c
\Cites(post){bibid}{bibid}#c
\Cites(pre)(post){bibid}{bibid}#c
\Cites(pre)(post)[post]{bibid}[post]{bibid}#c
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\Cites[post]{bibid}[post]{bibid}#c
\Cites[pre][post]{bibid}[pre][post]{bibid}#c
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\parencites{bibid}{bibid}#c
\parencites(post){bibid}{bibid}#c
\parencites(pre)(post){bibid}{bibid}#c
\parencites(pre)(post)[post]{bibid}[post]{bibid}#c
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\parencites[post]{bibid}[post]{bibid}#c
\parencites[pre][post]{bibid}[pre][post]{bibid}#c
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\Parencites{bibid}{bibid}#c
\Parencites(post){bibid}{bibid}#c
\Parencites(pre)(post){bibid}{bibid}#c
\Parencites(pre)(post)[post]{bibid}[post]{bibid}#c
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\Parencites[post]{bibid}[post]{bibid}#c
\Parencites[pre][post]{bibid}[pre][post]{bibid}#c
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\textcites{bibid}{bibid}#c
\textcites(post){bibid}{bibid}#c
\textcites(pre)(post){bibid}{bibid}#c
\textcites(pre)(post)[post]{bibid}[post]{bibid}#c
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\textcites[post]{bibid}[post]{bibid}#c
\textcites[pre][post]{bibid}[pre][post]{bibid}#c
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\Textcites{bibid}{bibid}#c
\Textcites(post){bibid}{bibid}#c
\Textcites(pre)(post){bibid}{bibid}#c
\Textcites(pre)(post)[post]{bibid}[post]{bibid}#c
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\Textcites[post]{bibid}[post]{bibid}#c
\Textcites[pre][post]{bibid}[pre][post]{bibid}#c
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\footcites{bibid}{bibid}#c
\footcites(post){bibid}{bibid}#c
\footcites(pre)(post){bibid}{bibid}#c
\footcites(pre)(post)[post]{bibid}[post]{bibid}#c
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\footcites[post]{bibid}[post]{bibid}#c
\footcites[pre][post]{bibid}[pre][post]{bibid}#c
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\Footcites{bibid}{bibid}#c
\Footcites(post){bibid}{bibid}#c
\Footcites(pre)(post){bibid}{bibid}#c
\Footcites(pre)(post)[post]{bibid}[post]{bibid}#c
\Footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\Footcites[post]{bibid}[post]{bibid}#c
\Footcites[pre][post]{bibid}[pre][post]{bibid}#c
\Footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\supercites{bibid}{bibid}#c
\supercites(post){bibid}{bibid}#c
\supercites(pre)(post){bibid}{bibid}#c
\supercites(pre)(post)[post]{bibid}[post]{bibid}#c
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\supercites[post]{bibid}[post]{bibid}#c
\supercites[pre][post]{bibid}[pre][post]{bibid}#c
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\autocite[prenote][postnote]{bibid}#c
\autocite[postnote]{bibid}#c
\autocite{bibid}#c

\Autocite[prenote][postnote]{bibid}#c
\Autocite[postnote]{bibid}#c
\Autocite{bibid}#c

\autocite*[prenote][postnote]{bibid}#c
\autocite*[postnote]{bibid}#c
\autocite*{bibid}#c

\Autocite*[prenote][postnote]{bibid}#c
\Autocite*[postnote]{bibid}#c
\Autocite*{bibid}#c

\autocites{bibid}{bibid}#c
\autocites(post){bibid}{bibid}#c
\autocites(pre)(post){bibid}{bibid}#c
\autocites(pre)(post)[post]{bibid}[post]{bibid}#c
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\autocites[post]{bibid}[post]{bibid}#c
\autocites[pre][post]{bibid}[pre][post]{bibid}#c
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\Autocites{bibid}{bibid}#c
\Autocites(post){bibid}{bibid}#c
\Autocites(pre)(post){bibid}{bibid}#c
\Autocites(pre)(post)[post]{bibid}[post]{bibid}#c
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\Autocites[post]{bibid}[post]{bibid}#c
\Autocites[pre][post]{bibid}[pre][post]{bibid}#c
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\smartcite[prenote][postnote]{bibid}#c
\smartcite[postnote]{bibid}#c
\smartcite{bibid}#c

\Smartcite[prenote][postnote]{bibid}#c
\Smartcite[postnote]{bibid}#c
\Smartcite{bibid}#c

\smartcites{bibid}{bibid}#c
\smartcites(post){bibid}{bibid}#c
\smartcites(pre)(post){bibid}{bibid}#c
\smartcites(pre)(post)[post]{bibid}[post]{bibid}#c
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\smartcites[post]{bibid}[post]{bibid}#c
\smartcites[pre][post]{bibid}[pre][post]{bibid}#c
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\Smartcites{bibid}{bibid}#c
\Smartcites(post){bibid}{bibid}#c
\Smartcites(pre)(post){bibid}{bibid}#c
\Smartcites(pre)(post)[post]{bibid}[post]{bibid}#c
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c
\Smartcites[post]{bibid}[post]{bibid}#c
\Smartcites[pre][post]{bibid}[pre][post]{bibid}#c
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#c

\svolcite{volume}{bibid}#c
\svolcite[prenote]{volume}{bibid}#c
\svolcite{volume}[page]{bibid}#c
\svolcite[prenote]{volume}[page]{bibid}#c

\Svolcite{volume}{bibid}#c
\Svolcite[prenote]{volume}{bibid}#c
\Svolcite{volume}[page]{bibid}#c
\Svolcite[prenote]{volume}[page]{bibid}#c

\tvolcite{volume}{bibid}#c
\tvolcite[prenote]{volume}{bibid}#c
\tvolcite{volume}[page]{bibid}#c
\tvolcite[prenote]{volume}[page]{bibid}#c

\Tvolcite{volume}{bibid}#c
\Tvolcite[prenote]{volume}{bibid}#c
\Tvolcite{volume}[page]{bibid}#c
\Tvolcite[prenote]{volume}[page]{bibid}#c

\avolcite{volume}{bibid}#c
\avolcite[prenote]{volume}{bibid}#c
\avolcite{volume}[page]{bibid}#c
\avolcite[prenote]{volume}[page]{bibid}#c

\Avolcite{volume}{bibid}#c
\Avolcite[prenote]{volume}{bibid}#c
\Avolcite{volume}[page]{bibid}#c
\Avolcite[prenote]{volume}[page]{bibid}#c

\notecite{volume}{bibid}#c
\notecite[prenote]{volume}{bibid}#c
\notecite{volume}[postnote]{bibid}#c
\notecite[prenote]{volume}[postnote]{bibid}#c

\Notecite{volume}{bibid}#c
\Notecite[prenote]{volume}{bibid}#c
\Notecite{volume}[postnote]{bibid}#c
\Notecite[prenote]{volume}[postnote]{bibid}#c

\pnotecite{volume}{bibid}#c
\pnotecite[prenote]{volume}{bibid}#c
\pnotecite{volume}[postnote]{bibid}#c
\pnotecite[prenote]{volume}[postnote]{bibid}#c

\Pnotecite{volume}{bibid}#c
\Pnotecite[prenote]{volume}{bibid}#c
\Pnotecite{volume}[postnote]{bibid}#c
\Pnotecite[prenote]{volume}[postnote]{bibid}#c

\fnotecite{volume}{bibid}#c
\fnotecite[prenote]{volume}{bibid}#c
\fnotecite{volume}[postnote]{bibid}#c
\fnotecite[prenote]{volume}[postnote]{bibid}#c

\citeauthor[prenote][postnote]{bibid}#c
\citeauthor[postnote]{bibid}#c
\citeauthor{bibid}#c

\citedate[prenote][postnote]{bibid}#c
\citedate[postnote]{bibid}#c
\citedate{bibid}#c

\Citeauthor[prenote][postnote]{bibid}#c
\Citeauthor[postnote]{bibid}#c
\Citeauthor{bibid}#c

\citetitle[prenote][postnote]{bibid}#c
\citetitle[postnote]{bibid}#c
\citetitle{bibid}#c

\citetitle*[prenote][postnote]{bibid}#c
\citetitle*[postnote]{bibid}#c
\citetitle*{bibid}#c

\citeyear[prenote][postnote]{bibid}#c
\citeyear[postnote]{bibid}#c
\citeyear{bibid}#c

\citeurl[prenote][postnote]{bibid}#c
\citeurl[postnote]{bibid}#c
\citeurl{bibid}#c

\nocite{bibid}#c

\fullcite[prenote][postnote]{bibid}#c
\fullcite[postnote]{bibid}#c
\fullcite{bibid}#c

\footfullcite[prenote][postnote]{bibid}#c
\footfullcite[postnote]{bibid}#c
\footfullcite{bibid}#c

\citename[prenote][postnote]{bibid}[format]{name list}
\citename[postnote]{bibid}[format]{name list}
\citename[postnote]{bibid}{name list}
\citename{bibid}[format]{name list}
\citename{bibid}{name list}#c

\citelist[prenote][postnote]{bibid}[format]{literallist}
\citelist[postnote]{bibid}[format]{literal list}
\citelist[postnote]{bibid}{literal list}
\citelist{bibid}[format]{literal list}
\citelist{bibid}{literal list}#c

\citefield[prenote][postnote]{bibid}[format]{field}
\citefield[postnote]{bibid}[format]{field}
\citefield[postnote]{bibid}{field}
\citefield{bibid}[format]{field}
\citefield{bibid}{field}#c

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
\NewBibliographyString{bibid}#c

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