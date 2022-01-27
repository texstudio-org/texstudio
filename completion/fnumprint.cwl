# fnumprint package
# Matthew Bertucci 10/5/2021 for v1.1a

#include:xifthen
#include:numprint

#keyvals:\usepackage/fnumprint#c
german
ngerman
english
USenglish
american
UKenglish
british
canadian
australian
newzealand
#endkeyvals

#ifOption:german
#include:zahl2string
\fnumprintc[eins]{counter}
\fnumprint[eins]{number}
#endif

#ifOption:ngerman
#include:zahl2string
\fnumprintc[eins]{counter}
\fnumprint[eins]{number}
#endif

\fnumprintc{counter}
\fnumprint{number}
