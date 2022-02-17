# schulma-ab class
# Matthew Bertucci 2/16/2022 for v1.2

#include:class-scrartcl
#include:adjustbox
#include:babel
#include:isodate
#include:schulma
#include:schulma-physik
#include:tasks
#include:enumitem
#include:scrlayer-scrpage
#include:comment

#keyvals:\documentclass/schulma-ab#c
A4quer
A5
A5quer
AT
Musterloesung
# other options passed to scrartcl
#endkeyvals

\Kurs{Kursbezeichnung%text}
\Datum{Datum}
\Thema{Thema%text}
\Thema[Nummer]{Thema%text}
\Bearbeiter{Name}
\schulmaalph{counter}#*
\begin{Kreisliste}
\end{Kreisliste}
\Aufgabentitel{Bezeichnung%text}
\Aufgabenabstand#*
\begin{Aufgaben}
\end{Aufgaben}
\Aufgabe
\Aufgabe*
\Uebung
\Uebung*
\theAufgabe#*
\theTeilaufgabe#*
\Teilaufgabenabstand#*
\begin{Teilaufgaben}
\end{Teilaufgaben}
\Luecke{Breite}
\begin{Lsg}
\begin{Lsg}*
\end{Lsg}
\NurAufgabe{Teil der Aufgabe}
\NurLoesung{Teil der Aufgabe}

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