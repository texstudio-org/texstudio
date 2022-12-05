# cesenaexam class
# Matthew Bertucci 2022/07/21 for v0.2

#include:etoolbox
#include:pgfkeys
#include:pgfopts
#include:geometry
#include:graphicx
#include:tikz
#include:circuitikz
#include:tikzlibraryintersections
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibrarycalc
#include:tikzlibrarythrough
#include:tikzlibrarybabel
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarybackgrounds
#include:fancyhdr
#include:titlesec

#keyvals:\documentclass/cesenaexam#c
noversion
boxed
times
left=##L
right=##L
top=##L
bottom=##L
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:times
#include:newtxtext
#include:newtxmath
#endif

\examsection{title}{italic text%text}#L2
\examsection*{title}{italic text%text}#L2
\boxempty
\boxcheck
\examparts{content%text}
\maketitle{surname}{name}{id}{signature}{N}
\maketitle[options%keyvals]{surname}{name}{id}{signature}{N}
\maketitle*{surname}{name}{id}{signature}{N}#S
\maketitle*[options%keyvals]{surname}{name}{id}{signature}{N}#S
#keyvals:\maketitle,\maketitle*
textboxheight=##L
whiteboxheight=##L
textboxone={%<content%>}
textboxtwo={%<content%>}
textboxthree={%<content%>}
textboxfour={%<content%>}
#endkeyvals
\examtwoblocks{length1%l}{length2%l}{block1%text}{block2%text}
\examtwoblockstop{length1%l}{length2%l}{block1%text}{block2%text}
\examoneblocktop{length}{block%text}

# not documented
\sectionfont#*
\cesenaexamversion#S
\boxlen#S
\lastboxlen#S
\minheighttypebox#S
