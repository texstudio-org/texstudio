# fontsetup package
# Matthew Bertucci 2023/01/02 for v1.4

#include:fontspec
#include:unicode-math
#include:ifthen
#include:iftex

#keyvals:\usepackage/fontsetup#c
default
upint
varnothing
gfsartemisia
gfsdidot
gfsdidotclassic
gfsneohellenic
cambria
lucida
kerkis
fira
times
palatino
stixtwo
neokadmus
msgaramond
ebgaramond
minion
neoeuler
libertinus
olddefault
concrete
talos
oldstandard
xcharter
#endkeyvals

#ifOption:default
#include:newcomputermodern
#endif

#ifOption:olddefault
#include:newcomputermodern
#endif

#ifOption:gfsneohellenic
#include:gfsneohellenicot
#endif

#ifOption:gfsdidot
\GFSDidotoSubstFont#*
\GFSDidotoSubst#*
\phifix#*
#endif

#ifOption:gfsdidotclassic
\defaultfont#*
\latinfont#*
#endif

#ifOption:libertinus
#include:libertinus-otf
#endif

#ifOption:xcharter
#include:xcharter-otf
#endif

\leftgrquotes#S
\rightgrquotes#S

\fontsetupdefault#S
\fontsetupgfsartemisia#S
\fontsetupgfsdidot#S
\fontsetupgfsdidotclassic#S
\fontsetupgfsneohellenic#S
\fontsetupcambria#S
\fontsetuplucida#S
\fontsetupkerkis#S
\fontsetupfira#S
\fontsetuptimes#S
\fontsetuppalatino#S
\fontsetupstixtwo#S
\fontsetupneokadmus#S
\fontsetupmsgaramond#S
\fontsetupebgaramond#S
\fontsetupminion#S
\fontsetupneoeuler#S
\fontsetuplibertinus#S
\fontsetupolddefault#S
\fontsetupconcrete#S
\fontsetuptalos#S
\fontsetupoldstandard#S
\fontsetupxcharter#S
\fontsetupfont#S
