# minimart class
# Matthew Bertucci 2/15/2022 for 2021/12/16 release

#include:kvoptions
#include:etoolbox
#include:silence
#include:geometry
#include:parskip
#include:minimalist
#include:iftex
#include:fontenc
#include:inputenc
#include:mathpazo
#include:newpxtext
#include:amssymb
#include:microtype
#include:nowidow
#include:embrac
#include:graphicx
#include:wrapfig
#include:float
#include:caption

#keyvals:\documentclass/minimart#c
draft#true,false
fast#true,false
classical#true,false
useindent#true,false
useosf#true,false
lmodern#true,false
palatino#true,false
times#true,false
garamond#true,false
noto#true,false
biolinum#true,false
customfont#true,false
thmnum=%<counter%>
b5paper
a4paper
# options passed to article class
a5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:draft
#include:draftwatermark
#endif
#ifOption:draft=true
#include:draftwatermark
#endif
#ifOption:fast
#include:draftwatermark
#endif
#ifOption:fast=true
#include:draftwatermark
#endif

#ifOption:classical
#include:indentfirst
#endif
#ifOption:classical=true
#include:indentfirst
#endif

#ifOption:lmodern
#include:lmodern
#endif
#ifOption:lmodern=true
#include:lmodern
#endif

#ifOption:times
#include:newtxtext
#include:newtxmath
#endif
#ifOption:times=true
#include:newtxtext
#include:newtxmath
#endif

#ifOption:garamond
#include:ebgaramond-maths
#include:ebgaramond
#endif
#ifOption:garamond=true
#include:ebgaramond-maths
#include:ebgaramond
#endif

#ifOption:noto
#include:anyfontsize
#include:notomath
#endif
#ifOption:noto=true
#include:anyfontsize
#include:notomath
#endif

#ifOption:biolinum
#include:biolinum
#include:mathastext
#endif
#ifOption:biolinum=true
#include:biolinum
#include:mathastext
#endif

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