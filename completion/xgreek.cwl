# xgreek package
# Matthew Bertucci 2022/08/29 for v3.1.0

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
#include:listings
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
