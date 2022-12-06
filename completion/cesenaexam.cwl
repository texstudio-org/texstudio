# cesenaexam package
# Matthew Bertucci 2022/07/21 for v0.2

#include:etoolbox
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
#include:titlesec

#keyvals:\usepackage/cesenaexam#c
boxed
#endkeyvals

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
\boxlen#S
\cesenaexamversion#S
\lastboxlen#S
\minheighttypebox#S
