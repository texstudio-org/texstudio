# scratch3 package
# Matthew Bertucci 1/29/2022 for v0.18

#include:simplekv
#include:tikz
#include:tikzlibraryshapes.misc
#include:tikzlibrarybending

## 2 L'environnement scratch ##
\begin{scratch}
\begin{scratch}[options%keyvals]
\end{scratch}

## 3 Les blocs normaux ##
\blockmove{text}
\blocklook{text}
\blocksound{text}
\blockpen{text}
\blockvariable{text}
\blocklist{text}
\blockevent{text}
\blockcontrol{text}
\blocksensing{text}

## 4 Les ovales ##
\ovalnum{number}
\ovalmove{text}
\ovalmove*{text}
\ovallook{text}
\ovallook*{text}
\ovalsound{text}
\ovalsound*{text}
\ovalpen{text}
\ovalpen*{text}
\ovalvariable{text}
\ovalvariable*{text}
\ovallist{text}
\ovallist*{text}
\ovalcontrol{text}
\ovalcontrol*{text}
\ovalsensing{text}
\ovalsensing*{text}
\ovaloperator{text}
\ovaloperator*{text}
\turnleft
\turnright
\pencolor{color}

## 5 Les blocs de début ##
\blockinit
\blockinitclone
\greenflag

## 6 Les rectangles ##
\selectmenu{text}

## 7 Les losanges et les blocs de test ##
\blockif{test%text}{true-instructions%text}
\blockifelse{test%text}{true-instructions%text}{false-instructions%text}
\booloperator{text}
\boolsensing{text}
\boollist{text}
\boolempty
\boolempty[dimen%l]

## 8 Les blocs de fin ##
\blockstop{text}

## 9 Les blocs de répétition ##
\blockrepeat{text}{instructions}
\blockinfloop{text}{instructions}

## 10 Les blocs de définition ##
\initmoreblocks{text}
\namemoreblocks{text}
\ovalmoreblocks{text}
\blockmoreblocks{text}
\boolmoreblocks{text}

## 11 Bloc invisible ##
\blockspace
\blockspace[coeff]

## 12 Personnalisation ##
\setscratch{options%keyvals}
\setdefaultscratch{options%keyvals}
\resetscratch

#keyvals:\begin{scratch},\setscratch,\setdefaultscratch
else word=%<characters%>
pre text=%<code%>
x sep=##L
y sepsup=##L
y sepinf=##L
line width=##L
loop width=##L
loop height=##L
corner=##L
notch=##L
scale=%<coeff%>
init arcangle=%<degrees%>
init arclength=##L
print#true,false
fill blocks#true,false
fill gray=%<factor%>
contrast=%<integer%>
text color=#%color
flag gray=%<factor%>
line gray=%<factor%>
num blocks#true,false
num sep=##L
num start=%<integer%>
baseline=%<l, c, or <integer>%>
#endkeyvals

\numblock{text%plain}#*

\scrdate#S
\scrname#S
\scrver#S
