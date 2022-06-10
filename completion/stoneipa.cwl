# stoneipa package
# Matthew Bertucci 2022/06/09 for v0.8

#include:fontspec
#include:newunicodechar
#include:pdftexcmds
#include:kvoptions

#keyvals:\usepackage/stoneipa#c
fontname=%<font name%>
scfontname=%<font name%>
phoneticfontname=%<font name%>
alternatefontname=%<font name%>
noalternatescaling#true,false
#endkeyvals

\sipafont
\sipaalternatefont
\sipachoosephoneticchar{char1}{char2}
\sipachoosealternatechar{char1}{char2}
\sipasetup{glyph}{char}
\sipaalternatesetup{glyph}{char}