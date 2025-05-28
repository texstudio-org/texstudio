# wordle package
# Matthew Bertucci 2025/05/28 for v0.3.0

#include:xcolor
#include:tikz

## English version
\begin{wordle}{solution%text}
\begin{wordle}{solution%text}[TikZ commands]
\begin{wordle}[keyvals]{solution%text}
\begin{wordle}[keyvals]{solution%text}[TikZ commands]
\end{wordle}
\WordleSetup{keyvals}

#keyvals:\begin{wordle},\WordleSetup,\usepackage/wordle#c
style=#sutom,standard,hard
colours={%<color1,color2,...%>}
colors={%<color1,color2,...%>}
absent colour=#%color
absent color=#%color
present colour=#%color
present color=#%color
correct colour=#%color
correct color=#%color
borders={%<absent color,present color,correct color,empty color%>}
frames={%<absent bool,present bool,correct bool,empty bool%>}
shapes={%<absent shape,present shape,correct shape,empty shape%>}
text={%<absent color,present color,correct color,empty color%>}
noalign
align
font=%<font commands%>
rounded=##L
separation=##L
scale=%<factor%>
size=##L
thickness=##L
tile style={%<TikZ keys%>}
letters
noletters
strict#true,false
rows=%<integer%>
case sensitive#true,false
natural case
lower case
upper case
tikz={%<TikZ keys%>}
name=%<name%>
#endkeyvals

## French version
\begin{GrilleSutom}{solution%text}
\begin{GrilleSutom}{solution%text}[TikZ commands]
\begin{GrilleSutom}[keyvals]{solution%text}
\begin{GrilleSutom}[keyvals]{solution%text}[TikZ commands]
\end{GrilleSutom}
\ParamsSutom{keyvals}

#keyvals:\begin{GrilleSutom},\ParamsSutom
Style=#sutom,standard,hard
Couleurs={%<color1,color2,...%>}
couleur absent=#%color
couleur present=#%color
couleur correct=#%color
CouleurBordures={%<absent color,present color,correct color,empty color%>}
Cadres={%<absent bool,present bool,correct bool,empty bool%>}
Formes={%<absent shape,present shape,correct shape,empty shape%>}
CouleurLettres={%<absent color,present color,correct color,empty color%>}
nonalign
align
Police=%<font commands%>
Arrondi=##L
Separation=##L
Echelle=%<factor%>
Taille=##L
Epaisseur=##L
Lettres
NonLettres
Strict#true,false
Lignes=%<integer%>
case sensitive#true,false
natural case
lower case
upper case
tikz={%<TikZ keys%>}
name=%<name%>
#endkeyvals
