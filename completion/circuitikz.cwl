# circuitikz package
# updated 2023/06/24 for v1.6.3

#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarybending
#include:tikzlibraryfpu

#keyvals:\usepackage/circuitikz#c
european
american
europeanvoltages
straightvoltages
americanvoltages
oldvoltagedirection
nooldvoltagedirection
RPvoltages
EFvoltages
europeancurrents
americancurrents
americanresistors
europeanresistors
americaninductors
europeaninductors
cuteinductors
americanports
europeanports
americangfsurgearrester
europeangfsurgearrester
fulldiode
emptydiode
strokediode
arrowmos
noarrowmos
fetbodydiode
nofetbodydiode
fetsolderdot
nofetsolderdot
emptypmoscircle
lazymos
legacytransistorstext
nolegacytransistorstext
centertransistorstext
straightlabels
rotatelabels
smartlabels
betterproportions
siunitx
nosiunitx
compatibility
#endkeyvals

#ifOption:siunitx
#include:xstring
#include:siunitx
#endif

# from circuitikz.sty
\begin{circuitikz}#\pictureHighlight
\begin{circuitikz}[options%keyvals]#\pictureHighlight
\end{circuitikz}

\circuitikz#S
\endcircuitikz#S
\pgfcircversion#S
\pgfcircversiondate#S

# from pgfcirc.defines.tex
\circuitikzbasekey#*
\circuitikzset{options}#S
\ctikzset{options%keyvals}
\ctikzvalof{option}#*
\ctikzsetvalof{option}{value}#
\pgfstartlinewidth#*
\unexpandedvalueof{option}#*
\pgfcircdeclarebipole{anchors}{lower ysize}{shape}{upper ysize}{width}{code}#*
\pgfcircdeclarebipolescaled{scale}{anchors}{lower ysize}{shape}{upper ysize}{width}{code}#*
\ctikzclass#*
\scaledRlen#*
\northeastborder#S
\southwestborder#S
\textanchor#S
\ctikzloadstyle{style%keyvals}
\ctikzsetstyle{style%keyvals}
#keyvals:\ctikzloadstyle#c,\ctikzsetstyle#c
romano
legacy
example
#endkeyvals
\ctikzgetanchor{name}{anchor}
\ctikzgetdirection{name}

# from pgfcircutils.tex
\ctikzflipx{text%plain}
\ctikzflipy{text%plain}
\ctikzflipxy{text%plain}
\ctikztextnot{text%plain}
\ctikzsubcircuitdef{name}{anchor1,anchor2,...}{definition}
\ctikzsubcircuitactivate{name}
\ctikztunablearrow{thickness}{length}{angle}{name}
\ctikztunablearrow[options]{thickness}{length}{angle}{name}

# from pgfcircpath.tex
\pgfcircresetpath#*
\comnpatname#S
\compattikzset{options}#S
\drawpoles#*

# from pgfcircshapes.tex
# no user commands

# from pgfcircmonopoles.tex
\scaledwidth#*
\gscale#*
\savedwaves#S
\arcpos#S
\topright#S

# from pgfcircbipoles.tex
\wiper#S
\zigs#S
\coredistance#S
\dotXdistance#S
\dotYdistance#S
\midtap#S
\centerprim#S
\centersec#S
\centertert#S
\pgfcircdeclarethyristor{name}{fill}{gate pos}{extra code}
\gatekink#S
\pgfcircdeclaretriac{name}{fill}#*
\pgfcircdiodestylemacro#*
\pgfcircdeclarecutesw{name}{bar pos}{arrow code}#*
\midlever#S
\thisshape#S
\cshape#S
\pgfcircdeclarecutespdt{name}{bar pos}{arrow code}#*
\drawmeteringcircle#*
\pgfcircdeclarejumper{name}{link arc height}#*
\tunablewidth#S
\pgfcircdeclaresolderjumper{name}{0|1}#*
\pgfcircdeclaredoublesolderjumper{name}{0|1}{0|1}#*

# from pgfcirctripoles.tex
\pgfcircdeclarelogicport{name}{number}{code}#*
\resize#S
\inputs#S
\step#S
\origin#S
\pgfcircdeclareeurologicport{name}{symbol}{number}{code}#*
\pgfcircdeclareieeeport{name}{type}{polarity}{code}#*
\baselen#S
\stdH#S
\notdiameter#S
\pind#S
\pinlen#S
\xorbar#S
\bodyleft#S
\topleft#S
\bodyright#S
\bottomright#S
\inners#S
\pgfcircdeclareieeeportpair{name}{negated name}{type}{code}#*
\pgfcircdeclareieeebufferport{name}{polarity}{code}#*
\pgfcircdeclareieeebufferportpair{name}{negated name}{code}#*
\pgfcircdeclareieeetgate{name}{1 or 2}{code}#*
\pgfcircdeclaretransistor{name}{code1}{code2}#*
\circlebase#S
\extrabodydiodelen#S
\scalecircleradius#S
\circleradius#S
\circleleft#S
\centergap#S
\drawdobydiodedot{name}{arg}#*
\drawbodydiode{name}#*
\declarebpt{name}#*
\declarebjt{name}#*
\cdir#S
\numE#S
\numC#S
\multistep#S
\external#S
\basedimension#S
\numup#S
\numdown#S
\declareigbt{name}#*
\declaregfet{name}#*
\drawfetcore{name}#*
\pgfdeclaretransistorwrapperaddbulk{name}{code1}{code2}#*
\pgfcircdeclarejunctiontransistor{name}{code1}{code2}#*
\inOneFixed#S
\inOne#S
\up#S
\leftedge#S
\refv#S
\outport#S
\outportfixed#S
\raOne#S
\pgfcircdeclaretube{name}{grid anchors}{grid code}#*

# from pgfcircquadpoles.tex
\pgfcircdeclarequadpole{name}{code1}{code2}#*
\stretto#S
\innerdot#S
\outerdot#S
\pgfcircmathresult#*
\componentisboxed#S
\pgfcircdeclarefourport{name}{code}#*
\pgfcircdeclaredbipole{arg1}{arg2}{arg3}#*

# from pgfcircmultipoles.tex
\numpins#S
\chipspacing#S
\extshift#S
\mytext#S
\quadrant#S
\rot#S
\central#S
\extnorthwest#S
\channels#S
\stepa#S
\currenta#S
\dotstatus#S
\dotspace#S
\gap#S
\boxgap#S
\wedge#S
\NL#S
\NR#S
\NT#S
\NB#S
\insetnortheast#S
\insethright#S

# from pgfcirclabel.tex
\myscale#S
\pgfcirclabrot#S

# from pgfcircvoltage.tex
\setscaledRlenforclass#*
\addvshift#S
\absvshift#S
\shiftv#S
\bumpa#S
\bumpaplus#S
\labeldist#S
\partheightf#S
\whichtypeshift#S

# from pgfcirccurrent.tex
# no user commands

# from pgfcircflow.tex
\absfshift#S
