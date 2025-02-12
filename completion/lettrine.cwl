# lettrine package
# Matthew Bertucci 2025/02/03 for v2.80

#keyvals:\usepackage/lettrine#c
optionsfile=%<filename%>
#endkeyvals

\lettrine{letter}{text%plain}
\lettrine[options%keyvals]{letter}{text%plain}

#keyvals:\lettrine,\usepackage/lettrine#c,\LettrineOptionsFor
lines=%<integer%>
depth=%<integer%>
lhang=%<decimal%>
loversize=%<decimal%>
lraise=%<decimal%>
findent=##L
nindent=##L
slope=##L
image#true,false
grid#true,false
nextpage#true,false
novskip=##L
realheight#true,false
refstring
refstring=%<string%>
#endkeyvals

#keyvals:\lettrine,\LettrineOptionsFor
ante=%<text%>
viewport=%<llx lly urx ury%>
#endkeyvals

\DefaultFindent#*
\DefaultLhang#*
\DefaultLoversize#*
\DefaultLraise#*
\DefaultNindent#*
\DefaultOptionsFile#*
\DefaultSlope#*
\DiscardVskip#*
\LettrineDepth#*
\theDefaultLines#*
\theDefaultDepth#*
\LettrineFont#*
\LettrineFontHook#*
\LettrineHeight#*
\ifLettrineImage#*
\LettrineImagetrue#S
\LettrineImagefalse#S
\ifLettrineOnGrid#*
\LettrineOnGridtrue#S
\LettrineOnGridfalse#S
\LettrineOptionsFor{letter}{options%keyvals}#*
\ifLettrineRealHeight#*
\LettrineRealHeightfalse#S
\LettrineRealHeighttrue#S
\LettrineSecondString#*
\LettrineTestString#*
\LettrineTextFont#*
\LettrineWidth#*
\ifLettrineMoveAtEOP#*
\LettrineMoveAtEOPtrue#S
\LettrineMoveAtEOPfalse#S
