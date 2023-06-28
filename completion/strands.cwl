# strands package
# Matthew Bertucci 9/21/2021 for v1.1

#include:forarray
#include:ifthen
#include:tikz
#include:xstring
#include:xkeyval

#keyvals:\usepackage/strands#c
backcolor=#%color
bend=%<integer%>
bendbraid=%<integer%>
bendtangle=%<integer%>
braidcross=%<number%>
braidsingcross=%<number%>
braidvirtcross=%<number%>
bulletsize=%<number%>
coverunion=%<number%>
direction=%<number%>
externalize=#0,1
font=%<number%>
gencharposbraid=%<braid generator%>
gencharnegbraid=%<braid generator%>
gencharvirtual=%<braid generator%>
gencharsingular=%<braid generator%>
genchartangle=%<braid generator%>
genchartie=%<braid generator%>
genchartiedtangle=%<braid generator%>
height=%<number%>
labelver=%<number%>
labelhor=%<number%>
norma=%<number%>
normb=%<number%>
normcolor=
nstr=%<integer%>
num=%<integer%>
rotate=%<angle%>
scale=%<factor%>
strwidth=%<number%>
tiebend=%<integer%>
tiebull=#0,1
tiebullsize=%<number%>
tiecolor=#%color
tiesnake#true,false
tiestyle=#solid,dashed,dotted
tiewidth=%<number%>
timeswidth=%<number%>
tkzpic=#0,1
width=%<number%>
#endkeyvals

#ifOption:externalize=1
#include:tikzlibraryexternal
#endif

\vpartition{sorted blocks}
\vpartition[options%keyvals]{sorted blocks}

#keyvals:\vpartition
bend=%<integer%>
bulla=#0,1
bullb=#0,1
bulletends=
floor=%<number%>
font=%<fontsize%>
height=%<number%>
labelver=%<number%>
labelhor=%<number%>
norma=%<number%>
normb=%<number%>
nstr=%<integer%>
reflect=%<integer%>
rotate=%<integer%>
scale=%<factor%>
strwidth=%<number%>
tkzpic=#0,1
type=#0,2,3,4,5
width=%<number%>
#endkeyvals

\arcpartition{sorted blocks}
\arcpartition[options%keyvals]{sorted blocks}

#keyvals:\arcpartition
bend=%<integer%>
bull=#0,1
bulletsize=%<number%>
floor=%<number%>
font=%<fontsize%>
labelver=%<number%>
labelhor=%<number%>
norma=%<number%>
normb=%<number%>
num=%<integer%>
rotate=%<integer%>
scale=%<factor%>
strwidth=%<number%>
tkzpic=#0,1
type=#0,1
width=%<number%>
#endkeyvals

\permutation{images of 1 to n}
\permutation[options%keyvals]{images of 1 to n}

#keyvals:\permutation
bulla=#0,1
bullb=#0,1
bulletends=%<number%>
floor=%<number%>
font=%<fontsize%>
height=%<number%>
labelver=%<number%>
labelhor=%<number%>
norma=%<number%>
normb=%<number%>
nstr=%<integer%>
rotate=%<integer%>
scale=%<factor%>
strwidth=%<number%>
tkzpic=#0,1
type=#0,2,3,4,5
width=%<number%>
#endkeyvals

\tiedpair{permutation}{set partition}
\tiedpair[options%keyvals]{permutation}{set partition}

#keyvals:\tiedpair
above=#0,1
bend=%<integer%>
bulla=#0,1
bullb=#0,1
bulletends=%<number%>
floor=%<number%>
font=%<fontsize%>
height=%<number%>
labelver=%<number%>
labelhor=%<number%>
norma=%<number%>
normb=%<number%>
nstr=%<integer%>
rotate=%<integer%>
scale=%<factor%>
strwidth=%<number%>
tkzpic=#0,1
type=#0,2,3,4,5
width=%<number%>
#endkeyvals

\tie{dots}
\tie[options%keyvals]{dots}

#keyvals:\tie
bend=%<integer%>
bull=#0,1
bulletie=%<number%>
color=#%color
floor=%<number%>
height=%<number%>
snake#true,false
snakeamp=
snakends=
snakelen=
style=#solid,dashed,dotted
tieheight=%<number%>
tiewidth=%<number%>
width=%<number%>
#endkeyvals

\strands{generators}
\strands[options%keyvals]{generators}

#keyvals:\strands
bendbraid=%<integer%>
bendtangle=%<integer%>
bulla=#0,1
bullb=#0,1
bulletends=%<number%>
direction=%<number%>
floor=%<number%>
height=%<number%>
labelver=%<number%>
labelhor=%<number%>
nstr=%<integer%>
rotate=%<integer%>
scale=%<factor%>
strwidth=%<number%>
tiebull=#0,1
tiebullsize=
tiecolor=#%color
tieheight=%<number%>
tiesnake#true,false
tiesnakeamp=
tiesnakends=
tiesnakelen=%<number%>
tiestyle=#solid,dashed,dotted
tiewidth=%<number%>
tkzpic=#0,1
type=#0,2,3,4,5
width=%<number%>
#endkeyvals

\getelem{list}{index}{name}#*
\decoratestrands#*
\decoratestrands[options]#*
\vvpartition{sorted blocks}#*
\vvpartition[options]{sorted blocks}#*
\oldnumstrands#S
\bbackstrands#*
\bbackstrands[options]#*
\lleftstrand#*
\lleftstrand[options]#*
\rrightstrand#*
\rrightstrand[options]#*
\ccrossback#*
\ccrossback[options]#*
\bbraidgen#*
\bbraidgen[options]#*
\ttanglegen#*
\ttanglegen[options]#*
\aaddgen#*
\aaddgen[options]#*
\thelevelscounter#*
\sstrands{generators}#*
\sstrands[options]{generators}#*
