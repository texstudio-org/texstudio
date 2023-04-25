# se2packages package
# Matthew Bertucci 2023/04/18 for v3.0.0

# packages loaded by default
#include:csquotes
#include:booktabs
#include:selnolig
#include:lua-widow-control
#include:microtype

#keyvals:\usepackage/se2packages#c
csquotes#true,false
nocsquotes
booktabs#true,false
nobooktabs
siunitx#true,false
minted#true,false
listings#true,false
biblatex#true,false
selnolig#true,false
noselnolig
widowcontrol#true,false
nowidowcontrol
microtype#true,false
nomicrotype
cleveref#true,false
all#true,false
#endkeyvals

#ifOption:siunitx
#include:siunitx
#endif
#ifOption:siunitx=true
#include:siunitx
#endif

#ifOption:minted
#include:minted
#endif
#ifOption:minted=true
#include:minted
#endif

#ifOption:listings
#include:listings
#endif
#ifOption:listings=true
#include:listings
#endif

#ifOption:biblatex
#include:biblatex
#endif
#ifOption:biblatex=true
#include:biblatex
#endif

#ifOption:cleveref
#include:cleveref
#endif
#ifOption:cleveref=true
#include:cleveref
#endif

# all does not load listings
#ifOption:all
#include:siunitx
#include:minted
#include:biblatex
#include:cleveref
#endif
#ifOption:all=true
#include:siunitx
#include:minted
#include:biblatex
#include:cleveref
#endif