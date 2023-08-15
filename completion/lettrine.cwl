# lettrine package
# Matthew Bertucci 2023/08/14 for v2.52

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
\LettrineImagetrue#*
\LettrineImagefalse#*
\ifLettrineOnGrid#*
\LettrineOnGridtrue#*
\LettrineOnGridfalse#*
\LettrineOptionsFor{letter}{options%keyvals}#*
\ifLettrineRealHeight#*
\LettrineRealHeightfalse#*
\LettrineRealHeighttrue#*
\LettrineSecondString#*
\LettrineTestString#*
\LettrineTextFont#*
\LettrineWidth#*
