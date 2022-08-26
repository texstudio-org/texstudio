# isov2 class
# Matthew Bertucci 2022/08/24 for v2.4

#include:url

#keyvals:\documentclass/isov2#c
a4paper
letterpaper
9pt
10pt
11pt
onecolumn
twocolumn
copyright
notcopyright
is
fdis
dis
cd
wd
techrep
techspec
pas
otherdoc
final
draft
#endkeyvals

\clause{title}#L2
\clause[short title]{title}#L2
\clause*{title}#L2
\sclause{title}#L3
\sclause[short title]{title}#L3
\sclause*{title}#L3
\ssclause{title}#L4
\ssclause[short title]{title}#L4
\ssclause*{title}#L4
\sssclause{title}#L5
\sssclause[short title]{title}#L5
\sssclause*{title}#L5
\ssssclause{title}#L6
\ssssclause[short title]{title}#L6
\ssssclause*{title}#L6
\sssssclause{title}#L7
\sssssclause[short title]{title}#L7
\sssssclause*{title}#L7

\normannex{title}
\infannex{title}
\repannex{title}

\maxsecnumdepth{sec%keyvals}
\maxtocdepth{sec%keyvals}
\setsecnumdepth{sec%keyvals}
\settocdepth{sec%keyvals}

#keyvals:\maxsecnumdepth#c,\maxtocdepth#c,\setsecnumdepth#c,\settocdepth#c
clause
sclause
ssclause
sssclause
ssssclause
sssssclause
#endkeyvals

\begin{note}
\end{note}
\begin{anote}
\end{anote}
\begin{example}
\end{example}
\begin{anexample}
\end{anexample}

\begin{nreferences}
\end{nreferences}
\isref{ref%text}{title%text}
\disref{ref%text}{title%text}

\begin{references}
\end{references}
\reference{author}{title%text}{publisher}

\begin{inscope}
\end{inscope}
\begin{outofscope}
\end{outofscope}
\inscopename#*
\outofscopename#*

\begin{olddefinitions}
\end{olddefinitions}
\olddefinition{phrase%text}{supplement%text}
\begin{definitions}
\end{definitions}
\definition{phrase%text}{definition text%text}
\begin{symbols}
\end{symbols}
\symboldef{symbol}{definition text%text}

\contcaption{text}

\title{intro%text}{main%text}{compl%text}
\standard{number}
\yearofedition{year}
\languageofedition{code}
\extrahead#*

\begin{cover}
\end{cover}
\aref{label}#r
\bref{label}#r
\cref{label}#r
\eref{label}#r
\fref{label}#r
\nref{label}#r
\tref{label}#r
\pref{label}#r

\begin{foreword}
\end{foreword}
\forewordname#*
\fwdbp
\tspasfwdbp
\trfwdbpi#*
\fwdnopatents

\begin{introduction}
\end{introduction}
\introductionname#*
\intropatents

\scopeclause#L2
\normrefsclause#L2
\normrefsname#*
\normrefbp{document identifier}
\defclause#L2
\symclause#L2
\abbclause#L2
\defsymclause#L2
\defabbclause#L2
\symabbclause#L2
\defsymabbclause#L2
\defsubclause#L3
\symsubclause#L3
\abbsubclause#L3
\defsymsubclause#L3
\defabbsubclause#L3
\symabbsubclause#L3
\symname#*
\symabbname#*
\defsymname#*
\defsymabbname#*
\defname#*
\defabbname#*
\abbname#*

\bibannex
\bibname#*

\isourl{URL}#U

\ifchangemarks#*
\changemarkstrue
\changemarksfalse#*
\editorial{number}
\added{text}{number}
\deleted{number}
\moved{text}{number}
\ifpdf
\pdftrue#*
\pdffalse#*

\annexname#*
\copyrightname#*
\examplename#*
\informativename#*
\ISname#*
\listannexname#*
\normativename#*
\notename#*
\pagename#*
\scopename#*
\tbpname#*
\annexrefname#*
\clauserefname#*
\examplerefname#*
\figurerefname#*
\noterefname#*
\tablerefname#*
\pagerefname#*

\copyrightnotice#*
\captionsize

# not documented
\addannextotoc{arg1}{arg2}#*
\alphaindexspace{arg}#*
\begin{bottomfloat}#*
\cdstandardfalse#S
\cdstandardtrue#S
\chaptername#S
\clausemark{code}#S
\compelement{text}#*
\copyrighthead#*
\disstandardfalse#S
\disstandardtrue#S
\end{bottomfloat}#*
\fcandaclause#*
\fcandaname#*
\fdisstandardfalse#S
\fdisstandardtrue#S
\figsfalse#S
\figstrue#S
\fillline#*
\floatlist{arg1}{arg2}#*
\hyperpage{arg}#*
\ifcdstandard#S
\ifdisstandard#S
\iffdisstandard#S
\iffigs#S
\ifinfloat#S
\ifisohyper#S
\ifisstandard#S
\ifotherdoc#S
\ifpaspec#S
\iftabs#S
\iftechrep#S
\iftechspec#S
\ifwdstandard#S
\indexfill#*
\indexsee{arg}#*
\indexseealso{arg}#*
\infloatfalse#S
\infloattrue#S
\introelement{text}#*
\isoemptystring{arg}#*
\isohyperfalse#S
\isohypertrue#S
\isostringsequal{arg1}{arg2}#*
\isstandardfalse#S
\isstandardtrue#S
\labelinfref#*
\loftfillnum{arg}#*
\loftnumberline{arg}#*
\mainelement{text}#*
\makeannexhead{arg}#*
\makecommand*{cmd}[args][default]{def}#*d
\makecommand*{cmd}[args]{def}#*d
\makecommand*{cmd}{def}#*d
\makecommand{cmd}[args][default]{def}#*d
\makecommand{cmd}[args]{def}#*d
\makecommand{cmd}{def}#*d
\makepreannexhead{arg}#*
\notelabel{arg}#*
\nreferencelabel{arg}#*
\otherdocfalse#S
\otherdoctrue#S
\otherindexspace{arg}#*
\paspecfalse#S
\paspectrue#S
\rectoisotitlehead#*
\sclausemark{arg}
\sectionname#S
\sindexfill#*
\ssclausemark{code}#S
\ssindexfill#*
\sssclausemark{code}#S
\ssssclausemark{code}#S
\sssssclausemark{code}#S
\symbollabel{arg}#*
\tabsfalse#S
\tabstrue#S
\techrepfalse#S
\techreptrue#S
\techspecfalse#S
\techspectrue#S
\theannex#*
\thebottomfloat#*
\theclause#*
\theexample#*
\thefloatnote#*
\theHannex#*
\theHclause#*
\theHexample#*
\theHfloatnote#*
\theHnote#*
\theHsclause#*
\theHssclause#*
\theHsssclause#*
\theHssssclause#*
\theHsssssclause#*
\theinfrefctr#*
\thenote#*
\thesclause#*
\theslanguage#*
\thessclause#*
\thesssclause#*
\thessssclause#*
\thesssssclause#*
\thestandard#*
\thesyear#*
\thetitle#*
\theyextra#*
\tocbaseline#*
\tocentryskip#*
\tocskip{arg}#*
\trfwdbpii{arg}#*
\versoisotitlehead#*
\wdstandardfalse#S
\wdstandardtrue#S
\zerocounters#*