# lettrine package
# Matthew Bertucci 2022/09/26 for v2.30

#include:xkeyval
#include:minifp

#keyvals:\usepackage/lettrine#c
optionsfile=%<filename%>
#endkeyvals

\lettrine{letter}{text%plain}
\lettrine[options%keyvals]{letter}{text%plain}

#keyvals:\lettrine,\usepackage/lettrine#c
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
#endkeyvals

#keyvals:\lettrine
ante=%<text%>
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
\LettrineTestString#*
\LettrineTextFont#*
\LettrineWidth#*
