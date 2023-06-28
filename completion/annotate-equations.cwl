# annotate-equations package
# Matthew Bertucci 2023/02/16 for v0.2.0

#include:ifluatex
#include:tikz
#include:tikzlibrarybackgrounds
#include:tikzlibraryshapes
#include:tikzlibrarytikzmark
#include:tikzlibrarycalc
#include:xcolor
#include:l3keys2e

\eqnmarkbox{node name}{equation terms}#m
\eqnmarkbox[color]{node name}{equation terms}#m
\eqnmark{node name}{equation terms}#m
\eqnmark[color]{node name}{equation terms}#m

\annotate{annotate keys%keyvals}{node names}{text}
\annotate[TikZ options]{annotate keys%keyvals}{node names}{text}
\annotatetwo{annotate keys%keyvals}{node name1}{node name2}{text}
\annotatetwo[TikZ options]{annotate keys%keyvals}{node name1}{node name2}{text}

#keyvals:\annotate,\annotatetwo
above
below
right
left
label above
label below
#endkeyvals

\addvalue{node name}{color}#*
\EAlabelanchor#*
\EAmarkanchor#*
\EAwesteast#*
\EAxshift#*
\eqnannotateCurrentNode#*
\eqnannotationfont#*
\eqnannotationstrut#*
\eqncolor{color}{math}#*m
\eqnhighlight{color}{math}#*m
\eqnhighlightcolorbox{color}{math}#*m
\eqnhighlightfbox{color}{math}#*m
\eqnhighlightheight#*
\eqnhighlightshade#*
\extractfirst{arg1}{arg2}#*
\myEAcolor#S
\myEAmarkOn#S
\myEAmarks#S
\myEAmarkTwo#S
\myEAtext#S
\myEAxshift#S
\swapNorthSouth{anchor}#*
\swapWestEast{anchor}#*
\theeqnannotatenode#*
\usevalue{node name}#*
