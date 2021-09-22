# strands package
# Matthew Bertucci 9/21/2021 for v1.1

#include:forarray
#include:tikz
#include:xfp
#include:xstring

\vpartition{sorted blocks}
\vpartition[options%keyvals]{sorted blocks}

#keyvals:\vpartition
bend=%<integer%>
bulla=#0,1
bullb=#0,1
bulletends=
floor=
font=%<fontsize%>
height=
labelver=
labelhor=
norma=
normb=
nstr=%<integer%>
reflect=%<integer%>
rotate=%<integer%>
scale=
strwidth=
tkzpic=#0,1
type=#0,2,3,4,5
width=
#endkeyvals

\arcpartition{sorted blocks}
\arcpartition[options%keyvals]{sorted blocks}

#keyvals:\arcpartition
bend=%<integer%>
bull=#0,1
bulletsize=
floor=
font=%<fontsize%>
labelver=
labelhor=
norma=
normb=
num=%<integer%>
rotate=%<integer%>
scale=
strwidth=
tkzpic=#0,1
type=#0,1
width=
#endkeyvals

\permutation{images of 1 to n}
\permutation[options%keyvals]{images of 1 to n}

#keyvals:\permutation
bulla=#0,1
bullb=#0,1
bulletends=
floor=
font=%<fontsize%>
height=
labelver=
labelhor=
norma=
normb=
nstr=%<integer%>
rotate=%<integer%>
scale=
strwidth=
tkzpic=#0,1
type=#0,2,3,4,5
width=
#endkeyvals

\tiedpair{permutation}{set partition}
\tiedpair[options%keyvals]{permutation}{set partition}

#keyvals:\tiedpair
above=#0,1
bend=%<integer%>
bulla=#0,1
bullb=#0,1
bulletends=
floor=
font=%<fontsize%>
height=
labelver=
labelhor=
norma=
normb=
nstr=%<integer%>
rotate=%<integer%>
scale=
strwidth=
tkzpic=#0,1
type=#0,2,3,4,5
width=
#endkeyvals

\tie{dots}
\tie[options%keyvals]{dots}

#keyvals:\tie
bend=%<integer%>
bull=#0,1
bulletie=
color=#%color
floor=
height=
snake#true,false
snakeamp=
snakends=
snakelen=
style=#solid,dashed,dotted
tieheight=
tiewidth=
width=
#endkeyvals

\strands{generators}
\strands[options%keyvals]{generators}

#keyvals:\strands
bendbraid=%<integer%>
bendtangle=%<integer%>
bulla=#0,1
bullb=#0,1
bulletends=
direction=
floor=
height=
labelver=
labelhor=
nstr=%<integer%>
rotate=%<integer%>
scale=
strwidth=
tiebull=#0,1
tiebullsize=
tiecolor=#%color
tieheight=
tiesnake=
tiesnakeamp=
tiesnakends=
tiesnakelen=
tiestyle=#solid,dashed,dotted
tiewidth=
tkzpic=#0,1
type=#0,2,3,4,5
width=
#endkeyvals
