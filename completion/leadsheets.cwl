# leadsheets package
# Matthew Bertucci 2022/08/03 for v0.7

#include:l3keys2e
#include:translations

# note: by default, all but musejazz libraries loaded

## I. About the Package ##
#keyvals:\usepackage/leadsheets#c
full
minimal
musicsymbols
chords
musejazz
songs
external
#endkeyvals

#ifOption:musejazz
#include:fontspec
#endif

\useleadsheetslibraries{list of libraries%keyvals}
\useleadsheetslibrary{library%keyvals}

#keyvals:\useleadsheetslibraries#c,\useleadsheetslibrary#c
musicsymbols
chords
musejazz
songs
external
#endkeyvals

## II. musicsymbols library ##
#include:etoolbox
#include:amsmath

\musix#*
\textmusix{text}#*
\musicsymbol{symbol}#*
\musicsymbol[raise%l]{symbol}#*

\sharp
\flat
\doublesharp
\doubleflat
\natural
\trebleclef
\bassclef
\altoclef
\allabreve
\meterC
\wholerest
\halfrest
\quarterrest
\eighthrest
\sixteenthrest
\Break
\normalbar
\leftrepeat
\rightrepeat
\leftrightrepeat
\doublebar
\stopbar

\normalbarwidth#*
\thickbarwidth#*
\interbarwidth#*

\meter{numerator}{denominator}

## III. chords library (and musejazz library) ##
\chordname{chord}
\writechord{chord}

\setchords{options%keyvals}

#keyvals:\setchords
format={%<code%>}
sharp={%<code%>}
flat={%<code%>}
double-sharp={%<code%>}
double-flat={%<code%>}
aug={%<code%>}
half-dim={%<code%>}
full-dim={%<code%>}
dim={%<code%>}
add={%<code%>}
sus={%<code%>}
major={%<code%>}
minor={%<code%>}
major-seven={%<code%>}
major-nine={%<code%>}
input-notation=#german,english
output-notation=#german,english
german-B={%<code%>}
german-H={%<code%>}
#endkeyvals

\musejazz#*

## IV. songs library ##
\begin{song}{properties}
\begin{song}[options%keyvals]{properties}
\end{song}

\setleadsheets{options%keyvals}

#keyvals:\begin{song},\setleadsheets
title-template=%<template name%>
chord-cs=%<command%>
song-format={%<code%>}
text-format={%<code%>}
before-song={%<code%>}
after-song={%<code%>}
after-title={%<code%>}
print-tags={%<list of tags%>}
add-to-reset={%<list of counters%>}
obey-lines#true,false
bar-shortcuts#true,false
disable-measuring#true,false
capo-nr-format=#arabic,roman,Roman
capo-nr={%<code%>}
smash-chords#true,false
smash-next-chord#true,false
empty-chord-dim=##L
align-chords=%<col%>
print-chords#true,false
remember-chords#true,false
transpose=%<number%>
enharmonic=#sharp,flat
transpose-capo#true,false
verses-format={%<code%>}
verses-label-format={%<code%>}
verses-after-label={%<code%>}
chords/format={%<code%>}
chords/sharp={%<code%>}
chords/flat={%<code%>}
chords/double-sharp={%<code%>}
chords/double-flat={%<code%>}
chords/aug={%<code%>}
chords/half-dim={%<code%>}
chords/full-dim={%<code%>}
chords/dim={%<code%>}
chords/add={%<code%>}
chords/sus={%<code%>}
chords/major={%<code%>}
chords/minor={%<code%>}
chords/major-seven={%<code%>}
chords/major-nine={%<code%>}
chords/input-notation=#german,english
chords/output-notation=#german,english
chords/german-B={%<code%>}
chords/german-H={%<code%>}
verse/format={%<code%>}
verse/label-format={%<code%>}
verse/class={%<class name%>}
verse/after-label={%<code%>}
verse/name=%<name%>
verse/template=%<template%>
verse/numbered#true,false
verse/named#true,false
verse/recall-chords={%<env-class%>}
#endkeyvals

\capo

\begin{verse}
\begin{verse}[options%keyvals]
\end{verse}
\begin{verse*}
\begin{verse*}[options%keyvals]
\end{verse*}
\begin{chorus}
\begin{chorus}[options%keyvals]
\end{chorus}
\begin{chorus*}
\begin{chorus*}[options%keyvals]
\end{chorus*}
\begin{intro}
\begin{intro}[options%keyvals]
\end{intro}
\begin{intro*}
\begin{intro*}[options%keyvals]
\end{intro*}
\begin{outro}
\begin{outro}[options%keyvals]
\end{outro}
\begin{interlude}
\begin{interlude}[options%keyvals]
\end{interlude}
\begin{bridge}
\begin{bridge}[options%keyvals]
\end{bridge}
\begin{info}
\begin{info}[options%keyvals]
\end{info}
\begin{solo}
\begin{solo}[options%keyvals]
\end{solo}
\begin{solo*}
\begin{solo*}[options%keyvals]
\end{solo*}

\newversetype{envname}#N
\newversetype{envname}[options%keyvals]#N
\newversetype*{envname}#N
\newversetype*{envname}[options%keyvals]#N
\provideversetype{envname}#*N
\provideversetype{envname}[options%keyvals]#*N
\provideversetype*{envname}#*N
\provideversetype*{envname}[options%keyvals]#*N

#keyvals:\begin{verse},\begin{verse*},\begin{chorus},\begin{chorus*},\begin{intro},\begin{intro*},\begin{outro},\begin{interlude},\begin{bridge},\begin{info},\begin{solo},\begin{solo*},\newversetype,\newversetype*,\provideversetype,\provideversetype*
format={%<code%>}
label-format={%<code%>}
class={%<class name%>}
after-label={%<code%>}
name=%<name%>
template=%<template%>
numbered#true,false
named#true,false
recall-chords={%<env-class%>}
#endkeyvals

#keyvals:\begin{verse}
type=%<type%>
#endkeyvals

\chord{chord}
\chord*{chord}
\chord-{chord}

\definesongtitletemplate{name}{code}#*
\definesongproperty{property}#*
\copysongproperty{from}{to}#*
\songproperty{property}#*
\printsongpropertylist{property}{between two}{between more}{between last two}#*
\printsongpropertylist[code]{property}{between two}{between more}{between last two}#*
\usesongpropertylist{property}{between}#*
\usesongpropertylist[code]{property}{between}#*
\forsongpropertylist{property}{code}#*
\ifsongproperty{property}{true}{false}#*
\ifanysongproperty{properties}{true}{false}#*
\ifallsongproperties{properties}{true}{false}#*
\ifsongpropertiesequal{property1}{property2}{true}{false}#*
\ifsongpropertyequal{property1}{property2}{true}{false}#*
\ifsongmeasuring{true}{false}#*
\expandcode{code}#*
\defineversetypetemplate{name}{begin code}{end code}#*
\verselabel#*
\verselabelformat#*
\verseafterlabel#*
\versename#*
\versenumber#*
\ifversestarred{true}{false}#*
\ifversenumbered{true}{false}#*
\ifversenamed{true}{false}#*
\ifobeylines{true}{false}#*

## V. external library ##
\includeleadsheet{file}#i
\includeleadsheet[options%keyvals]{file}#i
\includeleadsheet*{file}#i
\includeleadsheet*[options%keyvals]{file}#i

#keyvals:\includeleadsheet,\includeleadsheet*
gobble-preamble#true,false
#endkeyvals

## miscellaneous ##
\AddExternalClass{class}#S
\AddExternalFile{file}{ext}#S
\AddExternalPackage{package}#S
\coda#S
\defleadsheetstranslation{arg1}{arg2}{arg3}#S
\eigthnote#S
\genericbar{arg}#S
\getorprintchord#S
\halfdim#S
\halfnote#S
\LeadsheetEndSurvive#S
\leadsheetsdate#S
\LeadsheetsExplLibrary{library name}{info}#S
\leadsheetsiflibrary{library}#S
\leadsheetsifpackageloaded{package}#S
\leadsheetsinfo#S
\LeadsheetsLibrary{library name}{info}#S
\leadsheetstranslate{arg}#S
\LeadsheetSurvive#S
\leadsheetsversion#S
\musicdot#S
\quarternote#S
\recallchord#S
\segno#S
\sixteenthnote#S
\wholenote#S
