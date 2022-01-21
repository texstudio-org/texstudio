# eulerpx package
# Matthew Bertucci 1/18/2022 for v1.3

#include:amsmath
#include:newpxmath

#keyvals:\usepackage/eulerpx#c
sansmath
utf8
#endkeyvals

\mathscr{text%plain}#m
\mathfrak{text%plain}#m

#ifOption:sansmath
\oldrmfamily#*
\oldsffamily#*
#endif

\filedate#S
\fileversion#S