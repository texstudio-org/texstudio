# dhucs-setspace package
# Matthew Bertucci 2022/05/04 for v0.11

#include:setspace

#keyvals:\usepackage/dhucs-setspace#c
nofloatspacing
noquotespacing
hangul
adjustfootnotesep
adjustverbatim
# options passed to setspace
nodisplayskipstretch
singlespacing
onehalfspacing
doublespacing
#endkeyvals

\SetHangulspace{factor1}{factor2}
\SetHangulVerbatimSpace{factor}
\hangulspacing
\hangulfspacing
\hangulverbspacing

\ucsfninterwordhook#*
\filedate#S
\filename#S
\fileversion#S