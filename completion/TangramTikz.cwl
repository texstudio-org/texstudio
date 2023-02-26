# TangramTikz package
# Matthew Bertucci 2023/02/26 for v0.1.5

#include:tikz
#include:simplekv
#include:xstring
#include:listofitems
#include:tikzlibrarycalc
#include:tikzlibraryshapes.geometric

\begin{EnvTangramTikz}#\pictureHighlight
\begin{EnvTangramTikz}[options%keyvals]
\begin{EnvTangramTikz}[options%keyvals]<TikZ options>
\end{EnvTangramTikz}
\TangramTikz{tangram name}
\TangramTikz<TikZ options>{tangram name}
\TangramTikz[options%keyvals]{tangram name}
\TangramTikz[options%keyvals]<TikZ options>{tangram name}

#keyvals:\begin{EnvTangramTikz},\TangramTikz
Puzzle#true,false
Correction#true,false
Color=#%color
Couleur=#%color
ColorCorrection#true,false
CorrectionCouleur#true,false
ColorList={%<color1,color2,...%>}
ListeCouleurs={%<couleur1,couleur2,...%>}
Sep=##L
#endkeyvals

\PieceTangram[options%keyvals](x,y){piece name}
\PieceTangram[options%keyvals]<TikZ options>(x,y){piece name}

#keyvals:\PieceTangram#c
TangPuzz
TangPuzz={%<color%>}
TangSol
TangSol={%<color%>}
#endkeyvals

# not documented
\TangramSquare#S
\TangramSquare[TikZ options]#S
\TangramSquare*#S
\TangramSquare*[TikZ options]#S
\TangramPinguin#S
\TangramPinguin[TikZ options]#S
\TangramPinguin*#S
\TangramPinguin*[TikZ options]#S
\TangramBoat#S
\TangramBoat[TikZ options]#S
\TangramBoat*#S
\TangramBoat*[TikZ options]#S
\TangramHome#S
\TangramHome[TikZ options]#S
\TangramHome*#S
\TangramHome*[TikZ options]#S
\TangramFirTree#S
\TangramFirTree[TikZ options]#S
\TangramFirTree*#S
\TangramFirTree*[TikZ options]#S
\TangramCat#S
\TangramCat[TikZ options]#S
\TangramCat*#S
\TangramCat*[TikZ options]#S
\TangramSwan#S
\TangramSwan[TikZ options]#S
\TangramSwan*#S
\TangramSwan*[TikZ options]#S
\TangramDuck#S
\TangramDuck[TikZ options]#S
\TangramDuck*#S
\TangramDuck*[TikZ options]#S
\TangramPyramid#S
\TangramPyramid[TikZ options]#S
\TangramPyramid*#S
\TangramPyramid*[TikZ options]#S
\TangramRocket#S
\TangramRocket[TikZ options]#S
\TangramRocket*#S
\TangramRocket*[TikZ options]#S
\TangramCandle#S
\TangramCandle[TikZ options]#S
\TangramCandle*#S
\TangramCandle*[TikZ options]#S
\TangramShirt#S
\TangramShirt[TikZ options]#S
\TangramShirt*#S
\TangramShirt*[TikZ options]#S
\TangramFish#S
\TangramFish[TikZ options]#S
\TangramFish*#S
\TangramFish*[TikZ options]#S
\TangramSailboat#S
\TangramSailboat[TikZ options]#S
\TangramSailboat*#S
\TangramSailboat*[TikZ options]#S
\TangramKangaroo#S
\TangramKangaroo[TikZ options]#S
\TangramKangaroo*#S
\TangramKangaroo*[TikZ options]#S
\TangramDog#S
\TangramDog[TikZ options]#S
\TangramDog*#S
\TangramDog*[TikZ options]#S
\TangramRabbit#S
\TangramRabbit[TikZ options]#S
\TangramRabbit*#S
\TangramRabbit*[TikZ options]#S
\TangramPlane#S
\TangramPlane[TikZ options]#S
\TangramPlane*#S
\TangramPlane*[TikZ options]#S
\TangramRooster#S
\TangramRooster[TikZ options]#S
\TangramRooster*#S
\TangramRooster*[TikZ options]#S
\TangramJogger#S
\TangramJogger[TikZ options]#S
\TangramJogger*#S
\TangramJogger*[TikZ options]#S
\TangramDancer#S
\TangramDancer[TikZ options]#S
\TangramDancer*#S
\TangramDancer*[TikZ options]#S
\TangramCamel#S
\TangramCamel[TikZ options]#S
\TangramCamel*#S
\TangramCamel*[TikZ options]#S
\TangramFlamingo#S
\TangramFlamingo[TikZ options]#S
\TangramFlamingo*#S
\TangramFlamingo*[TikZ options]#S
\TangramHeart#S
\TangramHeart[TikZ options]#S
\TangramHeart*#S
\TangramHeart*[TikZ options]#S
\TangramGiraffe#S
\TangramGiraffe[TikZ options]#S
\TangramGiraffe*#S
\TangramGiraffe*[TikZ options]#S
\TangramHorse#S
\TangramHorse[TikZ options]#S
\TangramHorse*#S
\TangramHorse*[TikZ options]#S
\TangramGoat#S
\TangramGoat[TikZ options]#S
\TangramGoat*#S
\TangramGoat*[Tikz options]#S
\TangramLion#S
\TangramLion[TikZ options]#S
\TangramLion*#S
\TangramLion*[Tikz options]#S
\TangramFactory#S
\TangramFactory[TikZ options]#S
\TangramFactory*#S
\TangramFactory*[TikZ options]#S
\TangramAngel#S
\TangramAngel[TikZ options]#S
\TangramAngel*#S
\TangramAngel*[TikZ options]#S
\TangramTower#S
\TangramTower[TikZ options]#S
\TangramTower*#S
\TangramTower*[TikZ options]#S
\TangramUfo#S
\TangramUfo[TikZ options]#S
\TangramUfo*#S
\TangramUfo*[TikZ options]#S
\TangramChicken#S
\TangramChicken[TikZ options]#S
\TangramChicken*#S
\TangramChicken*[TikZ options]#S
\TangramTurtle#S
\TangramTurtle[TikZ options]#S
\TangramTurtle*#S
\TangramTurtle*[TikZ options]#S
\TangramCrab#S
\TangramCrab[TikZ options]#S
\TangramCrab*#S
\TangramCrab*[TikZ options]#S
\TangramSnail#S
\TangramSnail[TikZ options]#S
\TangramSnail*#S
\TangramSnail*[TikZ options]#S
\TangramTikzCreateEN{cmd}#S
\TangramTikzCreateFR{cmd}#S
\TangCouleurs#S
\TangColors#S
\TangCouleur#S
\TangColor#S
\TangBorder#S
