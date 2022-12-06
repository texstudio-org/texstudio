# pas-cours package
# Matthew Bertucci 2/16/2022 for v1.9

#include:xkeyval
#include:xstring
#include:amssymb
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryfadings
#include:enumitem
#include:numprint
#include:fancyvrb
#include:ifplatform
#include:pst-plot
#include:auto-pst-pdf

#keyvals:\usepackage/pas-cours#c
ant
everytoc
noitemstyle
noeffect
notitlebreak
calculs
xcas
#endkeyvals

\begin{ant}#*
\end{ant}#*

defi#B
ex#B
nota#B
rem#B
thm#B
prop#B
demo#B
act#B
meth#B

# from macro-patrons.tex
\patronprismereg
\patronprismereg[options%keyvals]
\pasPatronprismereg[options%keyvals]#*

#keyvals:\patronprismereg,\pasPatronprismereg
n=%<integer%>
r=%<rayon%>
h=%<hauteur%>
pos=
legende#true,false
#endkeyvals

\patronpyramreg
\patronpyramreg[options%keyvals]
\pasPatronpyramreg[options%keyvals]#*

#keyvals:\patronpyramreg,\pasPatronpyramreg
n=%<integer%>
r=%<rayon%>
h=%<hauteur%>
legende#true,false
#endkeyvals

\patroncone
\patroncone[options%keyvals]
\pasPatroncone[options%keyvals]#*

#keyvals:\patroncone,\pasPatroncone
r=%<rayon%>
h=%<hauteur%>
legende#true,false
#endkeyvals

\patroncylindre
\patroncylindre[options%keyvals]
\pasPatroncylindre[options%keyvals]#*

#keyvals:\patroncylindre,\pasPatroncylindre
r=%<rayon%>
h=%<hauteur%>
legende#true,false
#endkeyvals

\patronpave
\patronpave[options%keyvals]
\pasPatronpave[options%keyvals]#*

#keyvals:\patronpave,\pasPatronpave
a=%<number%>
b=%<number%>
c=%<number%>
pos=#1,2,3,4
legende#true,false
codages#true,false
#endkeyvals

# from macro-solides.tex
\prismereg
\prismereg[options%keyvals]
\pasPrismereg[options%keyvals]#*

#keyvals:\prismereg,\pasPrismereg
n=%<integer%>
bordercolor=#%color
incolor=#%color
coefopaq=%<opacity%>
axe#true,false
axecolor=#%color
hauteur=##L
rayon=##L
incl=%<coeff%>
legende#true,false
rotat=%<degrees%>
name#true,false
#endkeyvals

\pyramreg
\pyramreg[options%keyvals]
\pasPyramreg[options%keyvals]#*

#keyvals:\pyramreg,\pasPyramreg
n=%<integer%>
bordercolor=#%color
incolor=#%color
coefopaq=%<opacity%>
centre=%<name%>
poscentre=%<node pos%>
sommet=%<name%>
posommet=%<node pos%>
scalecentre=%<factor%>
axe#true,false
axecolor=#%color
name#true,false
hauteur=##L
rayon=##L
incl=%<coeff%>
legende#true,false
rotat=%<degrees%>
#endkeyvals

\boule
\boule[options%keyvals]
\pasBoule[options%keyvals]#*

#keyvals:\boule,\pasBoule
border#true,false
bordercolor=#%color
incolor=#%color
coefopaq=%<opacity%>
centre=%<name%>
poscentre=%<node pos%>
scale=%<factor%>
name#true,false
legende#true,false
greenwich#true,false
greenwichcolor=#%color
greenwichlegende#true,false
grandcercle#true,false
equateurlegende#true,false
exemplecoord#true,false
exemplecoordcolor=#%color
exemplecoordname=%<name%>
#endkeyvals

\cone
\cone[options%keyvals]
\pasCone[options%keyvals]#*

#keyvals:\cone,\pasCone
bordercolor=#%color
incolor=#%color
incl=%<coeff%>
hauteur=##L
coefopaq=%<opacity%>
rayon=##L
centre=%<name%>
poscentre=%<node pos%>
sommet=%<name%>
posommet=%<node pos%>
scalecentre=%<factor%>
name#true,false
axe#true,false
axecolor=#%color
legende#true,false
#endkeyvals

\cylindre
\cylindre[options%keyvals]
\pasCylindre[options%keyvals]#*

#keyvals:\cylindre,\pasCylindre
bordercolor=#%color
incolor=#%color
incl=%<coeff%>
hauteur=##L
coefopaq=%<opacity%>
rayon=##L
centrehaut=%<name%>
poscentrehaut=%<node pos%>
centrebas=%<name%>
poscentrebas=%<node pos%>
scalecentre=%<factor%>
name#true,false
axe#true,false
axecolor=#%color
legende#true,false
rectgener#true,false
#endkeyvals

\cube
\cube[options%keyvals]
\pasCube[options%keyvals]

#keyvals:\cube,\pasCube
bordercolor=#%color
incolor=#%color
angle=%<degrees%>
scale=%<factor%>
coefopaq=%<opacity%>
prof=%<profondeur%>
name#true,false
legende#true,false
#endkeyvals

# from macro-styles.tex
\env{text}
\env[options%keyvals]{text}
\pasEnv[options%keyvals]{text}#*

\begin{pasbox}
\begin{pasbox}[options%keyvals]
\end{pasbox}

#keyvals:\env,\pasEnv,\begin{pasbox}
degrade#true,false
pluriel#true,false
num#true,false
notitle#true,false
notitlebreak#true,false
endsymb#true,false
toc#true,false
notoc#true,false
effect#true,false
style=#defi,prop,thm,demo,nota,ex,act,rem,meth
name=%<name%>
title=%<title%>
symb=%<symbol%>
#endkeyvals

\breakbox

\chap{title}{subtitle%text}#L1
\chap[options%keyvals]{title}{subtitle%text}#L1
\pasChap[options%keyvals]{title}{subtitle%text}#*L1

#keyvals:\chap,\pasChap
autonum#true,false
num=%<numéro%>
color=#%color
pos=#left,right
nonewpage#true,false
#endkeyvals

\definmot{text}
\itemclass{color}

\begin{prerequis}
\end{prerequis}

\begin{aretenir}
\begin{aretenir}[factor]
\end{aretenir}

\begin{warning}
\begin{warning}[options%keyvals]
\end{warning}

#keyvals:\begin{warning}
scale=%<factor%>
img=%<imagefile%>
margins=##L
draw=#%color
bg#true,false
bgcolor=#%color
#endkeyvals

\begin{attention}
\begin{attention}[factor]
\end{attention}

\bonus{titre%text}
\bonus*{titre%text}

\titreFONT#*
\tocFONT#*
\prerequisBox#*
\imgPrerequis#*
\largeurimgPrerequis#*
\imageBox#*
\largeurimageBox#*
\aretenirBox#*
\attentionBox#*
\thebonus#*

#ifOption:calculs
# from macro-calculs.tex
\begin{ifactors}
\end{ifactors}
\begin{ifactorstable}
\end{ifactorstable}
\begin{fracsimplify}
\end{fracsimplify}
\begin{exprsimplify}
\end{exprsimplify}

\graphsuite
\graphsuite[options%keyvals]

#keyvals:\graphsuite
xmin=%<number%>
xmax=%<number%>
ymin=%<number%>
ymax=%<number%>
nmax=%<number%>
grid#true,false
gridcolor=#%color
gridstyle={%<TikZ options%>}
gridxstep=%<number%>
gridystep=%<number%>
nograd#true,false
function={%<function%>}
colorfunction=#%color
u=%<first value%>
colorconstruction=#%color
styleconstruction={%<TikZ options%>}
#endkeyvals

\begin{xcas}
\end{xcas}

\executGiac{code}#*
#endif

#ifOption:xcas
# from macro-calculs.tex
# from macro-calculs.tex
\begin{ifactors}
\end{ifactors}
\begin{ifactorstable}
\end{ifactorstable}
\begin{fracsimplify}
\end{fracsimplify}
\begin{exprsimplify}
\end{exprsimplify}

\graphsuite
\graphsuite[options%keyvals]

#keyvals:\graphsuite
xmin=%<number%>
xmax=%<number%>
ymin=%<number%>
ymax=%<number%>
nmax=%<number%>
grid#true,false
gridcolor=#%color
gridstyle={%<TikZ options%>}
gridxstep=%<number%>
gridystep=%<number%>
nograd#true,false
function={%<function%>}
colorfunction=#%color
u=%<first value%>
colorconstruction=#%color
styleconstruction={%<TikZ options%>}
#endkeyvals

\begin{xcas}
\end{xcas}

\executGiac{code}#*
#endif
