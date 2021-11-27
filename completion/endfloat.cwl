# endfloat package
# Matthew Bertucci 11/26/2021 for v2.7

#include:keyval
#include:rotating

#keyvals:\usepackage/endfloat#c
nofiglist
notablist
nolists
figlist
tablist
lists
nofighead
notabhead
noheads
fighead
tabhead
heads
markers
nomarkers
tablesfirst
figuresfirst
tablesonly
figuresonly
notables
nofigures
disable
#endkeyvals

\tableplace#*
\figureplace#*
\floatplace#*
\efloatheading#*

\AtBeginFigures
\AtBeginTables
\AtBeginDelayedFloats

\addtodelayedfloat{float type}{code}
\addtodelayedfloat*{float type}{code}

\processdelayedfloats

\efloatpreamble#*
\efloatseparator#*
\efloatpostamble#*
\efloattype#*

\efloatbegin#*
\efloatend#*
\efloatbeginlist#*
\efloatendlist#*

\DeclareDelayedFloatFlavor{envname}{float type}
\DeclareDelayedFloatFlavour{envname}{float type}#S
\DeclareDelayedFloatFlavor*{envname}{float type}
\DeclareDelayedFloatFlavour*{envname}{float type}#S

\DeclareDelayedFloat{envname}{heading}
\DeclareDelayedFloat{envname}[file ext]{heading}

\SetupDelayedFloat{float type}{options%keyvals}

#keyvals:\SetupDelayedFloat
nolist
list
nohead
head
#endkeyvals

\dofiglist#*
\dotablist#*
\markersintext#*
\nomarkersintext#*
\nofiglist#*
\notablist#*
\processotherdelayedfloats#*
\thepostfig#*
\thepostfigure#*
\theposttable#*
\theposttable#*

\docdate#S
\filedate#S
\filename#S
\fileversion#S