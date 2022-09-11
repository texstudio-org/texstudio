# csquotes package, available from ctan
# commands for csquotes users
# dbitouze, 14.09.2013
# Matthew Bertucci 2022/09/11 for v5.2m

#include:etoolbox
#include:keyval

\enquote{text}
\enquote*{text}

\foreignquote{language}{text}
\foreignquote*{language}{text}

\hyphenquote{language}{text}#*
\hyphenquote*{language}{text}#*

\textquote{text}
\textquote*{text}
\textquote[manual citation]{text}
\textquote*[manual citation]{text}
\textquote[manual citation][punct]{text}#*
\textquote*[manual citation][punct]{text}#*

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

\foreignblockquote{language}{text}
\foreignblockquote*{language}{text}#*
\foreignblockquote{language}[manual citation]{text}
\foreignblockquote*{language}[manual citation]{text}#*
\foreignblockquote{language}[manual citation][punct]{text}#*
\foreignblockquote*{language}[manual citation][punct]{text}#*

\hyphenblockquote{language}{text}#*
\hyphenblockquote*{language}{text}#*
\hyphenblockquote{language}[manual citation]{text}#*
\hyphenblockquote*{language}[manual citation]{text}#*
\hyphenblockquote{language}[manual citation][punct]{text}#*
\hyphenblockquote*{language}[manual citation][punct]{text}#*

\hybridblockquote{language}{text}#*
\hybridblockquote*{language}{text}#*
\hybridblockquote{language}[manual citation]{text}#*
\hybridblockquote*{language}[manual citation]{text}#*
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
\begin{displayquote}[manual citation][punct]#*
\end{displayquote}

\begin{foreigndisplayquote}{language}
\begin{foreigndisplayquote}{language}[manual citation]
\begin{foreigndisplayquote}{language}[manual citation][punct]#*
\end{foreigndisplayquote}

\begin{hyphendisplayquote}{language}
\begin{hyphendisplayquote}{language}[manual citation]
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

\textdel{text}

\DeclareQuoteStyle{style}{openoutermark}{closeoutermark}{openinnermark}{closeinnermark}#*
\DeclareQuoteStyle[variant]{style}[outerinit][innerinit]{openouter}[midouter]{closeouter}{openinner}[midinner]{closeinner}#*

\DeclareQuoteAlias{style}{alias}#*
\DeclareQuoteAlias[variant]{style}{alias}#*
\DeclareQuoteAlias{first-level alias}{second-level alias}#*

\DeclareQuoteOption{style}#*

\ExecuteQuoteOptions{options%keyvals}#*
#keyvals:\usepackage/csquotes#c,\ExecuteQuoteOptions#c
strict#true,false
style=%<style%>
autostyle=#true,false,try,once,tryonce
maxlevel=%<integer%>
autopunct#true,false
threshold=%<integer%>
thresholdtype=#lines,words
parthreshold#true,false
splitcomp#true,false
csdisplay#true,false
debug#true,false
version=%<version%>
austrian=#quotes,guillemets
croatian=#quotes,guillemets
czech=#quotes,guillemets
danish=#quotes,guillemets,topquotes
english=#american,british
estonian
french=#quotes,quotes*,guillemets,guillemets*
galician=#quotes,guillemets
german=#quotes,guillemets,swiss
hungarian
italian=#guillemets,quotes
latin=#italianguillemets,germanquotes,germanguillemets,britishquotes,americanquotes
japanese
latvian
norwegian=#guillemets,quotes
polish=#guillemets,guillemets*
portuguese=#portuguese,brazilian
romanian
serbian=#quotes,guillemets,german
slovenian=#quotes,guillemets
spanish=#spanish,mexican
swedish=#quotes,guillemets,guillemets*
turkish=#quotes,guillemets
ukrainian
#endkeyvals

\DeclarePlainStyle{openoutermark}{closeoutermark}{openinnermark}{closeinnermark}#*

\SetBlockThreshold{integer}#*
\SetBlockEnvironment{envname}#*
\SetCiteCommand{command}#*

\mkcitation{cite}#*
\mkccitation{cite code}#*
\mktextquote{open}{text}{close}{punct}{tpunct}{cite}#*
\mkblockquote{text}{punct}{tpunct}{cite}#*
\mkbegdispquote{punct}{cite}#*
\mkenddispquote{punct}{cite}#*

\ifpunctmark{character}{true}{false}#*
\ifpunct{true}{false}#*
\ifterm{true}{false}#*
\iftextpunctmark{text}{character}{true}{false}#*
\iftextpunct{text}{true}{false}#*
\iftextterm{text}{true}{false}#*
\ifblockquote{true}{false}#*
\ifblank{string}{true}{false}#*
\unspace#*

\DeclareAutoPunct{characters}#*

\mktextelp#*
\mktextelpins{text}#*
\mktextinselp{text}#*
\mktextins{text}#*
\mktextmod{text}#*
\mktextdel{text}#*

\BlockquoteDisable{code}#*

\DeclareQuoteGlyph{encoding}{position}#*

\openautoquote#*
\closeautoquote#*
\openinnerquote#*
\closeinnerquote#*

\textooquote#*
\textcoquote#*
\textmoquote#*
\textoiquote#*
\textciquote#*
\textmiquote#*

\initoquote#*
\initiquote#*

# not documented
\csqQQ{arg}#*
\csqBQbeg{arg}#*
\csqBQend{arg}#*
\csqBQsep{arg}#*
\csqBQ{arg}#*
\initfrenchquotes#*
\mkfrenchopenquote{text}#*
\mkfrenchclosequote{text}#*
\fixligatures#*
