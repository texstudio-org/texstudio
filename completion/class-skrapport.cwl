# skrapport class
# Matthew Bertucci 2/2/2022 for v0.12k

#include:l3keys2e
#include:xstring
#include:etoolbox
#include:typearea
#include:multicol
#include:babel
#include:amsmath
#include:amssymb
#include:calc
#include:isodate
#include:isomath
#include:microtype
#include:skmath
#include:textcomp
#include:xcolor
#include:xkeyval
#include:fontenc

#keyvals:\documentclass/skrapport#c
paper=#a4,a5
twocolumn
leqno
fleqn
indent#true,false
titles=#rm,it,bf,sf
hanging-titles#true,false
color=#default,unscathed,cruelwater,violet,skdoc,false
ptsize=#10pt,11pt,12pt
font=#none,kpfonts,lmodern,palatino,minion,skdoc,word
nomath#true,false
lang=#en,sv,de
draft#true,false
#endkeyvals

#ifOption:twocolumn
#include:grid
\begin{onecol}
\end{onecol}
#endif
#ifOption:twocolumn=true
#include:grid
\begin{onecol}
\end{onecol}
#endif

#ifOption:font=kpfonts
#include:kpfonts
#endif

#ifOption:font=lmodern
#include:lmodern
#include:sourcecodepro
#endif

#ifOption:font=palatino
#include:arev
#include:pxfonts
#include:tgpagella
#include:sourcecodepro
#endif

#ifOption:font=minion
#include:MinionPro
#include:MnSymbol
#include:MyriadPro
#include:sourcecodepro
#endif

#ifOption:font=skdoc
#include:PTSerif
#include:opensans
#include:sourcecodepro
#endif

#ifOption:font=word
#include:fontspec
#endif

# all lang options load british option of babel
\captionsbritish#*
\datebritish#*
\extrasbritish#*
\noextrasbritish#*
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

#ifOption:lang=en
\captionsswedish#*
\dateswedish#*
\extrasswedish#*
\noextrasswedish#*
\swedishhyphenmins#*
\datesymd
\datesdmy
\dq
#repl:"a ä
#repl:"o ö
#repl:"A Ä
#repl:"O Ö
#repl:"w å
#repl:"W Å
#repl:"f f
#repl:"b b
#repl:"d d
#repl:"g g
#repl:"l l
#repl:"m m
#repl:"n n
#repl:"p p
#repl:"r r
#repl:"s s
#repl:"t t
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#endif

#ifOption:lang=sv
\captionsswedish#*
\dateswedish#*
\extrasswedish#*
\noextrasswedish#*
\swedishhyphenmins#*
\datesymd
\datesdmy
\dq
#repl:"a ä
#repl:"o ö
#repl:"A Ä
#repl:"O Ö
#repl:"w å
#repl:"W Å
#repl:"f f
#repl:"b b
#repl:"d d
#repl:"g g
#repl:"l l
#repl:"m m
#repl:"n n
#repl:"p p
#repl:"r r
#repl:"s s
#repl:"t t
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#endif

#ifOption:lang=de
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
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
#endif

\author[email%URL]{name}
\regarding{topic%text}
\license{license name%text}

\maketitle[options%keyvals]
#keyvals:\maketitle
hide={%<types%>}
nopdfinfo
#endkeyvals

\begin{figcenter}
\end{figcenter} 

\comment{comment%todo}#D
\comment*{comment%todo}#D
\note{comment%todo}#*D
\note*{comment%todo}#*D
\com{comment%todo}#*D
\com*{comment%todo}#*D

\eg
\ie
\etc
\cf
\viz
\dash

\colortheme{theme%keyvals}
#keyvals:\colortheme
default
unscathed
cruelwater
violet
skdoc
#endkeyvals

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n