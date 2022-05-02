# minutes package
# updated 4/11/2022 for v1.8f

#include:multicol
#include:xspace
#include:url
#include:minitoc
#include:keyval

#keyvals:\usepackage/minutes#c
ListTitle
TableTitle
OneColumn
TwoColumn
CreateCld
8+3
Fileinfo
Secret
ASCII
#endkeyvals

\minutesstyle{keyvals}

#keyvals:\minutesstyle#c
columns=%<number%>
header=#list,table
contents#true,false
vote=#list,table
#endkeyvals

\begin{Minutes}{title}#L0
\begin{Minutes}[short title]{title}#L0
\end{Minutes}
\foreignMinutes{description%text}
\foreignMinutes[pages]{description%text}
\subtitle{text}
\moderation{name%text}
\minutetaker{name%text}
\participant{name1,name2,...%text}
\guest{name1,name2,...%text}
\minutesdate{date}
\starttime{time}
\endtime{time}
\location{location%text}
\cc{name1,name2,...%text}
\missing[no excuse name%text]{excused name1,excused name2,...%text}
\missingExcused{name1,name2,...%text}
\missingNoExcuse{name1,name2,...%text}
\topic{title}#L2
\topic[short title]{title}#L2
\addtopic{title}#L2
\addtopic[short title]{title}#L2
\subtopic{title}#L3
\subtopic[short title]{title}#L3
\subsubtopic{title}#L4
\subsubtopic[short title]{title}#L4
\minitopic{title}#L5
\newcols
\newcols[title%text]
\newcols[title%text][number]
\task{*who%text}{what%text}
\task{*who%text}[when%text]{what%text}
\task[done%text]{*who%text}{what%text}
\task[done%text]{*who%text}[when%text]{what%text}
\listoftasks
\listoftasks[file]#i
\schedule{when}{what%text}
\schedule{when}{what%text}[long%text]#*
\schedule{when}[time]{what%text}#*
\schedule{when}[time]{what%text}[long%text]#*
\schedule[cal]{when}{what%text}#*
\schedule[cal]{when}{what%text}[long%text]#*
\schedule[cal]{when}[time]{what%text}#*
\schedule[cal]{when}[time]{what%text}[long%text]
\begin{Vote}
\end{Vote}
\vote{text}{yes}{no}{-}
\vote{text}{yes}{no}{-}[resolution%text]
\decisiontheme{label}{title}#l
\decision{ref%ref}{text}#r
\decision{ref%ref}{text}[longText%text]#r
\decision*{text}
\decision*{text}[longText%text]
\listofdecisions
\begin{Argumentation}
\end{Argumentation}
\pro
\Pro
\contra
\Contra
\result
\begin{Opinions}
\end{Opinions}
\opinion{who}{what%text}
\begin{Secret}
\end{Secret}
\secret{text}
\attachment{title%text}{pages}
\attachment[label]{title%text}{pages}#l
\listofattachments
\postscript{text}
\begin{Postscript}
\end{Postscript}
\inputminutes{file}#i

# German aliases
\begin{Protokoll}{title}#*L0
\begin{Protokoll}[short title]{title}#*L0
\end{Protokoll}#*
\protokollKopf#*
\fremdProtokoll{description%text}#*
\fremdProtokoll[pages]{description%text}#*
\untertitel{text}#*
\protokollant{name%text}#*
\teilnehmer{name1,name2,...%text}#*
\gaeste{name1,name2,...%text}#*
\sitzungsdatum{date}#*
\sitzungsbeginn{time}#*
\sitzungsende{time}#*
\sitzungsort{location%text}#*
\verteiler{name1,name2,...%text}#*
\fehlend[no excuse name%text]{excused name1,excused name2,...%text}#*
\fehlendEntschuldigt{name1,name2,...%text}#*
\fehlendUnentschuldigt{name1,name2,...%text}#*
\zusatztopic{title}#*L2
\zusatztopic[short title]{title}#*L2
\neueSpalte#*
\neueSpalte[title%text]#*
\neueSpalte[title%text][number]#*
\aufgabe{*who%text}{what%text}#*
\aufgabe{*who%text}[when%text]{what%text}#*
\aufgabe[done%text]{*who%text}{what%text}#*
\aufgabe[done%text]{*who%text}[when%text]{what%text}#*
\aufgabenliste#*
\aufgabenliste[file]#*i
\termin{when}{what%text}
\termin{when}{what%text}[long%text]#*
\termin{when}[time]{what%text}#*
\termin{when}[time]{what%text}[long%text]#*
\termin[cal]{when}{what%text}#*
\termin[cal]{when}{what%text}[long%text]#*
\termin[cal]{when}[time]{what%text}#*
\termin[cal]{when}[time]{what%text}[long%text]#*
\begin{Abstimmung}#*
\end{Abstimmung}#*
\abstimmung{text}{yes}{no}{-}#*
\abstimmung{text}{yes}{no}{-}[resolution%text]#*
\beschlussthema{label}{title}#*l
\beschluss{ref%ref}{text}#*r
\beschluss{ref%ref}{text}[longText%text]#*r
\beschluss*{text}#*
\beschluss*{text}[longText%text]#*
\beschlussliste#*
\ergebnis#*
\begin{Meinungen}#*
\end{Meinungen}#*
\meinung{who}{what%text}#*
\begin{Geheim}#*
\end{Geheim}#*
\geheim{text}#*
\anhang{title%text}{pages}#*
\anhang[label]{title%text}{pages}#*l
\anhangsliste#*
\nachtrag{text}#*
\begin{Nachtrag}#*
\end{Nachtrag}#*

# Dutch aliases
\begin{Notulen}{title}#*L0
\begin{Notulen}[short title]{title}#*L0
\end{Notulen}#*
\notulenkop#*
\extranotulen{description%text}#*
\extranotulen[pages]{description%text}#*
\ondertitel{text}#*
\voorzitter{name%text}#*
\notulist{name%text}#*
\deelnemer{name1,name2,...%text}#*
\gast{name1,name2,...%text}#*
\bijeenkomstdatum{date}#*
\beginbijeenkomst{time}#*
\eindbijeenkomst{time}#*
\locatie{location%text}#*
\afwezig[no excuse name%text]{excused name1,excused name2,...%text}#*
\afwezigBericht{name1,name2,...%text}#*
\afwezigZonderBericht{name1,name2,...%text}#*
\extrapunt{title}#*L2
\extrapunt[short title]{title}#*L2
\nieuweKolom#*
\nieuweKolom[title%text]#*
\nieuweKolom[title%text][number]#*
\aktie{*who%text}{what%text}#*
\aktie{*who%text}[when%text]{what%text}#*
\aktie[done%text]{*who%text}{what%text}#*
\aktie[done%text]{*who%text}[when%text]{what%text}#*
\aktielijst#*
\aktielijst[file]#*i
\termijn{when}{what%text}#*
\termijn{when}{what%text}[long%text]#*
\termijn{when}[time]{what%text}#*
\termijn{when}[time]{what%text}[long%text]#*
\termijn[cal]{when}{what%text}#*
\termijn[cal]{when}{what%text}[long%text]#*
\termijn[cal]{when}[time]{what%text}#*
\termijn[cal]{when}[time]{what%text}[long%text]#*
\begin{Stemming}#*
\end{Stemming}#*
\stemming{text}{yes}{no}{-}#*
\stemming{text}{yes}{no}{-}[resolution%text]#*
\besluitonderwerp{label}{title}#*l
\besluit{ref%ref}{text}#*r
\besluit{ref%ref}{text}[longText%text]#*r
\besluit*{text}#*
\besluit*{text}[longText%text]#*
\besluitenlijst#*
\resultaat#*
\bijlage{title%text}{pages}#*
\bijlage[label]{title%text}{pages}#*l
\bijlagenlijst#*
\naschrift{text}#*
\begin{Naschrift}#*
\end{Naschrift}#*

# not documented
\hyperloadedfalse#S
\hyperloadedtrue#S
\ifhyperloaded#S
\minfiledate#S
\minfileversion#S
\minutestask{text}{section}{when%text}{who%text}{date}{file}{page}#*
\prepareCal#*
\prepareCal[file]#*
\responsiblelength#*
\thecolumns#*
\theHattachment#S
\votelength#*
