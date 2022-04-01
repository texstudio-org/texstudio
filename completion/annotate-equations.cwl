# annotate-equations package
# Matthew Bertucci 4/1/2022 for v0.1.0

#include:ifluatex
#include:tikz
# loads backgrounds, arrows, shapes, tikzmark, and calc tikzlibraries
#include:xcolor
#include:expl3
#include:l3keys2e
#include:xparse

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
\eqnannotationtext{text}#*
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

# from tikzmark library v1.10
\tikzmark{name}
\tikzmark[drawing command]{name}
\tikzmark{name}{coordinate}
\pgfmark{name}
\iftikzmark{name}{true}{false}
\iftikzmarkexists{name}
\iftikzmarkoncurrentpage{name}
\iftikzmarkonpage{name}{page}
\tikzmarknode{name}{contents}
\tikzmarknode[options]{name}{contents}
\subnode{name}{contents}
\subnode[options]{name}{contents}
\usetikzmarklibrary{library}#*

#keyvals:\tikzset#c,\begin{tikzpicture}#c,\node#c
check picture id
if picture id={%<name%>}{%<true%>}{%<false%>}
if tikzmark on current page={%<name%>}{%<true%>}{%<false%>}
if tikzmark on page={%<name%>}{%<page%>}{%<true%>}{%<false%>}
maybe define node=
next page vector
next page=#above,below,left,right,ignore
restore nodes from file=%<file name%>
restore nodes from list=%<name%>
save node
save nodes to file
save picture id=%<name%>
set node group=%<name%>
set saved nodes file name=%<file name%>
tikzmark prefix=%<prefix%>
tikzmark suffix=%<suffix%>
transform saved nodes
#endkeyvals