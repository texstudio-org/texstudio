# leadsheets package
# Matthew Bertucci 12/22/2021 for v0.5c

#include:expl3
#include:l3keys2e
#include:translations
#include:xparse

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

\newversetype{envname}
\newversetype{envname}[options%keyvals]
\newversetype*{envname}
\newversetype*{envname}[options%keyvals]

#keyvals:\begin{verse},\begin{verse*},\begin{chorus},\begin{chorus*},\begin{intro},\begin{intro*},\begin{interlude},\begin{bridge},\begin{info},\begin{solo},\begin{solo*},\newversetype,\newversetype*
format={%<code%>}
label-format={%<code%>}
class={%<class name%>}
after-label={%<code%>}
name=%<name%>
template=%<template%>
numbered#true,false
named#true,false
recall-chords={%<env-class%>}
verses-format={%<code%>}
verses-label-format={%<code%>}
verses-after-label={%<code%>}
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
\leadsheetsdate#S
\leadsheetsversion#S
\leadsheetsinfo#S
\LeadsheetsExplLibrary{library name}{info}#S
\LeadsheetsLibrary{library name}{info}#S
\leadsheetsiflibrary{arg1}#S
\leadsheetsifpackageloaded{arg1}#S
\LeadsheetSurvive#S
\LeadsheetEndSurvive#S
\recallchord#S
\getorprintchord#S
\segno#S
\coda#S
\halfdim#S
\wholenote#S
\halfnote#S
\quarternote#S
\eigthnote#S
\sixteenthnote#S
\musicdot #S