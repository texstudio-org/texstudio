# selnolig package
# Matthew Bertucci 11/26/2021 for v0.302

#include:ifluatex
#include:luatexbase

#keyvals:\usepackage/selnolig#c
english
ngerman
noftligs
broadf
hdlig
noadditionalhyphenationpatterns
#endkeyvals

#ifOption:english
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:UKenglish
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:british
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:USenglish
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:american
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:canadian
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:australian
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:newzealand
#include:selnolig-english-patterns
#include:selnolig-english-hyphex
#endif

#ifOption:ngerman
#include:selnolig-german-patterns
#include:selnolig-german-hyphex
#endif

#ifOption:german
#include:selnolig-german-patterns
#include:selnolig-german-hyphex
#endif

#ifOption:austrian
#include:selnolig-german-patterns
#include:selnolig-german-hyphex
#endif

#ifOption:naustrian
#include:selnolig-german-patterns
#include:selnolig-german-hyphex
#endif

#ifOption:swissgerman
#include:selnolig-german-patterns
#include:selnolig-german-hyphex
#endif

#ifOption:swiss
#include:selnolig-german-patterns
#include:selnolig-german-hyphex
#endif

\nolig{search string}{spec string}
\keeplig{string}
\uselig{string}
\breaklig

\debugoff
\debugon
\selnoligoff
\selnoligon

\selnoligpackagename#S
\selnoligpackageversion#S
\selnoligpackagedate#S