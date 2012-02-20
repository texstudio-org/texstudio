# biblatex package, available from ctan
# commands for biblatex users
# tbraun, 19.08.2009
# dbitouze, 14.02.2012

\ExecuteBibliographyOptions{key=value, ...}

\bibliography{bib ﬁles}

\addbibresource{bibliographic resource}
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
\begin{refsection}[bib ﬁles]
\end{refsection}
\newrefsection[bib ﬁles]
\begin{refsegment}
\end{refsegment}
\newrefsegment
\DeclareBibliographyCategory{category}
\addtocategory{category}{bibid}
\defbibheading{name}{code}
\defbibnote{name}{text}
\defbibfilter{name}{code}
\segment{integer}
\type{type}
\keyword{keyword}
\category{category}

\cite[prenote][postnote]{bibid}
\cite[postnote]{bibid}
\cite{bibid}
\Cite[prenote][postnote]{bibid}
\Cite[postnote]{bibid}
\Cite{bibid}

\parencite[prenote][postnote]{bibid}
\parencite[postnote]{bibid}
\parencite{bibid}
\Parencite[prenote][postnote]{bibid}
\Parencite[postnote]{bibid}
\Parencite{bibid}

\footcite[prenote][postnote]{bibid}
\footcite[postnote]{bibid}
\footcite{bibid}
\Footcite[prenote][postnote]{bibid}
\Footcite[postnote]{bibid}
\Footcite{bibid}

\textcite[prenote][postnote]{bibid}
\textcite[postnote]{bibid}
\textcite{bibid}
\Textcite[prenote][postnote]{bibid}
\Textcite[postnote]{bibid}
\Textcite{bibid}

\cite*[prenote][postnote]{bibid}
\cite*[postnote]{bibid}
\cite*{bibid}

\parencite*[prenote][postnote]{bibid}
\parencite*[postnote]{bibid}
\parencite*{bibid}

\supercite{bibid}

\cites{bibid}{bibid}
\cites(post){bibid}{bibid}
\cites(pre)(post){bibid}{bibid}
\cites(pre)(post)[post]{bibid}[post]{bibid}
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\cites[post]{bibid}[post]{bibid}
\cites[pre][post]{bibid}[pre][post]{bibid}
\cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\Cites{bibid}{bibid}
\Cites(post){bibid}{bibid}
\Cites(pre)(post){bibid}{bibid}
\Cites(pre)(post)[post]{bibid}[post]{bibid}
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\Cites[post]{bibid}[post]{bibid}
\Cites[pre][post]{bibid}[pre][post]{bibid}
\Cites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\parencites{bibid}{bibid}
\parencites(post){bibid}{bibid}
\parencites(pre)(post){bibid}{bibid}
\parencites(pre)(post)[post]{bibid}[post]{bibid}
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\parencites[post]{bibid}[post]{bibid}
\parencites[pre][post]{bibid}[pre][post]{bibid}
\parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\Parencites{bibid}{bibid}
\Parencites(post){bibid}{bibid}
\Parencites(pre)(post){bibid}{bibid}
\Parencites(pre)(post)[post]{bibid}[post]{bibid}
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\Parencites[post]{bibid}[post]{bibid}
\Parencites[pre][post]{bibid}[pre][post]{bibid}
\Parencites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\textcites{bibid}{bibid}
\textcites(post){bibid}{bibid}
\textcites(pre)(post){bibid}{bibid}
\textcites(pre)(post)[post]{bibid}[post]{bibid}
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\textcites[post]{bibid}[post]{bibid}
\textcites[pre][post]{bibid}[pre][post]{bibid}
\textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\Textcites{bibid}{bibid}
\Textcites(post){bibid}{bibid}
\Textcites(pre)(post){bibid}{bibid}
\Textcites(pre)(post)[post]{bibid}[post]{bibid}
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\Textcites[post]{bibid}[post]{bibid}
\Textcites[pre][post]{bibid}[pre][post]{bibid}
\Textcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\footcites{bibid}{bibid}
\footcites(post){bibid}{bibid}
\footcites(pre)(post){bibid}{bibid}
\footcites(pre)(post)[post]{bibid}[post]{bibid}
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\footcites[post]{bibid}[post]{bibid}
\footcites[pre][post]{bibid}[pre][post]{bibid}
\footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\Footcites{bibid}{bibid}
\Footcites(post){bibid}{bibid}
\Footcites(pre)(post){bibid}{bibid}
\Footcites(pre)(post)[post]{bibid}[post]{bibid}
\Footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\Footcites[post]{bibid}[post]{bibid}
\Footcites[pre][post]{bibid}[pre][post]{bibid}
\Footcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\supercites{bibid}{bibid}
\supercites(post){bibid}{bibid}
\supercites(pre)(post){bibid}{bibid}
\supercites(pre)(post)[post]{bibid}[post]{bibid}
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\supercites[post]{bibid}[post]{bibid}
\supercites[pre][post]{bibid}[pre][post]{bibid}
\supercites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\autocite[prenote][postnote]{bibid}
\autocite[postnote]{bibid}
\autocite{bibid}

\Autocite[prenote][postnote]{bibid}
\Autocite[postnote]{bibid}
\Autocite{bibid}

\autocite*[prenote][postnote]{bibid}
\autocite*[postnote]{bibid}
\autocite*{bibid}

\Autocite*[prenote][postnote]{bibid}
\Autocite*[postnote]{bibid}
\Autocite*{bibid}

\autocites{bibid}{bibid}
\autocites(post){bibid}{bibid}
\autocites(pre)(post){bibid}{bibid}
\autocites(pre)(post)[post]{bibid}[post]{bibid}
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\autocites[post]{bibid}[post]{bibid}
\autocites[pre][post]{bibid}[pre][post]{bibid}
\autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\Autocites{bibid}{bibid}
\Autocites(post){bibid}{bibid}
\Autocites(pre)(post){bibid}{bibid}
\Autocites(pre)(post)[post]{bibid}[post]{bibid}
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\Autocites[post]{bibid}[post]{bibid}
\Autocites[pre][post]{bibid}[pre][post]{bibid}
\Autocites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\smartcite[prenote][postnote]{bibid}
\smartcite[postnote]{bibid}
\smartcite{bibid}

\Smartcite[prenote][postnote]{bibid}
\Smartcite[postnote]{bibid}
\Smartcite{bibid}

\smartcites{bibid}{bibid}
\smartcites(post){bibid}{bibid}
\smartcites(pre)(post){bibid}{bibid}
\smartcites(pre)(post)[post]{bibid}[post]{bibid}
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\smartcites[post]{bibid}[post]{bibid}
\smartcites[pre][post]{bibid}[pre][post]{bibid}
\smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\Smartcites{bibid}{bibid}
\Smartcites(post){bibid}{bibid}
\Smartcites(pre)(post){bibid}{bibid}
\Smartcites(pre)(post)[post]{bibid}[post]{bibid}
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}
\Smartcites[post]{bibid}[post]{bibid}
\Smartcites[pre][post]{bibid}[pre][post]{bibid}
\Smartcites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}

\svolcite{volume}{bibid}
\svolcite[prenote]{volume}{bibid}
\svolcite{volume}[page]{bibid}
\svolcite[prenote]{volume}[page]{bibid}

\Svolcite{volume}{bibid}
\Svolcite[prenote]{volume}{bibid}
\Svolcite{volume}[page]{bibid}
\Svolcite[prenote]{volume}[page]{bibid}

\tvolcite{volume}{bibid}
\tvolcite[prenote]{volume}{bibid}
\tvolcite{volume}[page]{bibid}
\tvolcite[prenote]{volume}[page]{bibid}

\Tvolcite{volume}{bibid}
\Tvolcite[prenote]{volume}{bibid}
\Tvolcite{volume}[page]{bibid}
\Tvolcite[prenote]{volume}[page]{bibid}

\avolcite{volume}{bibid}
\avolcite[prenote]{volume}{bibid}
\avolcite{volume}[page]{bibid}
\avolcite[prenote]{volume}[page]{bibid}

\Avolcite{volume}{bibid}
\Avolcite[prenote]{volume}{bibid}
\Avolcite{volume}[page]{bibid}
\Avolcite[prenote]{volume}[page]{bibid}

\notecite{volume}{bibid}
\notecite[prenote]{volume}{bibid}
\notecite{volume}[postnote]{bibid}
\notecite[prenote]{volume}[postnote]{bibid}

\Notecite{volume}{bibid}
\Notecite[prenote]{volume}{bibid}
\Notecite{volume}[postnote]{bibid}
\Notecite[prenote]{volume}[postnote]{bibid}

\pnotecite{volume}{bibid}
\pnotecite[prenote]{volume}{bibid}
\pnotecite{volume}[postnote]{bibid}
\pnotecite[prenote]{volume}[postnote]{bibid}

\Pnotecite{volume}{bibid}
\Pnotecite[prenote]{volume}{bibid}
\Pnotecite{volume}[postnote]{bibid}
\Pnotecite[prenote]{volume}[postnote]{bibid}

\fnotecite{volume}{bibid}
\fnotecite[prenote]{volume}{bibid}
\fnotecite{volume}[postnote]{bibid}
\fnotecite[prenote]{volume}[postnote]{bibid}

\citeauthor[prenote][postnote]{bibid}
\citeauthor[postnote]{bibid}
\citeauthor{bibid}

\citedate[prenote][postnote]{bibid}
\citedate[postnote]{bibid}
\citedate{bibid}

\Citeauthor[prenote][postnote]{bibid}
\Citeauthor[postnote]{bibid}
\Citeauthor{bibid}

\citetitle[prenote][postnote]{bibid}
\citetitle[postnote]{bibid}
\citetitle{bibid}

\citetitle*[prenote][postnote]{bibid}
\citetitle*[postnote]{bibid}
\citetitle*{bibid}

\citeyear[prenote][postnote]{bibid}
\citeyear[postnote]{bibid}
\citeyear{bibid}

\citeurl[prenote][postnote]{bibid}
\citeurl[postnote]{bibid}
\citeurl{bibid}

\nocite{bibid}

\fullcite[prenote][postnote]{bibid}
\fullcite[postnote]{bibid}
\fullcite{bibid}

\footfullcite[prenote][postnote]{bibid}
\footfullcite[postnote]{bibid}
\footfullcite{bibid}

\citename[prenote][postnote]{bibid}[format]{name list}
\citename[postnote]{bibid}[format]{name list}
\citename[postnote]{bibid}{name list}
\citename{bibid}[format]{name list}
\citename{bibid}{name list}

\citelist[prenote][postnote]{bibid}[format]{literallist}
\citelist[postnote]{bibid}[format]{literal list}
\citelist[postnote]{bibid}{literal list}
\citelist{bibid}[format]{literal list}
\citelist{bibid}{literal list}

\citefield[prenote][postnote]{bibid}[format]{field}
\citefield[postnote]{bibid}[format]{field}
\citefield[postnote]{bibid}{field}
\citefield{bibid}[format]{field}
\citefield{bibid}{field}

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

\DefineBibliographyStrings{language}{deﬁnitions}
\DefineBibliographyExtras{language}{code}
\UndefineBibliographyExtras{language}{code}
\DefineHyphenationExceptions{language}{text}
\NewBibliographyString{bibid}

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

# spanish
smartand # counter
\forceE
\forceY

# koma-script classes
\ifkomabibtotoc{true}{false}
\ifkomabibtotocnumbered{true}{false}

# memoir class
\ifmemoirbibintoc{true}{false}

