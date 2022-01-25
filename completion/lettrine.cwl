# lettrine package
# Matthew Bertucci 8/30/2021 for v2.23

#include:keyval
#include:minifp

\lettrine{letter}{text%plain}
\lettrine[options%keyvals]{letter}{text%plain}

#keyvals:\lettrine
lines=%<integer%>
depth=%<integer%>
lhang=%<decimal%>
loversize=%<decimal%>
lraise=%<decimal%>
findent=##L
nindent=##L
slope=##L
ante=%<text%>
image#true,false
grid#true,false
novskip=##L
realheight#true,false
refstring
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
\LettrineFontHook#*
\LettrineHeight#*
\LettrineImage#*
\ifLettrineImage#*
\LettrineImagetrue#*
\LettrineImagefalse#*
\ifLettrineOnGrid#*
\LettrineOnGridtrue#*
\LettrineOnGridfalse#*
\ifLettrineRealHeight#*
\LettrineRealHeightfalse#*
\LettrineRealHeighttrue#*
\LettrineSecondString#*
\ifLettrineSelfRef#*
\LettrineSelfReftrue#*
\LettrineSelfReffalse#*
\LettrineTestString#*
\LettrineTextFont#*
\LettrineWidth#*
