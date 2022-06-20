# projlib-font package
# Matthew Bertucci 2022/06/17 for 2022/06/15 release

#include:l3keys2e
#include:anyfontsize
#include:setspace
#include:microtype

#keyvals:\usepackage/projlib-font#c
useosf
lmodern
palatino
times
garamond
noto
biolinum
#endkeyvals

#ifOption:lmodern
#include:amssymb
#include:lmodern
#endif
#ifOption:lmodern=true
#include:amssymb
#include:lmodern
#endif
#ifOption:latin-modern
#include:amssymb
#include:lmodern
#endif
#ifOption:latin-modern=true
#include:amssymb
#include:lmodern
#endif
#ifOption:latin modern
#include:amssymb
#include:lmodern
#endif
#ifOption:latin modern=true
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
#include:newtxmath
#include:ebgaramond-maths
#include:ebgaramond
#endif
#ifOption:garamond=true
#include:newtxmath
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
#include:eulervm
#include:biolinum
#include:mathastext
#endif
#ifOption:biolinum=true
#include:eulervm
#include:biolinum
#include:mathastext
#endif
