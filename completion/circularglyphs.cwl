# circularglyphs package
# Matthew Bertucci 2023/10/07 for v0.1.1

#include:tikz
#include:xstring
#include:calc
#include:simplekv

\CircGlyph{text}
\CircGlyph[options%keyvals]{%<text%>}
\CircGlyph*{text}
\CircGlyph*[options%keyvals]{%<text%>}

#keyvals:\CircGlyph,\CircGlyph*
Inline#true,false
Ext#true,false
Color=#%color
#endkeyvals

# not documented
\GenereCircGlyp{arg1}{arg2}#S
\GenereCircGlypAux#S
\CircGlyphChar{arg}#S
\CircGlyphCharAux#S
\CircGlyphAux#S