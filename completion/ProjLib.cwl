# ProjLib package
# Matthew Bertucci 12/30/2021

#include:kvoptions
#include:etoolbox
#include:PJLdate
#include:PJLdraft
#include:PJLlogo
#include:PJLmath
#include:PJLpaper
#include:PJLthm
#include:microtype

#ifOption:author
#include:PJLauthor
#endif
#ifOption:author=true
#include:PJLauthor
#endif
#ifOption:amsfashion
#include:PJLauthor
#endif
#ifOption:amsfashion=true
#include:PJLauthor
#endif

#ifOption:lmodern
#include:amssymb
#include:lmodern
#endif
#ifOption:lmodern=true
#include:amssymb
#include:lmodern
#endif

#ifOption:palatino
#include:mathpazo
#include:newpxtext
#endif
#ifOption:palatino=true
#include:mathpazo
#include:newpxtext
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
#endif
#ifOption:biolinum=true
#include:biolinum
#endif

#keyvals:\usepackage/ProjLib#c
draft#true,false
fast#true,false
author#true,false
amsfashion#true,false
nothms#true,false
delaythms#true,false
nothmnum#true,false
thmnum=%<counter%>
regionalref#true,false
originalref#true,false
complexname#true,false
simplename#true,false
useosf#true,false
lmodern#true,false
palatino#true,false
times#true,false
garamond#true,false
noto#true,false
biolinum#true,false
#endkeyvals