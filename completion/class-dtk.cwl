# dtk class
# Matthew Bertucci 3/27/2022 for v2.08h

#include:hyphsubst
#include:iftex
#include:luatex85
#include:xkeyval
#include:dtk-url
#include:class-scrbook
#include:scrhack
#include:dtk-extern
#include:babel
# loads english and main=ngerman options of babel
#include:csquotes
#include:microtype
#include:biblatex
#include:ragged2e
#include:dtk-logos
#include:scrlayer-scrpage
#include:xcolor
#include:listings
#include:lstautogobble
#include:marginnote
#include:enumitem

#keyvals:\documentclass/dtk#c
Ausgabe=
Jahr=
Monat=
korr#true,false
full#true,false
color#true,false
#endkeyvals

#ifOption:full
#include:multicol
#include:graphicx
#include:tabularx
#include:datetime2
#include:splitidx
#include:trimspaces
#include:picture
\AtEmbeddedBeginDocument#*
\AtEmbeddedEndDocument#*
\AutorenListenName#*
\begin{roll}
\begin{roll}[labelwidth%l]
\begin{theAutoren}
\DTKinput{file}#i
\DTKissueTOmonth{number}#*
\DTKmonthName#*
\DTKschriftenListe#*
\end{roll}
\end{theAutoren}
\ErzeugeMitarbeiterListe#*
\formatPosNumber{number}#*
\InfoTeX#*
\makePosNumbers{arg1}{arg2}#*
\MitarbeiterListe#*
\Part*{title}#L0
\Part[short title]{title}#L0
\Part{title}#L0
\rolllabel{label}#*
\theartcounter#*
#endif
#ifOption:full=true
#include:multicol
#include:graphicx
#include:tabularx
#include:datetime2
#include:splitidx
#include:trimspaces
#include:picture
\AtEmbeddedBeginDocument#*
\AtEmbeddedEndDocument#*
\AutorenListenName#*
\begin{roll}
\begin{roll}[labelwidth%l]
\begin{theAutoren}
\DTKinput{file}#i
\DTKissueTOmonth{number}#*
\DTKmonthName#*
\DTKschriftenListe#*
\end{roll}
\end{theAutoren}
\ErzeugeMitarbeiterListe#*
\formatPosNumber{number}#*
\InfoTeX#*
\makePosNumbers{arg1}{arg2}#*
\MitarbeiterListe#*
\Part*{title}#L0
\Part[short title]{title}#L0
\Part{title}#L0
\rolllabel{label}#*
\theartcounter#*
#endif

\Author{Vorname}{Nachname}{Adresse}
\begin{Figure}
\begin{Figure}[width]{caption%text}
\begin{Figure}{caption%text}
\begin{Table}[width]{caption
\begin{Table}{caption%text}
\Class{class%plain}
\Code{code}
\Command{command}
\DTKcorrVersion#*
\DTKdate#*
\DTKfullIssue#*
\DTKissn#*
\DTKissue#*
\DTKlstfont#*
\DTKlstKeywordfont#*
\DTKmonth#*
\DTKrecordfalse#*
\DTKrecordtrue#*
\DTKversion#*
\DTKversiondate#*
\DTKvolume#*
\DTKyear#*
\end{Figure}
\end{Table}
\Env{envname}#*
\Environment{envname}
\fullwidth#*
\ifDTKrecord#*
\journalname
\Macro{csname}
\ORIGprintbibliography#S
\Package{package%plain}
\Paket{package%plain}#*
\Program{program name}
\Programm{program}#*
\tex#S
\tex4ht

DTKlstBackground#B
DTKlstKeys#B
DTKlstComments#B
DTKlstStrings#B
DTKlstNumbers#B

# from dtk-author.clo
\AutorenListe#*
\keywords{keywords%text}

# from dtk-old-engines.clo
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:libertine
#include:AnonymousPro
\DTKrmFontName#*
\DTKsfFontName#*
\DTKttFontName#*
\DTKmathFontName#*

# from english and main=ngerman options of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
\captionsngerman
\datengerman
\extrasngerman
\noextrasngerman
\dq
\ntosstrue#*
\ntossfalse#*
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