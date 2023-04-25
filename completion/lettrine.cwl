# lettrine package
# Matthew Bertucci 2023/04/18 for v2.3

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
#endkeyvals

#keyvals:\lettrine,\LettrineOptionsFor
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
\LettrineFont#*
\LettrineFontHook#*
\LettrineHeight#*
\LettrineImage#*
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
