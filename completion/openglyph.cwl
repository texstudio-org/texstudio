# openglyph package
# Matthew Bertucci 2026/10/29 for v0.2.1

#include:iftex
#include:fontspec

\ebag{name}
\gwglyph{name}
\OpenGlyphAlias{new name}{old name}
\OpenGlyphIfExistsTF{name}{true code}{false code}
\OpenGlyphLoad{collection}
\OpenGlyphSequence{name1,name2,...}
\OpenGlyph{name}

\OpenGlyphDeclareEntry{name}{namespace}{hex}#*
\OpenGlyphDeclareFont{namespace}{font file%file}#*
\OpenGlyphDeclare{name}{namespace}{hex}#*