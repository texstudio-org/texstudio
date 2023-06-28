# unitconv package
# Matthew Bertucci 12/12/2021 for v0.1

#include:iftex
#include:luacode

\convTeXLength{TeX length}
\convTeXLength[unit%keyvals]{TeX length}
\convTeXLength[unit%keyvals][digits]{TeX length}
\convTeXLength*{TeX length}
\convTeXLength*[unit%keyvals]{TeX length}
\convTeXLength*[unit%keyvals][digits]{TeX length}

\convLength[unit1%keyvals]{value}[unit2]
\convLength[unit1%keyvals][digits]{value}[unit2]
\convLength*[unit1%keyvals]{value}[unit2]
\convLength*[unit1%keyvals][digits]{value}[unit2]

#keyvals:\convTeXLength,\convTeXLength*,\convLength,\convLength*
bp
cc
cm
dd
em
ex
in
km
m
mm
mu
pc
pt
px
sp
#endkeyvals