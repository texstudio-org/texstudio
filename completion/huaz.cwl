# huaz package
# Matthew Bertucci 2024/04/30 for v2.0

#include:xstring
#include:refcount
#include:iftex

\az{szöveg}
\az*{szöveg}
\azv{szöveg}
\azv*{szöveg}

\Az{szöveg}
\Az*{szöveg}
\Azv{szöveg}
\Azv*{szöveg}

\azsaved
\aznotshow
\azseparator{kód}

\aref{label}#r
\aref*{label}#r
\avref{label}#r
\avref*{label}#r
\aeqref{label}#r
\aveqref{label}#r
\arefeq{label}#r
\avrefeq{label}#r
\apageref{label}#r
\apageref*{label}#r
\avpageref{label}#r
\avpageref*{label}#r

\Aref{label}#r
\Aref*{label}#r
\Avref{label}#r
\Avref*{label}#r
\Aeqref{label}#r
\Aveqref{label}#r
\Arefeq{label}#r
\Avrefeq{label}#r
\Apageref{label}#r
\Apageref*{label}#r
\Avpageref{label}#r
\Avpageref*{label}#r

\acite{bibid}#C
\acite[szöveg]{bibid}#C
\avcite{bibid}#C
\avcite[szöveg]{bibid}#C

\Acite{bibid}#C
\Acite[szöveg]{bibid}#C
\Avcite{bibid}#C
\Avcite[szöveg]{bibid}#C

\huazignorecmd{parancs}
\huazignorecmd[opció]{parancs}
\huazrefcmd{parancs}
\huazpagerefcmd{parancs}
\huazdefcmd{átdefiniáló kód}
