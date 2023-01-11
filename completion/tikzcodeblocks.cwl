# tikzcodeblocks package
# Matthew Bertucci 12/15/2021 for v0.13

#include:adjustbox
#include:xcolor
#include:colortbl
#include:fontawesome
#include:tikz
#include:longtable
#include:tikzlibrarymatrix
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibrarycalc
#include:tikzlibraryshapes
#include:tikzlibrarybackgrounds
#include:tikzlibrarymath
#include:tikzlibrarytrees
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing
#include:translations
#include:xspace
#include:ifthen

#keyvals:\usepackage/tikzcodeblocks#c
print#true,false
#endkeyvals

#keyvals:\begin{tikzpicture}#c
codeblocks
openroberta
eckig
nocolor
umgebung
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\node#c,\intbox#c,\stringbox#c,\boolbox#c,\wenndann#c,\wenndannsonst#c,\schleife#c,\ifthenblocks#c,\ifthenelseblocks#c,\loopblocks#c
grundlage
eingabe
schleife
logik
musik
led
platzhalter
mathe
funk
motor
zeichenkette
spiel
bild
pins
konsole
steuerung
bluetooth
start
aktion
sensor
kontrolle
liste
farbe
bild
variablen
funktion
nachricht
unter={%<node%>}{%<x-factor%>}{%<y-factor%>}
under={%<node%>}{%<x-factor%>}{%<y-factor%>}
robertashape
puzzleteil
keinezacken
pinlow
pinhigh
nopins
square
puzzlepiece
boden
floor
#endkeyvals

\setcolor{name%specialDef}{hex color code}#s#%color

grundlagen-color#B
eingaben-color#B
musik-color#B
led-color#B
schleifen-color#B
logik-color#B
platzhalter-color#B
mathematik-color#B
funk-color#B
motoren-color#B
text-color#B
spiel-color#B
bilder-color#B
pins-color#B
konsole-color#B
steuerung-color#B
bluetooth-color#B
int-color#B
string-color#B
boolean-color#B
color-color#B
led-bg-color#B
led-on-color#B

\dropdown{text}
\intbox{text}
\intbox[options%keyvals]{text}
\stringbox{text}
\stringbox[options%keyvals]{text}
\boolbox{text}
\boolbox[options%keyvals]{text}

\bild{content}
\bild[scale]{content}
\emptyled
\fullled
\X
\0

\wenndann{text}{then node code}{node name}
\wenndann[options%keyvals]{text}{then node code}{node name}
\wenndannsonst{text}{then node code}{else node code}{node name}
\wenndannsonst[options%keyvals]{text}{then node code}{else node code}{node name}
\schleife{text}{then node code}{else node code}{node name}
\schleife[options%keyvals]{text}{then node code}{else node code}{node name}

\ifthenblocks{text}{then node code}{node name}
\ifthenblocks[options%keyvals]{text}{then node code}{node name}
\ifthenelseblocks{text}{then node code}{else node code}{node name}
\ifthenelseblocks[options%keyvals]{text}{then node code}{else node code}{node name}
\loopblocks{text}{then node code}{else node code}{node name}
\loopblocks[options%keyvals]{text}{then node code}{else node code}{node name}

\einruecken{nodes}
\moveindent{nodes}

\usb
\farbe{color}

\setupquotes#*
\myspace#*
\myshift#*
\blockhspace#*
\blockhspaceoben#*
\blockhspaceunten#*
\blockvspace#*
\dreieckseite#*
