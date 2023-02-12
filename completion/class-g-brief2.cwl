# g-brief2 class
# Matthew Bertucci 2023/02/10 for v4.0.3

#include:ifthen
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
\adresstext#*
\adresszeilea#*
\AdressZeileA{text}
\adresszeileb#*
\AdressZeileB{text}
\adresszeilec#*
\AdressZeileC{text}
\adresszeiled#*
\AdressZeileD{text}
\adresszeilee#*
\AdressZeileE{text}
\adresszeilef#*
\AdressZeileF{text}
\anlagen#*
\Anlagen{Anlagen}
\anrede#*
\Anrede{Anrede%text}
\banktext#*
\bankzeilea#*
\BankZeileA{text}
\bankzeileb#*
\BankZeileB{text}
\bankzeilec#*
\BankZeileC{text}
\bankzeiled#*
\BankZeileD{text}
\bankzeilee#*
\BankZeileE{text}
\bankzeilef#*
\BankZeileF{text}
\betreff#*
\Betreff{Betreff%text}
\datum#*
\Datum{Datum}
\datumtext#*
\Einrueckung{text}#*
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
\iffaltmarken#*
\iffenstermarken#*
\iflochermarke#*
\iftrennlinien#*
\ifunserzeichen#*
\ihrschreiben#*
\IhrSchreiben{Datum}
\ihrschreibentext#*
\ihrzeichen#*
\IhrZeichen{Zeichen}
\ihrzeichentext#*
\internettext#*
\internetzeilea#*
\InternetZeileA{text}
\internetzeileb#*
\InternetZeileB{text}
\internetzeilec#*
\InternetZeileC{text}
\internetzeiled#*
\InternetZeileD{text}
\internetzeilee#*
\InternetZeileE{text}
\internetzeilef#*
\InternetZeileF{text}
\lochermarke
\lochermarkefalse#S
\lochermarketrue#S
\meinzeichen#*
\MeinZeichen{Zeichen}
\meinzeichentext#*
\name#*
\Name{Name}
\namezeilea#*
\NameZeileA{text}
\namezeileb#*
\NameZeileB{text}
\namezeilec#*
\NameZeileC{text}
\namezeiled#*
\NameZeileD{text}
\namezeilee#*
\NameZeileE{text}
\namezeilef#*
\NameZeileF{text}
\namezeileg#*
\NameZeileG{text}
\postvermerk#*
\Postvermerk{Vermerke}
\retouradresse#*
\RetourAdresse{Adresse}
\sprache#*
\telefontext#*
\telefonzeilea#*
\TelefonZeileA{text}
\telefonzeileb#*
\TelefonZeileB{text}
\telefonzeilec#*
\TelefonZeileC{text}
\telefonzeiled#*
\TelefonZeileD{text}
\telefonzeilee#*
\TelefonZeileE{text}
\telefonzeilef#*
\TelefonZeileF{text}
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