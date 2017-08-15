# csquotes package, available from ctan
# commands for csquotes users
# dbitouze, 14.09.2013

\enquote{text}
\enquote*{text}

\foreignquote{language}{text}
\foreignquote*{language}{text}

\hyphenquote{language}{text}#*
\hyphenquote*{language}{text}#*

\textquote[manual citation][punct]{text}
\textquote*[manual citation][punct]{text}

\foreigntextquote{language}{text}
\foreigntextquote*{language}{text}#*
\foreigntextquote{language}[manual citation]{text}
\foreigntextquote*{language}[manual citation]{text}#*
\foreigntextquote{language}[manual citation][punct]{text}#*
\foreigntextquote*{language}[manual citation][punct]{text}#*
\foreigntextquote{language}[manual citation][punct]{text}#*
\foreigntextquote*{language}[manual citation][punct]{text}#*

\hyphentextquote{language}{text}#*
\hyphentextquote*{language}{text}#*
\hyphentextquote{language}[manual citation]{text}#*
\hyphentextquote*{language}[manual citation]{text}#*
\hyphentextquote{language}[manual citation][punct]{text}#*
\hyphentextquote*{language}[manual citation][punct]{text}#*
\hyphentextquote{language}[manual citation][punct]{text}#*
\hyphentextquote*{language}[manual citation][punct]{text}#*

\blockquote{text}
\blockquote[manual citation]{text}
\blockquote[manual citation][punct]{text}#*
\blockquote[manual citation][punct]{text}#*

\foreignblockquote{language}{text}
\foreignblockquote*{language}{text}#*
\foreignblockquote{language}[manual citation]{text}
\foreignblockquote*{language}[manual citation]{text}#*
\foreignblockquote{language}[manual citation][punct]{text}#*
\foreignblockquote*{language}[manual citation][punct]{text}#*
\foreignblockquote{language}[manual citation][punct]{text}#*
\foreignblockquote*{language}[manual citation][punct]{text}#*

\hyphenblockquote{language}{text}#*
\hyphenblockquote*{language}{text}#*
\hyphenblockquote{language}[manual citation]{text}#*
\hyphenblockquote*{language}[manual citation]{text}#*
\hyphenblockquote{language}[manual citation][punct]{text}#*
\hyphenblockquote*{language}[manual citation][punct]{text}#*
\hyphenblockquote{language}[manual citation][punct]{text}#*
\hyphenblockquote*{language}[manual citation][punct]{text}#*

\hybridblockquote{language}{text}#*
\hybridblockquote*{language}{text}#*
\hybridblockquote{language}[manual citation]{text}#*
\hybridblockquote*{language}[manual citation]{text}#*
\hybridblockquote{language}[manual citation][punct]{text}#*
\hybridblockquote*{language}[manual citation][punct]{text}#*
\hybridblockquote{language}[manual citation][punct]{text}#*
\hybridblockquote*{language}[manual citation][punct]{text}#*

\setquotestyle{style}#*
\setquotestyle[variant]{style}#*
\setquotestyle{alias}#*
\setquotestyle*#*

\MakeOuterQuote{character}#*
\MakeInnerQuote{character}#*

\MakeAutoQuote{character 1}{character 2}#*
\MakeAutoQuote*{character 1}{character 2}#*

\MakeForeignQuote{language}{character 1}{character 2}#*
\MakeForeignQuote*{language}{character 1}{character 2}#*

\MakeHyphenQuote{language}{character 1}{character 2}#*
\MakeHyphenQuote*{language}{character 1}{character 2}#*

\MakeBlockQuote{character 1}{delimiter}{character 2}#*

\MakeForeignBlockQuote{language}{character 1}{delimiter}{character 2}#*

\MakeHyphenBlockQuote{language}{character 1}{delimiter}{character 2}#*

\MakeHybridBlockQuote{language}{character 1}{delimiter}{character 2}#*

\EnableQuotes#*
\DisableQuotes#*
\VerbatimQuotes#*
\DeleteQuotes#*

\textcquote{bibid}{text}#C
\textcquote[prenote]{bibid}{text}#C
#\textcquote[][postnote]{bibid}{text}#*C
#\textcquote[prenote][postnote]{bibid}{text}#*C
#\textcquote{bibid}[punct]{text}#*C
#\textcquote[prenote]{bibid}[punct]{text}#*C
#\textcquote[][postnote]{bibid}[punct]{text}#*C
#\textcquote[prenote][postnote]{bibid}[punct]{text}#*C
\textcquote*{bibid}{text}#C
\textcquote*[prenote]{bibid}{text}#C
#\textcquote*[][postnote]{bibid}{text}#*C
#\textcquote*[prenote][postnote]{bibid}{text}#*C
#\textcquote*{bibid}[punct]{text}#*C
#\textcquote*[prenote]{bibid}[punct]{text}#*C
#\textcquote*[][postnote]{bibid}[punct]{text}#*C
#\textcquote*[prenote][postnote]{bibid}[punct]{text}#*C

\foreigntextcquote{language}{bibid}{text}#C
\foreigntextcquote{language}[prenote]{bibid}{text}#C
#\foreigntextcquote{language}[][postnote]{bibid}{text}#*C
#\foreigntextcquote{language}[prenote][postnote]{bibid}{text}#*C
#\foreigntextcquote{language}{bibid}[punct]{text}#*C
#\foreigntextcquote{language}[prenote]{bibid}[punct]{text}#*C
#\foreigntextcquote{language}[][postnote]{bibid}[punct]{text}#*C
#\foreigntextcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C
\foreigntextcquote*{language}{bibid}{text}#C
\foreigntextcquote*{language}[prenote]{bibid}{text}#C
#\foreigntextcquote*{language}[][postnote]{bibid}{text}#*C
#\foreigntextcquote*{language}[prenote][postnote]{bibid}{text}#*C
#\foreigntextcquote*{language}{bibid}[punct]{text}#*C
#\foreigntextcquote*{language}[prenote]{bibid}[punct]{text}#*C
#\foreigntextcquote*{language}[][postnote]{bibid}[punct]{text}#*C
#\foreigntextcquote*{language}[prenote][postnote]{bibid}[punct]{text}#*C

\hyphentextcquote{language}{bibid}{text}#C
\hyphentextcquote{language}[prenote]{bibid}{text}#C
#\hyphentextcquote{language}[][postnote]{bibid}{text}#*C
#\hyphentextcquote{language}[prenote][postnote]{bibid}{text}#*C
#\hyphentextcquote{language}{bibid}[punct]{text}#*C
#\hyphentextcquote{language}[prenote]{bibid}[punct]{text}#*C
#\hyphentextcquote{language}[][postnote]{bibid}[punct]{text}#*C
#\hyphentextcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C
\hyphentextcquote*{language}{bibid}{text}#C
\hyphentextcquote*{language}[prenote]{bibid}{text}#C
#\hyphentextcquote*{language}[][postnote]{bibid}{text}#*C
#\hyphentextcquote*{language}[prenote][postnote]{bibid}{text}#*C
#\hyphentextcquote*{language}{bibid}[punct]{text}#*C
#\hyphentextcquote*{language}[prenote]{bibid}[punct]{text}#*C
#\hyphentextcquote*{language}[][postnote]{bibid}[punct]{text}#*C
#\hyphentextcquote*{language}[prenote][postnote]{bibid}[punct]{text}#*C


\blockcquote{bibid}{text}#C
\blockcquote[prenote]{bibid}{text}#C
#\blockcquote[][postnote]{bibid}{text}#*C
#\blockcquote[prenote][postnote]{bibid}{text}#*C
#\blockcquote{bibid}[punct]{text}#*C
#\blockcquote[prenote]{bibid}[punct]{text}#*C
#\blockcquote[][postnote]{bibid}[punct]{text}#*C
#\blockcquote[prenote][postnote]{bibid}[punct]{text}#*C

\foreignblockcquote{language}{bibid}{text}#C
\foreignblockcquote{language}[prenote]{bibid}{text}#C
#\foreignblockcquote{language}[][postnote]{bibid}{text}#*C
#\foreignblockcquote{language}[prenote][postnote]{bibid}{text}#*C
#\foreignblockcquote{language}{bibid}[punct]{text}#*C
#\foreignblockcquote{language}[prenote]{bibid}[punct]{text}#*C
#\foreignblockcquote{language}[][postnote]{bibid}[punct]{text}#*C
#\foreignblockcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C

#\hyphenblockcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C

\hyphenblockcquote{language}{bibid}{text}#C
\hyphenblockcquote{language}[prenote]{bibid}{text}#C
#\hyphenblockcquote{language}[][postnote]{bibid}{text}#*C
#\hyphenblockcquote{language}[prenote][postnote]{bibid}{text}#*C
#\hyphenblockcquote{language}{bibid}[punct]{text}#*C
#\hyphenblockcquote{language}[prenote]{bibid}[punct]{text}#*C
#\hyphenblockcquote{language}[][postnote]{bibid}[punct]{text}#*C
#\hyphenblockcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C

#\hybridblockcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C

\hybridblockcquote{language}{bibid}{text}#C
\hybridblockcquote{language}[prenote]{bibid}{text}#C
#\hybridblockcquote{language}[][postnote]{bibid}{text}#*C
#\hybridblockcquote{language}[prenote][postnote]{bibid}{text}#*C
#\hybridblockcquote{language}{bibid}[punct]{text}#*C
#\hybridblockcquote{language}[prenote]{bibid}[punct]{text}#*C
#\hybridblockcquote{language}[][postnote]{bibid}[punct]{text}#*C
#\hybridblockcquote{language}[prenote][postnote]{bibid}[punct]{text}#*C

\begin{displayquote}
\begin{displayquote}[manual citation]
\begin{displayquote}[][punct]#*
\begin{displayquote}[manual citation][punct]#*
\end{displayquote}

\begin{foreigndisplayquote}{language}
\begin{foreigndisplayquote}{language}[manual citation]
\begin{foreigndisplayquote}{language}[][punct]#*
\begin{foreigndisplayquote}{language}[manual citation][punct]#*
\end{foreigndisplayquote}

\begin{hyphendisplayquote}{language}
\begin{hyphendisplayquote}{language}[manual citation]
\begin{hyphendisplayquote}{language}[][punct]#*
\begin{hyphendisplayquote}{language}[manual citation][punct]#*
\end{hyphendisplayquote}

\begin{displaycquote}{bibid}#C
\begin{displaycquote}[prenote]{bibid}#C
#\begin{displaycquote}[][postnote]{bibid}#*C
#\begin{displaycquote}[prenote][postnote]{bibid}#*C
#\begin{displaycquote}{bibid}[punct]#*C
#\begin{displaycquote}[prenote]{bibid}[punct]#*C
#\begin{displaycquote}[][postnote]{bibid}[punct]#*C
#\begin{displaycquote}[prenote][postnote]{bibid}[punct]#*C
\end{displaycquote}

\begin{foreigndisplaycquote}{bibid}#C
\begin{foreigndisplaycquote}[prenote]{bibid}#C
#\begin{foreigndisplaycquote}[][postnote]{bibid}#*C
#\begin{foreigndisplaycquote}[prenote][postnote]{bibid}#*C
#\begin{foreigndisplaycquote}{bibid}[punct]#*C
#\begin{foreigndisplaycquote}[prenote]{bibid}[punct]#*C
#\begin{foreigndisplaycquote}[][postnote]{bibid}[punct]#*C
#\begin{foreigndisplaycquote}[prenote][postnote]{bibid}[punct]#*C
\end{foreigndisplaycquote}

\begin{hyphendisplaycquote}{bibid}#C
\begin{hyphendisplaycquote}[prenote]{bibid}#C
#\begin{hyphendisplaycquote}[][postnote]{bibid}#*C
#\begin{hyphendisplaycquote}[prenote][postnote]{bibid}#*C
#\begin{hyphendisplaycquote}{bibid}[punct]#*C
#\begin{hyphendisplaycquote}[prenote]{bibid}[punct]#*C
#\begin{hyphendisplaycquote}[][postnote]{bibid}[punct]#*C
#\begin{hyphendisplaycquote}[prenote][postnote]{bibid}[punct]#*C
\end{hyphendisplaycquote}

\textelp{}
\textelp{text}
\textelp*{text}

\textins{text}
\textins*{text}

\SetCiteCommand{command}
