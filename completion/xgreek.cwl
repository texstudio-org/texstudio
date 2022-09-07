# xgreek package
# Matthew Bertucci 2022/09/07 for v3.2.0

#keyvals:\usepackage/xgreek#c
monogreek
polygreek
ancientgreek
stigma
noindentfirst
nonumeralsign
listings
#endkeyvals

#ifOption:listings
#include:xelistings
#endif

\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*

\anwtonos
\katwtonos
\koppa
\sampi
\Digamma
\ddigamma
\anoteleia
\euro
\permill
\stigma

\greeknumeral{number}
\Greeknumeral{number}
\atticnum{number}

\setlanguage{language%keyvals}
#keyvals:\setlanguage#c
monogreek
polygreek
ancientgreek
american
#endkeyvals

\grtoday
\Grtoday
