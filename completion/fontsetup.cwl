# fontsetup package
# Matthew Bertucci 2024/11/04 for v2.3.0

#include:iflang
#include:iftex
#include:fontspec
#include:unicode-math
#include:ifthen

#keyvals:\usepackage/fontsetup#c
default
sansdefault
upint
varnothing
newcmbb
olddefault
cambria
concrete
ebgaramond
erewhon
euler
fira
gfsartemisia
gfsdidotclassic
gfsdidot
gfsneohellenic
kerkis
libertinus
lucida
minion
msgaramond
oldstandard
palatino
stixtwo
talos
times
xcharter
#endkeyvals

#ifOption:default
#include:newcomputermodern
#endif

#ifOption:olddefault
#include:newcomputermodern
#endif

#ifOption:erewhon
#include:fourier-otf
#endif

#ifOption:gfsdidotclassic
\defaultfont#S
\latinfont#S
#endif

#ifOption:gfsdidot
\phifix#S
#endif

#ifOption:gfsneohellenic
#include:gfsneohellenicot
#endif

#ifOption:libertinus
#include:libertinus-otf
#endif

#ifOption:xcharter
#include:xcharter-otf
#endif

\leftgrquotes#*
\rightgrquotes#*

# not documented
\greeksetup#S
\cvfoursetup#S
\ncmsetup#S
\ncmsanssetup#S
