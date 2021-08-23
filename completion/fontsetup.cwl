# fontsetup package
# Matthew Bertucci 8/18/2021 for v1.02

#include:fontspec
#include:unicode-math
#include:ifthen
#include:iftex

#ifOption:default
#include:newcomputermodern
#endif

#ifOption:olddefault
#include:newcomputermodern
#endif

#ifOption:fira
#include:FiraSans
#include:firamath-otf
#endif

#ifOption:gfsneohellenic
#include:gfsneohellenicot
#endif

#ifOption:libertinus
#include:libertinus-otf
#endif