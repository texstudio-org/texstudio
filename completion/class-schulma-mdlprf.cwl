# schulma-mdlprf class
# Matthew Bertucci 2/16/2022 for v1.2

#include:class-scrartcl
#include:babel
#include:datetime2
#include:schulma
#include:schulma-physik

#keyvals:\documentclass/schulma-mdlprf#c
AT
Prueferin
# other options passed to scrartcl
#endkeyvals

\Schule{Schulname}
\Datum{Datum}
\Fach{Unterrichtsfach%text}
\Vorbereitungsraum{Raum}
\Vorbereitungszeit{Zeit}
\Pruefungsraum{Raum}
\Pruefer{Name}
\PNummer{Nummer}
\Hilfsmittel{Hilfsmittel%text}
\Aufgabe{Aufgabentext%text}
\Erwartungshorizont{Lösung%text}
\WeitereThemen{Themen%text}
\Pruefung{Name}{Uhrzeit}

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

#ifOption:AT
\captionsnaustrian#*
\datenaustrian#*
\extrasnaustrian#*
\noextrasnaustrian#*
#endif