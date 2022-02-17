# schulma-gutachten class
# Matthew Bertucci 2/16/2022 for v1.2

#include:class-scrartcl
#include:babel
#include:datetime2
#include:siunitx

#keyvals:\documentclass/schulma-gutachten#c
BELL
AT
Referentin
Korreferentin
# other options passed to scrartcl
#endkeyvals

\Schule{Schulname}
\Ort{Schulort}
\Datum{Datum}
\Fach{Unterrichtsfach%text}
\Gesamtpunktzahl{Punktzahl}
\Name
\NameDativ
\begin{Gutachten}{Vorname}{Nachname}{Geschlecht}{Punktzahl}
\begin{Gutachten}{Vorname}{Nachname}{Geschlecht}{Punktzahl}[Abwertung]
\end{Gutachten}

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