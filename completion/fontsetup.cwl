# fontsetup package
# Matthew Bertucci 12/11/2021 for v1.1

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

\quoteleft#S
\quoteright#S

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
\fontsetupfont#S
