# ucalgmthesis class
# Matthew Bertucci 2023/03/20 for release 2023/03/18

#include:class-memoir
#include:fontenc
# loads T1 option of fontenc

#keyvals:\documentclass/ucalgmthesis#c
singlespaced
onehalfspaced
doublespaced
palatino
times
garamond
utopia
libertine
plain
headers
fullpage
manuscript
#endkeyvals

#ifOption:palatino
#include:amsthm
#include:newpxtext
#include:newpxmath
#endif

#ifOption:times
#include:amsthm
#include:newtxtext
#include:newtxmath
#endif

#ifOption:garamond
#include:amsthm
#include:garamondx
#include:newtxmath
#endif

#ifOption:utopia
#include:amsthm
#include:erewhon
#include:newtxmath
#endif

#ifOption:libertine
#include:amsthm
#include:libertine
#include:newtxmath
#endif

\dedication{text}
\degree{degree%text}
\dept{department%text}#*
\fixmdhrulefill#*
\fullpagethesis#*
\gradyear{year}#*
\makethesistitle
\manuscriptthesis#*
\monthname{month%text}
\prog{program%text}
\thesis{text}#*
\thesisyear{year}

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
