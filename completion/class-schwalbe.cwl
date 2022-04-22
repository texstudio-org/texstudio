# schwalbe class
# Matthew Bertucci 4/20/2022 for v2.7

#include:schwalbe
#include:fontenc
# loads T2A and T1 options of fontenc
#include:inputenc
#include:babel
# loads russian, german, english, and ngerman options of babel
#include:eurosym
#include:ifthen
#include:times
#include:multicol
#include:url
#include:paralist
#include:afterpage
#include:picinpar

\Heft{volume}{issue}{year}{page}
\begin{Editorial}{heading%text}
\begin{Editorial}[short title%text]{title%text}
\end{Editorial}
\begin{aktuell}
\end{aktuell}
\begin{InformalEntscheid}{dept}{year}{name}
\end{InformalEntscheid}
\begin{Aufsatz}
\end{Aufsatz}{title%text}{author}
\begin{Titel}
\end{Titel}
\begin{Untertitel}
\end{Untertitel}
\begin{Urdrucke}{number}
\end{Urdrucke}
\Abteilung{dept}{firstrefname}{lastrefname}{name}{email}
\Abteilung*{dept}{firstrefname}{name}{email}
\begin{maerchenlexikon}
\end{maerchenlexikon}
\maerchenart{text}
\begin{retrolexikon}
\end{retrolexikon}
\retroart{text}
\begin{Loesungen}
\end{Loesungen}
\Loeser{short name}{name}
\Loeser*{short name}{name}
\ListeLoeserKuerzel
\begin{BuB}
\end{BuB}
\begin{turnierberichte}
\end{turnierberichte}
\begin{Buecher}
\end{Buecher}
\Buch{authors}{title%text}
\Buch*
\begin{WebSites}
\end{WebSites}
\WebSite{URL}#U
\begin{Briefkasten}
\end{Briefkasten}
\begin{Turnierbericht}{tournament}{author}
\end{Turnierbericht}
\begin{Entscheid}{title%text}
\end{Entscheid}
\begin{Loeserliste}{year}
\end{Loeserliste}
\TurnierAusschreibung{text}
\Nachruf{text}
\dauerkonto{text}
\loesungswettbewerb{text}
\dh
\ua
\zB
\su
\ep
\seedia
\bsol
\esol
\figline
\foto{Breite}{Hoehe}{Bildunterschrift}
\mal

# not documented
\Briefkasten#*
\Einladung{text}#*
\Entscheid#*
\Geburtstag{arg}#*
\Inhalt#*
\LoesungenBis#*
\SchwalbeCopyright#*
\Turnierberichte#*
\Verstorben{arg1}{arg2}#*
\aTurnier{arg1}{arg2}#*
\aufsatz{arg1}{arg2}{arg3}#*
\bTurnier{arg}#*
\begin{Bericht}#*
\end{Bericht}#*
\begin{Gruss}#*
\end{Gruss}#*
\begin{Tagung}#*
\end{Tagung}#*
\eEntscheid{arg}#*
\editorial{arg}#*
\turnier{arg1}#*

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

# from T2A option of fontenc
\C{arg}#n
\CYRA#n
\cyra#n
\CYRAE#n
\cyrae#n
\CYRB#n
\cyrb#n
\CYRC#n
\cyrc#n
\CYRCH#n
\cyrch#n
\CYRCHRDSC#n
\cyrchrdsc#n
\CYRCHVCRS#n
\cyrchvcrs#n
\CYRD#n
\cyrd#n
\cyrdash#n
\CYRDJE#n
\cyrdje#n
\CYRDZE#n
\cyrdze#n
\CYRDZHE#n
\cyrdzhe#n
\CYRE#n
\cyre#n
\CYREREV#n
\cyrerev#n
\CYRERY#n
\cyrery#n
\CYRF#n
\cyrf#n
\CYRG#n
\cyrg#n
\CYRGHCRS#n
\cyrghcrs#n
\CYRGUP#n
\cyrgup#n
\CYRH#n
\cyrh#n
\CYRHDSC#n
\cyrhdsc#n
\CYRHRDSN#n
\cyrhrdsn#n
\CYRI#n
\cyri#n
\CYRIE#n
\cyrie#n
\CYRII#n
\cyrii#n
\CYRISHRT#n
\cyrishrt#n
\CYRJE#n
\cyrje#n
\CYRK#n
\cyrk#n
\CYRKBEAK#n
\cyrkbeak#n
\CYRKDSC#n
\cyrkdsc#n
\CYRKVCRS#n
\cyrkvcrs#n
\CYRL#n
\cyrl#n
\cyrlangle#n
\CYRLJE#n
\cyrlje#n
\CYRM#n
\cyrm#n
\CYRN#n
\cyrn#n
\CYRNDSC#n
\cyrndsc#n
\CYRNG#n
\cyrng#n
\CYRNJE#n
\cyrnje#n
\CYRO#n
\cyro#n
\CYROTLD#n
\cyrotld#n
\CYRP#n
\cyrp#n
\CYRpalochka#n
\CYRQ#n
\cyrq#n
\CYRR#n
\cyrr#n
\cyrrangle#n
\CYRS#n
\cyrs#n
\CYRSCHWA#n
\cyrschwa#n
\CYRSDSC#n
\cyrsdsc#n
\CYRSFTSN#n
\cyrsftsn#n
\CYRSH#n
\cyrsh#n
\CYRSHCH#n
\cyrshch#n
\CYRSHHA#n
\cyrshha#n
\CYRT#n
\cyrt#n
\CYRTSHE#n
\cyrtshe#n
\CYRU#n
\cyru#n
\CYRUSHRT#n
\cyrushrt#n
\CYRV#n
\cyrv#n
\CYRW#n
\cyrw#n
\CYRY#n
\cyry#n
\CYRYA#n
\cyrya#n
\CYRYHCRS#n
\cyryhcrs#n
\CYRYI#n
\cyryi#n
\CYRYO#n
\cyryo#n
\CYRYU#n
\cyryu#n
\CYRZ#n
\cyrz#n
\CYRZDSC#n
\cyrzdsc#n
\CYRZH#n
\cyrzh#n
\CYRZHDSC#n
\cyrzhdsc#n
\f{arg}#n
\U{arg}#n

# from russian option of babel
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Russian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\NOD#m
\nod#m
\NOK#m
\nok#m
\Proj#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\captionsrussian#*
\daterussian#*
\extrasrussian#*
\noextrasrussian#*
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\prefacename#*
\bibname#*
\chaptername#*
\tocname#*
\authorname#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*

# from german option of babel
\captionsgerman#*
\dategerman#*
\extrasgerman#*
\noextrasgerman#*
\tosstrue#*
\tossfalse#*
\mdqon#*
\mdqoff#*
\ck#*
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
#repl:"ck ck
#repl:"ff ff
#repl:"ll ll
#repl:"mm mm
#repl:"nn nn
#repl:"pp pp
#repl:"rr rr
#repl:"tt tt
#repl:"FF FF
#repl:"LL LL
#repl:"MM MM
#repl:"NN NN
#repl:"PP PP
#repl:"RR RR
#repl:"TT TT
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

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*

# from ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\ntosstrue#*
\ntossfalse#*