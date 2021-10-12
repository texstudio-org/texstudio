# fnumprint package
# Matthew Bertucci 10/5/2021 for v1.1a

#include:xifthen
#include:numprint

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