# ucalgmthesis class
# Matthew Bertucci 2022/06/07 for release 2019/10/24

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
#include:mathdesign
#include:garamondx
#endif

#ifOption:utopia
#include:mathdesign
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