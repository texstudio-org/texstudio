# g-brief class
# Matthew Bertucci 2023/02/10 for v4.0.3

#include:class-letter
#include:babel
# loads ngerman option of babel
#include:inputenc
#include:marvosym
#include:europs
#include:eurosym

#keyvals:\documentclass/g-brief#c
10pt
11pt
12pt
ansinew
applemac
ascii
cp1250
cp1252
cp437de
cp437
cp850
cp852
cp865
decmulti
latin1
latin2
latin3
latin4
latin5
latin9
next
german
ngerman
english
american
#endkeyvals

\begin{g-brief}
\end{g-brief}

\adresse#*
\Adresse{Anschrift}
\anlagen#*
\Anlagen{Anlagen}
\anrede#*
\Anrede{Anrede%text}
\bank#*
\Bank{Bank}
\banktext#*
\betreff#*
\Betreff{Betreff%text}
\betrefftext#*
\blz#*
\BLZ{Bankleitzahl}
\blztext#*
\datum#*
\Datum{Datum}
\datumtext#*
\Einrueckung{text}#*
\email#*
\EMail{eMail-Adresse%URL}#U
\emailtext#*
\faltmarken
\faltmarkenfalse#S
\faltmarkentrue#S
\fenstermarken
\fenstermarkenfalse#S
\fenstermarkentrue#S
\filedate#S
\filename#S
\fileversion#S
\gruss#*
\Gruss{text}{length}
\grussskip#*
\http#*
\HTTP{URL}#U
\httptext#*
\iffaltmarken#*
\iffenstermarken#*
\ifklassisch#*
\iflochermarke#*
\iftrennlinien#*
\ifunserzeichen#*
\ihrschreiben#*
\IhrSchreiben{Datum}
\ihrschreibentext#*
\ihrzeichen#*
\IhrZeichen{Zeichen}
\ihrzeichentext#*
\klassisch
\klassischfalse#S
\klassischtrue#S
\konto#*
\Konto{Kontonummer}
\kontotext#*
\land#*
\Land{Land}
\lochermarke
\lochermarkefalse#S
\lochermarketrue#S
\meinzeichen#*
\MeinZeichen{Zeichen}
\meinzeichentext#*
\name#*
\Name{Name}
\ort#*
\Ort{Postleitzahl und Ort}
\postvermerk#*
\Postvermerk{Vermerke}
\retouradresse#*
\RetourAdresse{Adresse}
\sprache#*
\strasse#*
\Strasse{Straße}
\telefax#*
\Telefax{Telefaxnummer}
\telefaxtext#*
\Telefon{Telefonnummer}
\telefontex#*
\telex#*
\Telex{Telexnummer}
\telextext#*
\trennlinien
\trennlinienfalse#S
\trennlinientrue#S
\unserzeichen
\unserzeichenfalse#S
\unserzeichentext#*
\unserzeichentrue#S
\unterschrift#*
\Unterschrift{Name}
\verteiler#*
\Verteiler{Verteiler}
\VorschubH#L
\VorschubV#L
\zusatz#*
\Zusatz{Zusatz zur Adresse}

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