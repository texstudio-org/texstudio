# se2packages package
# Matthew Bertucci 2023/09/12 for v3.2.0

# packages loaded by default
#include:fvextra
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
biblatex=#true,false,alphabetic,numeric
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
#include:ragged2e
#include:sidenotesplus
\makebibmarginnote{arg}#S
\maycite[prenote][postnote]{bibid}#C
\maycite[postnote]{bibid}#C
\maycite{bibid}#C
\margincite[prenote][postnote]{bibid}#C
\margincite[postnote]{bibid}#C
\margincite{bibid}#C
\margincites{bibid}{bibid}#C
\margincites(post){bibid}{bibid}#*C
\margincites(pre)(post){bibid}{bibid}#C
\margincites(pre)(post)[post]{bibid}[post]{bibid}#*C
\margincites[post]{bibid}[post]{bibid}#*C
\margincites[pre][post]{bibid}[pre][post]{bibid}#*C
\margincites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\bibliofont#S
#endif
#ifOption:biblatex=true
#include:biblatex
#include:ragged2e
#include:sidenotesplus
\makebibmarginnote{arg}#S
\maycite[prenote][postnote]{bibid}#C
\maycite[postnote]{bibid}#C
\maycite{bibid}#C
\margincite[prenote][postnote]{bibid}#C
\margincite[postnote]{bibid}#C
\margincite{bibid}#C
\margincites{bibid}{bibid}#C
\margincites(post){bibid}{bibid}#*C
\margincites(pre)(post){bibid}{bibid}#C
\margincites(pre)(post)[post]{bibid}[post]{bibid}#*C
\margincites[post]{bibid}[post]{bibid}#*C
\margincites[pre][post]{bibid}[pre][post]{bibid}#*C
\margincites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\bibliofont#S
#endif
#ifOption:biblatex=numeric
#include:biblatex
#include:ragged2e
#include:sidenotesplus
\makebibmarginnote{arg}#S
\maycite[prenote][postnote]{bibid}#C
\maycite[postnote]{bibid}#C
\maycite{bibid}#C
\margincite[prenote][postnote]{bibid}#C
\margincite[postnote]{bibid}#C
\margincite{bibid}#C
\margincites{bibid}{bibid}#C
\margincites(post){bibid}{bibid}#*C
\margincites(pre)(post){bibid}{bibid}#C
\margincites(pre)(post)[post]{bibid}[post]{bibid}#*C
\margincites[post]{bibid}[post]{bibid}#*C
\margincites[pre][post]{bibid}[pre][post]{bibid}#*C
\margincites(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\bibliofont#S
#endif

#ifOption:biblatex=alphabetic
#include:biblatex
#include:software-biblatex
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
