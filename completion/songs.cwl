# songs package
# Matthew Bertucci 2022/09/19 for v3.1

#include:ifpdf
#include:keyval
#include:color

## Initialization and Options ##
#keyvals:\usepackage/songs#c
slides
unouter
rawtext
noshading
noindexes
nopdfindex
chorded
lyric
showmeasures
nomeasures
transposecapos
noscripture
twosongcolumns
onesongcolumn
#endkeyvals

\chordson
\chordsoff
\slides
\measureson
\measuresoff
\indexeson
\indexesoff
\scriptureon
\scriptureoff
\includeonlysongs{songlist}

## Songs ##
\begin{songs}{indexes}
\end{songs}

\beginsong{titles%text}
\beginsong{titles%text}[otherinfo%keyvals]
\endsong

#keyvals:\beginsong
by={%<authors%>}
cr={%<copyright%>}
li={%<license%>}
sr={%<refs%>}
index={%<lyrics%>}
ititle={%<title%>}
%newsongkey
#endkeyvals

\setlicense{license}

\beginverse
\beginverse*
\endverse
\beginchorus
\endchorus

\[%<chordname%>]
\[#S
\nolyrics
\DeclareLyricChar{token}
\DeclareNonLyric{token}
\DeclareNoHyphen{token}
\MultiwordChords
\shrp
\flt

\memorize
\memorize[regname]
\newchords{regname}
\replay
\replay[regname]
\repchoruses
\norepchoruses

\brk
\nextcol
\sclearpage
\scleardpage

\echo{lyrics and chords}
\rep{n}
\lrep
\rrep

\measurebar
\meter{n}{d}
\mbar{n}{d}

\textnote{text}
\musicnote{text}
\capo{n}

\ch{chord}{pre}{post}{full}
\mch{chord}{pre}{post}{full}

## Guitar Tablatures ##
\gtab{chord}{fret:strings:fingering}
\minfrets=%<n%>

## Automatic Transposition ##
\transpose{n}
\preferflats
\prefersharps
\trchordformat{chordname}{transposed-chordname}#*
\solfedge
\alphascale
\notenames{nameA}{nameB}{nameC}{nameD}{nameE}{nameF}{nameG}
\notenamesin{nameA}{nameB}{nameC}{nameD}{nameE}{nameF}{nameG}
\notenamesout{nameA}{nameB}{nameC}{nameD}{nameE}{nameF}{nameG}
\transposehere{chords}
\notrans{chords}
\gtabtrans{chord}{fret:strings:fingering}#*

## Between Songs ##
\begin{intersong}
\end{intersong}
\begin{intersong*}
\end{intersong*}
\begin{songgroup}
\end{songgroup}

\beginscripture{ref}
\endscripture
\Acolon
\Bcolon
\strophe
\scripindent
\scripoutdent

## Chapters and Sections ##
\songsection{title}#L2
\songchapter{title}#L1

## Indexes ##
\newindex{id}{filename%file}
\newauthorindex{id}{filename%file}
\newscripindex{id}{filename%file}
\showindex{title%text}{id}
\showindex[columns]{title%text}{id}
\indexentry{lyrics%text}
\indexentry[indexes]{lyrics%text}
\indextitleentry{title%text}
\indextitleentry[indexes]{title%text}

## Customizing the Book ##
\thesongnum#*
\printsongnum{arg}#*
\songnumwidth#*
\nosongnumbers
\theversenum#*
\printversenum{arg}#*
\versenumwidth#*
\noversenumbers
\placeversenum{arg}#*

\lyricfont#*
\stitlefont#*
\versefont#*
\chorusfont#*
\meterfont#*
\echofont#*
\notefont#*
\notebgcolor#*
\snumbgcolor#*
\printchord{arg}#*
\sharpsymbol#*
\flatsymbol#*
\everyverse#*
\everychorus#*
\versesep#*
\afterpreludeskip#*
\beforepostludeskip#*
\baselineadj#*
\clineparams#*
\cbarwidth#*
\sbarheight#*
\extendprelude#*
\showauthors#*
\showrefs#*
\extendpostlude#*
\makeprelude#*
\makepostlude#*
\vvpenalty#*
\ccpenalty#*
\vcpenalty#*
\cvpenalty#*
\brkpenalty#*
\sepverses#*
\versejustify#*
\chorusjustify#*
\justifyleft#*
\justifycenter#*
\notejustify#*
\placenote#*

\scripturefont#*
\printscrcite{arg}#*

\ifchorded
\chordedtrue#S
\chordedfalse#S
\iflyric
\lyrictrue#S
\lyricfalse#S
\ifslides
\slidestrue#S
\slidesfalse#S
\ifpartiallist
\partiallisttrue#S
\partiallistfalse#S
\ifpartial
\partialtrue#S
\partialfalse#S
\ifsongindexes
\songindexestrue#S
\songindexesfalse#S
\ifmeasures
\measurestrue#S
\measuresfalse#S
\ifrawtext
\rawtexttrue#S
\rawtextfalse#S
\iftranscapos
\transcapostrue#S
\transcaposfalse#S
\ifnolyrics
\nolyricstrue#S
\nolyricsfalse#S
\ifpagepreludes
\pagepreludestrue#S
\pagepreludesfalse#S
\ifvnumbered
\vnumberedtrue#S
\vnumberedfalse#S

\songcolumns{n}
\pagepreludes
\colbotglue#*
\lastcolglue#*
\songpos{level}
\spenalty#*

\sepindexestrue
\sepindexesfalse
\idxheadwidth#*
\idxrefsfont#*
\idxtitlefont#*
\idxlyricfont#*
\idxheadfont#*
\idxbgcolor#*
\idxauthfont#*
\idxscripfont#*
\idxbook{text}#*
\idxcont{text}#*
\indexsongsas{id}{number}#*
\songtarget{level}{name}#*
\songlink{name}{text}#*
\titleprefixword{word}#*
\authsepword{word}#*
\authbyword{word}#*
\authignoreword{word}#*

\songmark#*
\versemark#*
\chorusmark#*

\newsongkey{keyname%specialDef}{initcode}{setcode}#*s#%newsongkey
\newsongkey{keyname%specialDef}{initcode}[default]{setcode}#*

\chordlocals#*
\shiftdblquotes{arg1}{arg2}{arg3}{arg4}#*

## Informational Macros ##
\songauthors#*
\songrefs#*
\songcopyright#*
\songlicense#*
\songtitle#*
\resettitles#*
\nexttitle#*
\foreachtitle{code}#*
\songlist#*

# not in main documentation
\BarreDelims{arg1}{arg2}#S
\begin{chorus}#S
\begin{idxblock}{arg}#S
\begin{scripture}#S
\begin{song}#S
\commitsongs#S
\DeclareFlatSize{arg1}{arg2}#S
\end{chorus}#S
\end{idxblock}#S
\end{scripture}#S
\end{song}#S
\idxaltentry{arg1}{arg2}#S
\idxentry{arg1}{arg2}#S
\ifrepchorus#S
\ifsepindexes#S
\notenameA#S
\notenameB#S
\notenameC#S
\notenameD#S
\notenameE#S
\notenameF#S
\notenameG#S
\onesongcolumn#S
\printnoteA#S
\printnoteB#S
\printnoteC#S
\printnoteD#S
\printnoteE#S
\printnoteF#S
\printnoteG#S
\repchorusfalse#S
\repchorustrue#S
\scitehere#S
\songnumstyle#S
\twosongcolumns#S
\versenumstyle#S
