# tikzsymbols package
# Matthew Bertucci 10/17/2021 for v4.12

#include:tikz
#include:xcolor
#include:xspace
#include:l3keys2e
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarytrees

\tikzsymbolsset{keyvals}

#keyvals:\tikzsymbolsset,\usepackage/tikzsymbols#c
draft#true,false
final#true,false
tree=#true,false,on,off
after-symbol=%<code%>
global-scale=%<number%>
symbol-scale={%<sym1=num1,sym2=num2,...%>}
append-style={%<TikZ keys%>}
usebox#true,false
baseline#true,false
remember-picture#true,false
#endkeyvals

#keyvals:\usepackage/tikzsymbols#c
marvosym#true,false
prefix=%<string%>
#endkeyvals

\tikzsymbolsuse{symbol name}

\Kochtopf
\pot
\Bratpfanne
\fryingpan
\Schneebesen
\eggbeater
\Sieb
\sieve
\Purierstab
\blender
\Dreizack
\trident
\Backblech
\bakingplate
\Ofen
\oven
\Pfanne
\pan
\Herd
\cooker
\Saftpresse
\squeezer
\Schussel
\bowl
\Schaler
\peeler
\Reibe
\grater
\Flasche
\bottle
\Nudelholz
\rollingpin
\Knoblauchpresse
\garlicpress
\Kochtopf[scale]
\pot[scale]
\Bratpfanne[scale]
\fryingpan[scale]
\Schneebesen[scale]
\eggbeater[scale]
\Sieb[scale]
\sieve[scale]
\Purierstab[scale]
\blender[scale]
\Dreizack[scale]
\trident[scale]
\Backblech[scale]
\bakingplate[scale]
\Ofen[scale]
\oven[scale]
\Pfanne[scale]
\pan[scale]
\Herd[scale]
\cooker[scale]
\Saftpresse[scale]
\squeezer[scale]
\Schussel[scale]
\bowl[scale]
\Schaler[scale]
\peeler[scale]
\Reibe[scale]
\grater[scale]
\Flasche[scale]
\bottle[scale]
\Nudelholz[scale]
\rollingpin[scale]
\Knoblauchpresse[scale]
\garlicpress[scale]

\Smiley
\Sadey
\Neutrey
\Annoey
\Laughey
\Winkey
\oldWinkey
\Sey
\Xey
\Innocey
\wInnocey
\Cooley
\Tongey
\Nursey
\Vomey
\Walley
\rWalley
\Cat
\Ninja
\Sleepey
\Maskey
\NiceReapey
\Smiley[scale][color]
\Sadey[scale][color]
\Neutrey[scale][color]
\Changey[scale][color]{mood}
\cChangey[scale][color1%color][color2%color][color3%color]{mood}
\Annoey[scale][color]
\Laughey[scale][color][mouth color%color]
\Winkey[scale][color]
\oldWinkey[scale][color]
\Sey[scale][color]
\Xey[scale][color]
\Innocey[scale][color][halo color%color]
\wInnocey[scale]
\Cooley[scale][color]
\Tongey[scale][color][tongue color%color]
\Nursey[scale][color][cross color%color]
\Vomey[scale][color][vomit color%color]
\Walley[scale][color][wall color%color]
\rWalley[scale][color][wall color%color]
\Cat[scale]
\SchrodingersCat[scale]{case}
\Ninja[scale][color][headband color%color][eye color%color]
\Sleepey[scale][color][cap color%color][star color%color]
\Maskey[scale][color][mask color%color]
\NiceReapey[scale]

\dSmiley
\dSadey
\dNeutrey
\dAnnoey
\dLaughey
\dWinkey
\dSey
\dXey
\dInnocey
\dCooley
\dNinja
\drWalley
\dWalley
\dVomey
\dNursey
\dTongey
\dSleepey
\olddWinkey
\dSmiley[scale][color]
\dSadey[scale][color]
\dNeutrey[scale][color]
\dChangey[scale][color]{mood}
\dcChangey[scale][color1%color][color2%color][color3%color]{mood}
\dAnnoey[scale][color]
\dLaughey[scale][color][mouth color%color]
\dWinkey[scale][color]
\dSey[scale][color]
\dXey[scale][color]
\dInnocey[scale][color][halo color%color]
\dCooley[scale][color]
\dNinja[scale][color][headband color%color][eye color%color]
\drWalley[scale][color][wall color%color]
\dWalley[scale][color][wall color%color]
\dVomey[scale][color][vomit color%color]
\dNursey[scale][color][cap color%color][cross color%color]
\dTongey[scale][color][tongue color%color]
\dSleepey[scale][color][cap color%color][star color%color]
\olddWinkey[scale]

\Strichmaxerl
\Heart
\dHeart
\Candle
\Fire
\Coffeecup
\Chair
\Bed
\Tribar
\Moai
\Snowman
\Strichmaxerl[scale][left arm][right arm][left leg][right leg]
\Heart[scale][color]
\dHeart[scale][color]
\Candle[scale]
\Fire[scale]
\Coffeecup[scale]
\Chair[scale]
\Bed[scale]
\Tribar[scale][color1%color][color2%color][color3%color]
\Moai[scale]
\Snowman[scale]

\BasicTree{trunkcolor%color}{leafcolor1%color}{leafcolor2%color}{leaf}
\Springtree
\Summertree
\Autumntree
\Wintertree
\WorstTree
\BasicTree[scale]{trunkcolor%color}{leafcolor1%color}{leafcolor2%color}{leaf}
\Springtree[scale]
\Summertree[scale]
\Autumntree[scale]
\Wintertree[scale]
\WorstTree[scale]

\tikzsymbolsdefinesymbol{symbol name}{args}{code}
\tikzsymbolsprovideandusesavebox{box name}{code}
\tikzsymbolssetscaleabs{dimen%l}
\tikzsymbolsscaleabs
