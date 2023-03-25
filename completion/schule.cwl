# schule package
# Matthew Bertucci 2023/03/21 for v0.8.4

#include:pgfopts
#include:xifthen
#include:xstring
#include:forarray
#include:babel
# loads ngerman option of babel
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:environ
#include:amsmath
#include:xcolor
# loads table and dvipsnames options of xcolor
#include:tikz
#include:graphicx
#include:hyperref

#keyvals:\usepackage/schule#c
fach=#Informatik,Physik,Geschichte
weitereFaecher={%<Fach1,Fach2,...%>}
module=#Aufgaben,Aufgabenpool,Bewertung,Format,Formulare,genord,Kuerzel,Lizenzen,Metadaten,Papiertypen,Storycard,Symbole,Texte
typ=#ab,Beurteilung,folie,kl,leit,lzk,ub,ueb,ohne
sprache={%<lang1,lang2,...%>}
debug
#endkeyvals

#ifOption:typ=schuleALT
#include:schulealt
#endif

\swarnung{Text%text}
\sfehler{Text%text}
\sinfo{Text%text}
\sdwarnung{Text%text}
\sdinfo{Text%text}

# no good way to distinguish module={mod1,mod2,...} syntax with #ifOption so all commands from modules listed here

## module: Aufgaben ##
#include:xsim
#include:tcolorbox
#include:utfsym

#keyvals:\usepackage/schule#c
loesungen=#folgend,keine,seite
#endkeyvals

\setzeSymbol{Symbol}
\punkteAufgabe
\punkteTotal
\punktuebersicht
\punktuebersicht[Darstellungsart]
\punktuebersicht*
\punktuebersicht*[Darstellungsart]

\begin{aufgabe}
\begin{aufgabe}[Optionen%keyvals]
\end{aufgabe}
\begin{aufgabe*}
\begin{aufgabe*}[Optionen%keyvals]
\end{aufgabe*}

#keyvals:\begin{aufgabe},\begin{aufgabe*}
ID=%<text%>
counter-value=%<integer%>
subtitle=%<text%>
points=%<number%>
bonus-points=%<number%>
print#true,false
print!#true,false
use#true,false
use!#true,false
used#true,false
solution#true,false
tags={%<tag1,tag2,...%>}
topics={%<topic1,topic2,...%>}
page=%<text%>
page-value=%<integer%>
section=%<text%>
section-value=%<integer%>
chapter=%<text%>
chapter-value=%<integer%>
sectioning={%<section numbers%>}
exercise-body={%<code%>}
solution-body={%<code%>}
%xsimexerprop
%xsimexertag
# properties provided by schule
symbol=%<symbol%>
#endkeyvals

\setzeAufgabentemplate{Templatename%keyvals}

#keyvals:\setzeAufgabentemplate
schule-binnen
schule-default
schule-keinenummer
schule-keinepunkte
schule-keintitel
schule-randpunkte
schule-tcolorbox
#endkeyvals

\teilaufgabe
\teilaufgabe[Punkte]
\teilaufgabeOhneLoesung
\begin{teilaufgaben}
\end{teilaufgaben}
\begin{loesung}
\end{loesung}
\begin{loesung*}
\end{loesung*}

\luecke{Länge}
\luecke[Optionen für blank%keyvals]{Text%text}
\textluecke{Länge}
\textluecke[Optionen für blank%keyvals]{Text%text}

#keyvals:\luecke,\textluecke
blank-style={%<code%>}
filled-style={%<code%>}
style={%<code%>}
scale=%<factor%>
width=##L
linespread=%<factor%>
line-increment=##L
line-minimum-length=##L
#endkeyvals

\choice
\choice[richtig]
\mcrichtig
\mcloesung
\begin{mcumgebung}(Spaltenzahl)
\end{mcumgebung}
\begin{bearbeitungshinweis}
\end{bearbeitungshinweis}
\bearbeitungshinweisZuAufgabe{AufgabenId}
\bearbeitungshinweisZuAufgabe[Aufgabentyp]{AufgabenId}
\bearbeitungshinweisliste

## module: Aufgabenpool ##
#include:standalone

\aufgabeninput{Verzeichnis}{Datei%file}
\getBasedir
\setBasedir
\basedir#*

## module: Bewertung ##
# loads Aufgaben module

#keyvals:\usepackage/schule#c
erwartungshorizontAnzeigen
erwartungshorizontKeineSeiten
erwartungshorizontStil=#einzeltabellen,simpel,standard
kmkPunkte
notenOhneTendenz
notenschema={%<spec%>}
#endkeyvals

\begin{erwartungen}
\end{erwartungen}
\erwartung{Erwartung}{Punkte}
\erwartung{Erwartung}{Punkte}[Zusatzpunkte]
\erwartungshorizont
\notenverteilung

## module: Format ##
#include:enumitem
# loads inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}
#include:multirow
#include:longtable
#include:ctable
#include:array
#include:tasks
#include:csquotes
#include:setspace
#include:ulem
#include:xspace
#include:amssymb
#include:eurosym
#include:zref-totpages
#include:refcount

#keyvals:\usepackage/schule#c
farbig
datumAnzeigen
namensfeldAnzeigen
seitenzahlen=#auto,autoGesamt,immer,immerGesamt,keine
zitate=#guillemets,quotes,swiss 
#endkeyvals

\achtung{Text%text}
\chb
\chb*
\hinweis{Text%text}
\person{Name}
\so{Text%text}
\Seitenzahlen
\begin{smalldescription}
\end{smalldescription}
\begin{smallenumerate}
\end{smallenumerate}
\begin{smallitemize}
\end{smallitemize}
\diastring{Zeichenkette}
\hierkeineseitenzahl#S
\abhierkeineseitenzahl#S

## module: Formulare ##
\feldLinFormular{Anzahl}
\feldLinFormular{Anzahl}[Textfeldargumente]
\feldLinFormular[Abstand]{Anzahl}
\feldLinFormular[Abstand]{Anzahl}[Textfeldargumente]

## module: Kuerzel ##
#keyvals:\usepackage/schule#c
gendering=#binneni,fem,gap,mas,split,star
#endkeyvals

\Lkr
\Lkre
\Lpr
\Lprn
\EuE
\EuEn
\EK
\GK
\LK
\EKe
\GKe
\LKe
\EKen
\GKen
\LKen
\SuS
\SuSn
\LuL
\LuLn
\KuK
\KuKn

## module: Lizenzen ##
#include:doclicense
#include:ccicons

#keyvals:\usepackage/schule#c
lizenz=#cc-by-4,cc-by-sa-4,cc-by-nc-sa-4,cc-by-nc-sa-eu-4
nohyperxmp
#endkeyvals

\lizenzName
\lizenzNameKurz
\lizenzSymbol

## module: Metadaten ##
#keyvals:\usepackage/schule#c
lerngruppe=%<Lerngruppe%>
nummer=%<Dokumentnummer%>
#endkeyvals

\Autor
\Datum
\Titel
\Fach
\Lerngruppe
\Kurs
\DokumentNummer

## module: Papiertypen ##
\feldLin{Anzahl}
\feldLin[Abstand]{Anzahl}
\feldKar{Anzahl}
\feldKar[Seitenlänge]{Anzahl}
\feldMil{Anzahl}

## module: Symbole ##
\symNase
\symAuge
\symAugen
\symMund
\symZunge
\symOhr
\symDaumenHoch
\symDaumenRunter
\symZeigefinger
\symApplaus

\symSprechblase
\symZweiSprechblasen
\symDreiSprechblasen
\symDenkblase

\symPalette

\symBleistift
\symFueller
\symKuli
\symBuntstift
\symLineal
\symGeodreieck
\symBueroklammer
\symBueroklammern
\symPin
\symNadel
\symPinsel
\symBuch
\symBild
\symMikroskop
\symHeft
\symBuecher
\symKlemmbrett
\symCD
\symZeitung
\symThermometer
\symSchere
\symSchloss
\symSchlossOffen
\symSchluessel
\symGlocke
\symKeineGlocke
\symLupe

\symNote
\symNoten

\symSmileyLachend
\symSmileyNeutral
\symSmileyTraurig
\symSmileyGrinsend
\symSmileySchlafend
\symSmileyZwinkernd

\symKlee
\symSonne
\symMond
\symStern
\symUhr
\symHaken

\symSpielkarte
\symPik
\symHerz
\symKaro
\symKreuz
\symPikAss
\symPikZwei
\symPikDrei
\symPikVier
\symPikFuenf
\symPikSechs
\symPikSieben
\symPikAcht
\symPikNeun
\symPikZehn
\symPikBube
\symPikDame
\symPikKoenig
\symHerzAss
\symHerzZwei
\symHerzDrei
\symHerzVier
\symHerzFuenf
\symHerzSechs
\symHerzSieben
\symHerzAcht
\symHerzNeun
\symHerzZehn
\symHerzBube
\symHerzDame
\symHerzKoenig
\symKaroAss
\symKaroZwei
\symKaroDrei
\symKaroVier
\symKaroFuenf
\symKaroSechs
\symKaroSieben
\symKaroAcht
\symKaroNeun
\symKaroZehn
\symKaroBube
\symKaroDame
\symKaroKoenig
\symKreuzAss
\symKreuzZwei
\symKreuzDrei
\symKreuzVier
\symKreuzFuenf
\symKreuzSechs
\symKreuzSieben
\symKreuzAcht
\symKreuzNeun
\symKreuzZehn
\symKreuzBube
\symKreuzDame
\symKreuzKoenig

\symBaseball
\symBasketball
\symFussball
\symVolleyball
\symHockey
\symLaufen
\symReiten
\symSchwimmen
\symSki
\symSnowboard
\symSurfen
\symTennis
\symTischtennis
\symPokal
\symMedaille
\symZielflagge

\symHandy
\symKeinHandy

\symTheater

\symAuto
\symBus
\symBahn
\symStrassenbahn
\symSchwebebahn
\symSeilbahn
\symSchiff
\symBoot
\symFahrrad
\symFussgaenger
\symRollstuhl

\symWuerfelEins
\symWuerfelZwei
\symWuerfelDrei
\symWuerfelVier
\symWuerfelFuenf
\symWuerfelSechs

## module: Texte ##
#include:lineno
#include:multicol

\resetZeilenNr
\begin{mehrspaltig}
\begin{mehrspaltig}[Anzahl]
\end{mehrspaltig}
\begin{zeilenNr}
\begin{zeilenNr}[Modulo]
\end{zeilenNr}
\begin{zeilenNrMehrspaltig}{Anzahl}
\begin{zeilenNrMehrspaltig}[Modulo]{Anzahl}
\end{zeilenNrMehrspaltig}
\begin{zeilenNrZweispaltig}
\begin{zeilenNrZweispaltig}[Modulo]
\end{zeilenNrZweispaltig}

## module: Storycard ## (not documented)
\begin{scMaterial}#S
\end{scMaterial}#S
\begin{scNeedSkillCards}#S
\end{scNeedSkillCards}#S
\begin{scAufgabe}#S
\end{scAufgabe}#S
\begin{scLoesung}#S
\end{scLoesung}#S
\begin{scStoryCard}{arg}#S
\begin{scStoryCard}[opt]{arg}#S
\end{scStoryCard}#S
\begin{scSkillCard}{arg}#S
\begin{scSkillCard}[opt]{arg}#S
\end{scSkillCard}#S

# no good way to distinguish weitereFaecher={fach1,fach2,...} syntax with #ifOption so all commands from fachmodules listed here

## fach: Informatik ##
#include:struktex
#include:relaycircuit
#include:pgf-umlcd
#include:pgf-umlsd
#include:syntaxdi
#include:tikzlibraryer
#include:listings
#include:tikzlibraryshapes
#include:tikzlibraryshadows.blur

\anchormark{Nodename}
\anchormark{Nodename}[Skalierung]
\anchormark[Horizontale Verschiebung]{Nodename}
\anchormark[Horizontale Verschiebung]{Nodename}[Skalierung]
\skaliereSequenzdiagramm{Faktor}
\newthreadtwo{Bezeichnung}{Name}{Abstand}
\newthreadtwo[Farbe]{Bezeichnung}{Name}{Abstand}
\nextlevel

#keyvals:\begin{tikzpicture}#c
pap
#endkeyvals

#keyvals:\node#c
startstop
verzweigung
aktion
einausgabe
unterprogramm
#endkeyvals

#keyvals:\draw#c
linie
#endkeyvals

\begin{klassenDokumentation}#S
\end{klassenDokumentation}#S
\methodenDokumentation{arg1}{arg2}{arg3}#S

## fach: Physik ##
#include:nicefrac
#include:mhchem
#include:ziffer

\elementarladung
\plankscheEV
\plankscheJ
\elektronenmasse
\protonenmasse
\lichtgeschwindigkeit
\rydbergfrequenz
\unit{dimension}
\unit[value]{dimension}
\unitfrac{num}{den}
\unitfrac[value]{num}{den}

## fach: Geschichte ##
#include:biblatex
#include:marginnote

\material{title}#L3
\material[Ebene]{title}#L3
\quelle{title}#L3
\quelle[Ebene]{title}#L3
\vt{title}#L3
\vt[Ebene]{title}#L3
\thematcounter#S
\thequelcounter#S
\thevtcounter#S

# Dokumenttypen

## typ: ab ##
#include:scrlayer-scrpage
\dokumententypName{arg}#S

## typ: kl ##
#keyvals:\usepackage/schule#c
klausurtyp=#klausur,klasse,kurs
#endkeyvals

## typ: leit ##
#include:scrhack

#keyvals:\usepackage/schule#c
hinweisLinkVerbergen
loesungLinkVerbergen
#endkeyvals

\TextFeld{Höhe}
\monatWort{Monatszahl}
\uebungBild
\hinweisBild
\begin{hinweisBox}
\end{hinweisBox}

\headingpar#S

## typ: lzk ##
# no new commands

## typ: ueb ##
# no new commands

## typ: ub ##
\besuchtitel{Titel%text}
\lehrer{Lehrername}
\schulform{Schulform}
\lerngruppe{Name der Lerngruppe}{Anzahl weiblich}{Anzahl männlich}
\lerngruppe[Kurzform der Lerngruppe]{Name der Lerngruppe}{Anzahl weiblich}{Anzahl männlich}
\zeit{Startzeit}{Endzeit}{Stunde}
\schule{Name der Schule}
\raum{Raumbezeichnung}

## typ: folie ##
#include:geometry

## typ: Beurteilung ##
#include:tcolorboxlibrarybreakable
#include:tcolorboxlibraryskins

#keyvals:\usepackage/schule#c
beurteilung={%<Namen%>}
ref={%<Namen%>}
zeitraum={%<Zeitraum%>}
schulname={%<Namen%>}
schullogo=%<imagefile%>
schulanschrift={%<schulanschrift%>}
schulstr={%<Straße%>}
schulort={%<Ort%>}
lehramt={%<Lehramt%>}
#endkeyvals

\setzeGrundlagen{Termine}
\begin{handlungsfeld1}
\begin{handlungsfeld1}[tcolorbox options]
\end{handlungsfeld1}
\begin{handlungsfeld2}
\begin{handlungsfeld2}[tcolorbox options]
\end{handlungsfeld2}
\begin{handlungsfeld3}
\begin{handlungsfeld3}[tcolorbox options]
\end{handlungsfeld3}
\begin{handlungsfeld4}
\begin{handlungsfeld4}[tcolorbox options]
\end{handlungsfeld4}
\begin{handlungsfeld5}
\begin{handlungsfeld5}[tcolorbox options]
\end{handlungsfeld5}
\begin{handlungsfeld6}
\begin{handlungsfeld6}[tcolorbox options]
\end{handlungsfeld6}

# from ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# from table option of xcolor
#include:colortbl

# from dvipsnames option of xcolor
Apricot#B
Aquamarine#B
Bittersweet#B
Black#B
Blue#B
BlueGreen#B
BlueViolet#B
BrickRed#B
Brown#B
BurntOrange#B
CadetBlue#B
CarnationPink#B
Cerulean#B
CornflowerBlue#B
Cyan#B
Dandelion#B
DarkOrchid#B
Emerald#B
ForestGreen#B
Fuchsia#B
Goldenrod#B
Gray#B
Green#B
GreenYellow#B
JungleGreen#B
Lavender#B
LimeGreen#B
Magenta#B
Mahogany#B
Maroon#B
Melon#B
MidnightBlue#B
Mulberry#B
NavyBlue#B
OliveGreen#B
Orange#B
OrangeRed#B
Orchid#B
Peach#B
Periwinkle#B
PineGreen#B
Plum#B
ProcessBlue#B
Purple#B
RawSienna#B
Red#B
RedOrange#B
RedViolet#B
Rhodamine#B
RoyalBlue#B
RoyalPurple#B
RubineRed#B
Salmon#B
SeaGreen#B
Sepia#B
SkyBlue#B
SpringGreen#B
Tan#B
TealBlue#B
Thistle#B
Turquoise#B
Violet#B
VioletRed#B
White#B
WildStrawberry#B
Yellow#B
YellowGreen#B
YellowOrange#B
