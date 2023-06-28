# flexipage package
# Matthew Bertucci 2022/10/07 for v1.01

#include:l3keys2e
#include:calc
#include:fp
#include:ifoddpage
#include:graphics
#include:mparhack
#include:etoolbox
#include:fancyhdr

#keyvals:\usepackage/flexipage#c
binding=##L
inner=##L
outer=##L
top=##L
bot=##L
marginparsep=##L
paperheight=##L
paperwidth=##L
outerbleed=##L
innerbleed=##L
grid=%<number%>
marginalgrid=%<number%>
show
NoFixMargin
headsep=##L
headheight=##L
footskip=##L
extrafirstfoot=##L
fancyhdrOff
a4paper
a5paper
b4paper
b5paper
c4paper
c5paper
b4jpaper
b5jpaper
letterpaper
legalpaper
executivepaper
10x8paper
US-Trade
UK-B-Format
US-B-Format
UK-Royal
Quarto
Octavo
CrownQuarto
Demi
#endkeyvals

#ifOption:show
#include:eso-pic
#endif

\NewMarginPage{marginalgrid}
\NewMarginPage<parsep%l>{marginalgrid}
\NewMarginPage[grid]{marginalgrid}
\NewMarginPage[grid]<parsep%l>{marginalgrid}
\NewFullPage
\OldMarginPage
\ResetFlexiPage
\begin{Landscape}
\end{Landscape}
\begin{landscape}
\end{landscape}
\Landscape#S
\endLandscape#S
\landscape#S
\endlandscape#S

# not documented
\IfNoValueOrEmptyTF{arg}{true}{false}#*
\fleximarginparsep#*
\marginparsepeven#*
\marginparsepodd#*
\patch#S
\patcherr#S
\patchok#S
