# pgfcore package
# Benito van der Zander, 14 May 2011, init contribute
# jsundermeyer@sf.net, 16 Jul 2014, 19 Sep 2015
# Tim Hoffmann, 1 Dec 2016, 9 Feb 2017
# muzimuzhi, 8 Jul 2020
# Matthew Bertucci 2023/01/15 for v3.1.10

# Dependency Tree:
# pgfcore.sty
# ├── graphicx.sty
# ├── pgfsys.sty (see pgfsys.cwl for its dependencies)
# ├── keyval.sty
# ├── xcolor.sty
# └── pgfcore.code.tex
#     ├── pgfmath.code.tex
#     │   ├── pgfkeys.code.tex
#     │   │   └── pgfkeysfiltered.code.tex
#     │   ├── pgfmathcalc.code.tex
#     │   │   ├── pgfmathutil.code.tex
#     │   │   ├── pgfmathparser.code.tex
#     │   │   └── pgfmathfunctions.code.tex
#     │   │       ├── pgfmathfunctions.basic.code.tex
#     │   │       ├── pgfmathfunctions.trigonometric.code.tex
#     │   │       ├── pgfmathfunctions.random.code.tex
#     │   │       ├── pgfmathfunctions.comparison.code.tex
#     │   │       ├── pgfmathfunctions.base.code.tex
#     │   │       ├── pgfmathfunctions.round.code.tex
#     │   │       ├── pgfmathfunctions.misc.code.tex
#     │   │       └── pgfmathfunctions.integerarithmetics.code.tex
#     │   └── pgfmathfloat.code.tex
#     ├── pgfint.code.tex
#     ├── pgfcorepoints.code.tex
#     ├── pgfcorepathconstruct.code.tex
#     ├── pgfcorepathusage.code.tex
#     ├── pgfcorescopes.code.tex
#     ├── pgfcoregraphicstate.code.tex
#     ├── pgfcoretransformations.code.tex
#     ├── pgfcorequick.code.tex
#     ├── pgfcoreobjects.code.tex
#     ├── pgfcorepathprocessing.code.tex
#     ├── pgfcorearrows.code.tex
#     ├── pgfcoreshade.code.tex
#     ├── pgfcoreimage.code.tex
#     ├── pgfcoreexternal.code.tex
#     ├── pgfcorelayers.code.tex
#     ├── pgfcoretransparency.code.tex
#     ├── pgfcorepatterns.code.tex
#     └── pgfcorerdf.code.tex

#include:graphicx
#include:pgfsys
#include:keyval
#include:xcolor

# from pgfmath.code.tex (this is what pgfmath.sty inputs)
#include:pgfmath

# from pgfint.code.tex
\pgfintloaded#*
\pgfinteval{expr}#*
\pgfintabs{number}#*
\pgfintmax{number1}{number2}#*
\pgfintmin{number1}{number2}#*
\pgfintdivtruncate{number1}{number2}#*
\pgfintdivfloor{number1}{number2}#*
\pgfintdivround{number1}{number2}#*
\pgfintmod{number}{modulus}#*
\pgfintset{arg}{expr}#*

# from pgfcorepoints.code.tex
\pgfpoint{x}{y}#*
\pgfqpoint{x}{y}#*
\pgfpointorigin#*
\pgfpointtransformed{point}#*
\pgfpointdiff{start}{end}#*
\pgfpointadd{vec1}{vec2}#*
\pgfpointscale{factor}{coordinate}#*
\pgfqpointscale{factor}{coordinate}#*
\pgfpointintersectionoflines{start1}{end1}{start2}{end2}#*
\pgfpointintersectionofcircles{p1}{p2}{r1}{r2}{solution}#*
\pgfpointlineattime{time}{p1}{p2}#*
\pgfpointlineatdistance{distance}{p1}{p2}#*
\pgfpointcurveattime{time}{p1}{p2}{p3}{p4}#*
\pgfpointarcaxesattime{time}{center}{0-degree axis}{90-degree axis}{start angle}{end angle}#*
\pgfpointpolar{degree}{radius}#*
\pgfqpointpolar{degree}{radius}#*
\pgfpointpolarxy{degree}{radius}#*
\pgfpointcylindrical{degree}{radius}{height}#*
\pgfpointspherical{longitude}{latitude}{radius}#*
\pgfpointxy{x}{y}#*
\pgfqpointxy{x}{y}#*
\pgfpointxyz{x}{y}{z}#*
\pgfqpointxyz{x}{y}{z}#*
\pgfsetxvec{point}#*
\pgfsetyvec{point}#*
\pgfsetzvec{point}#*
\pgfpointnormalised{point}#*
\pgfpointborderrectangle{direction}{corner}#*
\pgfpointborderellipse{direction}{corner}#*
\pgfextractx{dimension}{point}#*
\pgfextracty{dimension}{point}#*
\pgfgetlastxy{macro for x%cmd}{macro for y%cmd}#*d
\pgfpointtransformednonlinear{point}#*

# from pgfcorepathconstruct.code.tex
\pgfgetpath{macro%cmd}#*d
\pgfsetpath{macro}#*
\pgfsetcornersarced{point}#*
\pgfpathmoveto{point}#*
\pgfpathlineto{point}#*
\pgfpathclose#*
\pgfpathcurveto{support p1}{support p2}{end point}#*
\pgfpathquadraticcurveto{support point}{end point}#*
\pgfpatharc{start angle}{end angle}{radius}#*
\pgfpatharcaxes{start angle}{end angle}{axis1}{axis2}#*
\pgfpatharcto{x-radius}{y-radius}{rotation}{large arc flag}{countercl flag}{target point}#*
\pgfpatharctomaxstepsize#*
\pgfpatharctoprecomputed{point1}{start angle}{end angle}{point2}{a}{b}{ab-ratio}{ba-ratio}#*
\pgfpathellipse{center}{axis2}{axis2}#*
\pgfpathcircle{center}{radius}#*
\pgfpathrectangle{corner}{diagonal vector}#*
\pgfpathrectanglecorners{corner}{opposite corner}#*
\pgfpathgrid{corner1}{corner2}#*
\pgfpathgrid[options%keyvals]{corner1}{corner2}#*
#keyvals:\pgfpathgrid#c
stepx=##L
stepy=##L
step=%<vector%>
#endkeyvals
\pgfpathparabola{bend vector}{end vector}#*
\pgfpathsine{vector}#*
\pgfpathcosine{vector}#*
\pgfpathcurvebetweentime{time t1}{time t2}{point p}{point s1}{point s2}{point q}#*
\pgfpathcurvebetweentimecontinue{time t1}{time t2}{point p}{point s1}{point s2}{point q}#*

# from pgfcorepathusage.code.tex
\pgfusepath{actions%keyvals}#*
#keyvals:\pgfusepath#c
fill
stroke
draw
clip
discard
#endkeyvals
\pgfsetshortenstart{dimen%l}#*
\pgfsetshortenend{dimen%l}#*

# from pgfcorescopes.code.tex
\pgfpic#*
\ifpgfrememberpicturepositiononpage#*
\pgfrememberpicturepositiononpagetrue#*
\pgfrememberpicturepositiononpagefalse#*
\pgfscope#*
\endpgfscope#*
\begin{pgfscope}#*
\end{pgfscope}#*
\pgfqbox{box number}#*
\pgfqboxsynced{box number}#*
\pgftext{text}#*
\pgftext[options%keyvals]{text}#*
#keyvals:\pgftext#c
left
right
top
bottom
base
at=%<point%>
x=##L
y=##L
rotate=%<degree%>
#endkeyvals
\pgfresetboundingbox#*
\pgfpicture#*
\endpgfpicture#*
\begin{pgfpicture}#*
\end{pgfpicture}#*
\pgfsetbaselinepointlater{point}#*
\pgfsetbaselinepointnow{point}#*
\pgfsetbaseline{dimen%l}#*
\pgfsettrimleftpointlater{coordinate}#*
\pgfsettrimleftpointnow{coordinate}#*
\pgfsettrimleft{coordinate}#*
\pgfsettrimrightpointlater{coordinate}#*
\pgfsettrimrightpointnow{coordinate}#*
\pgfsettrimright{coordinate}#*
\begin{pgfinterruptpath}#*
\end{pgfinterruptpath}#*
\pgfinterruptpath#*
\endpgfinterruptpath#*
\begin{pgfinterruptboundingbox}#*
\end{pgfinterruptboundingbox}#*
\pgfinterruptboundingbox#*
\endpgfinterruptboundingbox#*
\begin{pgfidscope}#*
\end{pgfidscope}#*
\pgfidscope#*
\endpgfidscope#*
\pgfuseid{name}#*
\pgfclearid#*
\pgfidrefnextuse{cmd}{name}#*d
\pgfidrefprevuse{cmd}{name}#*d
\pgfusetype{type}#*
\pgfpushtype#*
\pgfpoptype#*
\pgfaliasid{alias}{name}#*
\pgfgaliasid{alias}{name}#*
\pgfifidreferenced{name}{then code}{else code}#*
\begin{pgfinterruptpicture}#*
\end{pgfinterruptpicture}#*
\pgfinterruptpicture#*
\endpgfinterruptpicture#*

# from pgfcoregraphicstate.code.tex
\pgflinewidth#*
\pgfsetlinewidth{width}#*
\pgfsetinnerlinewidth{width}#*
\pgfinnerlinewidth#*
\pgfsetinnerstrokecolor{color}#*
\pgfinnerstrokecolor#*
\pgfsetmiterlimit{miter limit factor}#*
\pgfsetdash{{%<dimen1%>}%<{dimen2}...%>}{%<phase%>}#*
\pgfsetstrokecolor{color}#*
\pgfsetfillcolor{color}#*
\pgfsetcolor{color}#*
\pgfsetbuttcap#*
\pgfsetroundcap#*
\pgfsetrectcap#*
\pgfsetmiterjoin#*
\pgfsetbeveljoin#*
\pgfsetroundjoin#*
\pgfseteorule#*
\pgfsetnonzerorule#*

# from pgfcoretransformations.code.tex
\pgfgettransform{macro%cmd}#*d
\pgfgettransformentries{macro1%cmd}{macro2%cmd}{macro3%cmd}{macro4%cmd}{xshift-macro%cmd}{yshift-macro%cmd}#*d
\pgfsettransformentries{macro1}{macro2}{macro3}{macro4}{xshift-macro}{yshift-macro}#*
\pgfsettransform{macro}#*
\pgftransforminvert#*
\pgftransformcm{a}{b}{c}{d}{point}#*
\pgftransformtriangle{a}{b}{c}#*
\pgftransformreset#*
\pgftransformresetnontranslations#*
\pgftransformshift{point}#*
\pgftransformxshift{dimen%l}#*
\pgftransformyshift{dimen%l}#*
\pgftransformscale{factor}#*
\pgftransformxscale{factor}#*
\pgftransformyscale{factor}#*
\pgftransformxslant{factor}#*
\pgftransformyslant{factor}#*
\pgftransformrotate{angle}#*
\ifpgfslopedattime#*
\pgfslopedattimetrue#*
\pgfslopedattimefalse#*
\ifpgfallowupsidedownattime#*
\pgfallowupsidedownattimetrue#*
\pgfallowupsidedownattimefalse#*
\ifpgfresetnontranslationattime#*
\pgfresetnontranslationattimetrue#*
\pgfresetnontranslationattimefalse#*
\pgftransformlineattime{time}{start}{end}#*
\pgftransformarcaxesattime{time}{center}{0-deg axis}{90-deg axis}{start angle}{end angle}#*
\pgftransformcurveattime{time}{start}{support1}{support2}{end}#*
\pgftransformarrow{start}{end}#*
\pgftransformationadjustments#*
\pgfhorizontaltransformationadjustment#*
\pgfverticaltransformationadjustment#*
\pgflowlevelsynccm#*
\pgflowlevel{transformation code}#*
\begin{pgflowlevelscope}{transformation code}#*
\end{pgflowlevelscope}#*
\pgflowlevelscope{transformation code}#*
\endpgflowlevelscope#*
\pgflowlevelobj{transformation code}{code}#*
\pgfviewboxscope{ll1}{ur1}{ll2}{ur2}{meet or slice}#*
\endpgfviewboxscope#*
\begin{pgfviewboxscope}{ll1}{ur1}{ll2}{ur2}{meet or slice}#*
\end{pgfviewboxscope}#*
\pgfapproximatenonlineartranslation#*
\pgfapproximatenonlineartransformation#*
\pgftransformnonlinear{transformation code}#*

# from pgfcorequick.code.tex
\pgfpathqmoveto{x-dimen%l}{y-dimen%l}#*
\pgfpathqlineto{x-dimen%l}{y-dimen%l}#*
\pgfpathqcurveto{x-dimen1%l}{y-dimen1%l}{x-dimen2%l}{y-dimen2%l}{target-x-dimen%l}{target-y-dimen%l}#*
\pgfpathqcircle{radius%l}#*
\pgfusepathqstroke#*
\pgfusepathqfill#*
\pgfusepathqfillstroke#*
\pgfusepathqclip#*

# from pgfcoreobjects.code.tex
\pgfdefobject{name}{ll}{ur}{code}#*
\pgfuseobject{name}#*
\pgfuseobjectmagnify{name}#*

# from pgfcorepathprocessing.code.tex
\pgfprocesssplitpath{macro%cmd}#*d
\pgfprocesssplitsubpath{macro%cmd}#*d
\pgfprocessresultsubpathprefix#*
\pgfprocessresultsubpathsuffix#*
\pgfprocesspathextractpoints{macro%cmd}#*d
\pgfpointfirstonpath#*
\pgfpointsecondonpath#*
\pgfpointsecondlastonpath#*
\pgfpointlastonpath#*
\pgfprocesscheckclosed{macro%cmd}{code}#*d
\pgfprocessround{macro1%cmd}{macro2%cmd}#*d
\pgfprocesspathreplacestartandend{start coord}{end coord}#*

# from pgfcorearrows.code.tex
\pgfdeclarearrow{config%keyvals}#*
#keyvals:\pgfdeclarearrow#c
name=%<name%>
name=%<start name%>-%<end name%>
parameters={%<list of macros%>}
setup code={%<code%>}
drawing code={%<code%>}
cache#true,false
bending mode=#none,orthogonal,polar
defaults=%<arrow keys%>
means=
#endkeyvals
\pgfarrowdraw{specification}#*
\pgfarrowtotallength{specification}#*
\pgfsetarrowsend{specification}#*
\pgfsetarrowsstart{specification}#*
\pgfarrowsep#*
\ifpgfarrowswap#*
\pgfarrowswaptrue#*
\pgfarrowswapfalse#*
\ifpgfarrowreversed#*
\pgfarrowreversedtrue#*
\pgfarrowreversedfalse#*
\ifpgfarrowharpoon#*
\pgfarrowharpoontrue#*
\pgfarrowharpoonfalse#*
\ifpgfarrowopen#*
\pgfarrowopentrue#*
\pgfarrowopenfalse#*
\pgfarrowsaddtolengthscalelist{dimen register}#*
\pgfarrowsaddtowidthscalelist{dimen register}#*
\pgfarrowsaddtooptions{code}#*
\pgfarrowsaddtolateoptions{code}#*
\pgfarrowlength#*
\pgfarrowsthreeparameters{size spec}#*
\pgfarrowstheparameters#*
\pgfarrowsfourparameters{size spec}#*
\pgfarrowslinewidthdependent{dimen%l}{line width factor}{outer factor}#*
\pgfarrowslengthdependent{dimen%l}{length factor}{dummy}#*
\pgfarrowssavethe{register}#*
\pgfarrowssave{macro%cmd}#*d
\pgfarrowshullpoint{x-dimen%l}{y-dimen%l}#*
\pgfarrowsupperhullpoint{x-dimen%l}{y-dimen%l}#*
\pgfarrowssettipend{dimen%l}#*
\pgfarrowssetbackend{dimen%l}#*
\pgfarrowssetlineend{dimen%l}#*
\pgfarrowssetvisualtipend{dimen%l}#*
\pgfarrowssetvisualbackend{dimen%l}#*
\pgfsetarrows{startspec-endspec}#*

# the following arrow commands are deprecated
\pgfsetarrowoptions{shape}{dimen%l}#S
\pgfgetarrowoptions{shape}#S
\pgfarrowsdeclare{arg1}{arg2}{arg3}{arg4}#S
\pgfarrowsleftextend{arg1}#S
\pgfarrowsrightextend{arg1}#S
\pgfarrowsdeclarealias{arg1}{arg2}{arg3}{arg4}#S
\pgfarrowsdeclarereversed{arg1}{arg2}{arg3}{arg4}#S
\pgfarrowsdeclarecombine#S
\pgfarrowsdeclaredouble#S
\pgfarrowsdeclaretriple#S

# from pgfcoreshade.code.tex
\ifpgfshadingmodelrgb#*
\pgfshadingmodelrgbtrue#*
\pgfshadingmodelrgbfalse#*
\ifpgfshadingmodelcmyk#*
\pgfshadingmodelcmyktrue#*
\pgfshadingmodelcmykfalse#*
\ifpgfshadingmodelgray#*
\pgfshadingmodelgraytrue#*
\pgfshadingmodelgrayfalse#*
\pgfdeclarehorizontalshading{name}{height}{color spec}#*
\pgfdeclarehorizontalshading[color list]{name}{height}{color spec}#*
\pgfdeclareverticalshading{name}{width}{color spec}#*
\pgfdeclareverticalshading[color list]{name}{width}{color spec}#*
\pgfdeclareradialshading{name}{center point}{color spec}#*
\pgfdeclareradialshading[color list]{name}{center point}{color spec}#*
\pgfdeclarefunctionalshading{name}{ll-corner}{ur-corner}{init-code}{function}#*
\pgfdeclarefunctionalshading[color list]{name}{ll-corner}{ur-corner}{init-code}{function}#*
\pgfshadecolortorgb{color}{macro%cmd}#*d
\pgfshadecolortocmyk{color}{macro%cmd}#*d
\pgfshadecolortogray{color}{macro%cmd}#*d
\pgffuncshadingrgbtocmyk#*
\pgffuncshadingrgbtogray#*
\pgffuncshadingcmyktorgb#*
\pgffuncshadingcmyktogray#*
\pgffuncshadinggraytorgb#*
\pgffuncshadinggraytocmyk#*
\pgfuseshading{name}#*
\pgfaliasshading{alias name}{original name}#*
\pgfshadepath{name}{angle}#*
\pgfsetadditionalshadetransform{transformation}#*

# from pgfcoreimage.code.tex
\pgfdeclareimage[options%keyvals]{image name}{imagefile}#*
\pgfdeclareimage{image name}{imagefile}#*
\pgfdeclaremask[options%keyvals]{mask name}{imagefile}#*
\pgfdeclaremask{mask name}{imagefile}#*
#keyvals:\pgfdeclaremask
matte=%<color components%>
#endkeyvals
\pgfaliasimage{new image name}{existing image name}#*
\pgfuseimage{image name}#*
\pgfalternateextension#*
\pgfimage[options%keyvals]{imagefile}#*g
\pgfimage{imagefile}#*g
#keyvals:\pgfdeclareimage,\pgfimage
height=##L
width=##L
page=%<page number%>
interpolate#true,false
mask=%<mask name%>
#endkeyvals

# from pgfcoreexternal.code.tex
\ifpgfexternalreadmainaux#*
\pgfexternalreadmainauxtrue#*
\pgfexternalreadmainauxfalse#*
\pgfrealjobname{name}#*
\pgfactualjobname#*
\beginpgfgraphicnamed{file name prefix}#*
\endpgfgraphicnamed#*
\pgfincludeexternalgraphics{imagefile}#*g
\pgfexternalreaddpth{imagefile}#*
\pgfexternaldepth#*
\pgfexternaltrimleft#*
\pgfexternaltrimright#*
\dpthimport#*
\pgfexternalstorecommand{cmd}#*
\pgfexternalwidth#*
\pgfexternalheight#*

# from pgfcorelayers.code.tex
\pgfdeclarelayer{name}#*
\pgfsetlayers{layer list}#*
\begin{pgfonlayer}{layer name}#*
\end{pgfonlayer}#*
\pgfonlayer{layer name}#*
\endpgfonlayer#*
\pgfdiscardlayername#*

# from pgfcoretransparency.code.tex
\pgfsetstrokeopacity{value}#*
\pgfsetfillopacity{value}#*
\pgfsetblendmode{mode%keyvals}#*
#keyvals:\pgfsetblendmode
normal
multiply
screen
overlay
darken
lighten
color dodge
color burn
hard light
soft light
difference
exclusion
saturation
color
hue
luminosity
#endkeyvals
\pgfdeclarefading{name}{contents}#*
\pgfsetfading{name}{transformations}#*
\pgfsetfadingforcurrentpath{name}{transformations}#*
\pgfsetfadingforcurrentpathstroked{name}{transformations}#*
\begin{pgftransparencygroup}#*
\begin{pgftransparencygroup}[options%keyvals]#*
\end{pgftransparencygroup}#*
\pgftransparencygroup#*
\pgftransparencygroup[options%keyvals]#*
\endpgftransparencygroup#*
#keyvals:\begin{pgftransparencygroup},\pgftransparencygroup
knockout#true,false
isolated#true,false
#endkeyvals

# from pgfcorepatterns.code.tex
\pgfdeclarepatternformonly{name}{bottom left}{top right}{tile size}{code}#*
\pgfdeclarepatternformonly[variables]{name}{bottom left}{top right}{tile size}{code}#*
\pgfdeclarepatterninherentlycolored{name}{bottom left}{top right}{tile size}{code}#*
\pgfdeclarepatterninherentlycolored[variables]{name}{bottom left}{top right}{tile size}{code}#*
\pgfpatternreleasename{name}#*
\pgfsetfillpattern{name}{color}#*

# from pgfcorerdf.code.tex
\pgfrdfabout{text}#*
\pgfrdfcontent{text}#*
\pgfrdfdatatype{text}#*
\pgfrdfhref{text}#*
\pgfrdfinlist#*
\pgfrdfprefix{text}#*
\pgfrdfproperty{text}#*
\pgfrdfrel{text}#*
\pgfrdfresource{text}#*
\pgfrdfrev{text}#*
\pgfrdfsrc{text}#*
\pgfrdftypeof{text}#*
\pgfrdfvocab{text}#*

## Commands in pgf libraries and modules also listed here with #S
## They must be loaded with \usepgflibrary or \usepgfmodule
## If another package loads a library or module the commands can be copied to that package's cwl with #S removed or replaced with #*

## arrows pgflibrary
\arrowsize#S

## arrows.meta pgflibrary
\pgfarrowinset#S
\pgfarrowwidth#S
\pgfarrowlinewidth#S
\ifpgfarrowroundcap#S
\pgfarrowroundcaptrue#S
\pgfarrowroundcapfalse#S
\ifpgfarrowroundjoin#S
\pgfarrowroundjointrue#S
\pgfarrowroundjoinfalse#S
\pgfarrowarc#S
\pgfarrown#S

## arrows.spaced pgflibrary
# loads arrows pgflibrary
# no new user commands

## curvilinear pgflibrary
\pgfsetcurvilinearbeziercurve{start}{support1}{support2}{end}#S
\pgfcurvilineardistancetotime{distance}#S
\pgfpointcurvilinearbezierorthogonal{distance}{offset}#S
\pgfpointcurvilinearbezierpolar{x}{y}#S

## datavisualization.barcharts pgflibrary
# loads datavisualization pgfmodule
# no new user commands

## datavisualization.formats.functions pgflibrary
# loads datavisualization pgfmodule
# no new user commands

## datavisualization.polar pgflibrary
# loads datavisualization pgfmodule
# no new user commands

## decorations.footprints pgflibrary
# loads decorations pgfmodule
# no new user commands

## decorations.fractals pgflibrary
# loads decorations pgfmodule
# no new user commands

## decorations.markings pgflibrary
# loads decorations pgfmodule
# no new user commands

## decorations.pathmorphing pgflibrary
# loads decorations pgfmodule
# no new user commands

## decorations.pathreplacing pgflibrary
# loads decorations pgfmodule
# no new user commands

## decorations.shapes pgflibrary
# loads decorations pgfmodule
\ifpgfshapedecorationsloped#S
\pgfshapedecorationslopedtrue#S
\pgfshapedecorationslopedfalse#S
\ifpgfshapedecorationscaled#S
\pgfshapedecorationscaledtrue#S
\pgfshapedecorationscaledfalse#S

## decorations.text pgflibrary
# loads decorations pgfmodule
\pgfdecorationrestoftext#S
\pgfdecorationtext#S
\pgfsetdecoratetextformatdelimiters{delim1}{delim2}#S

## fadings pgflibrary
# no new user commands

## fixedpointarithmetic pgflibrary
\pgfmathfpscale#S
\pgfmathfpparse{expr}#S
\pgfmathfpscientific{x}{y}#S
\pgfmathfplessthan{x}{y}#S
\pgfmathfpgreaterthan{x}{y}#S
\pgfmathfpequalto{x}{y}#S
\pgfmathfpadd{x}{y}#S
\pgfmathfpsubtract{x}{y}#S
\pgfmathfpmultiply{x}{y}#S
\pgfmathfpdivide{x}{y}#S
\pgfmathfpabs{x}#S
\pgfmathfpneg{x}#S
\pgfmathfpround{x}#S
\pgfmathfpfloor{x}#S
\pgfmathfpceil{x}#S
\pgfmathfpmod{x}{y}#S
\pgfmathfpmax{x}{y}#S
\pgfmathfpmin{x}{y}#S
\pgfmathfppow{x}{y}#S
\pgfmathfpexp{x}#S
\pgfmathfpln{x}#S
\pgfmathfpsqrt{x}#S
\pgfmathfpveclen{x}{y}#S
\pgfmathfpsin{x}#S
\pgfmathfpcos{x}#S
\pgfmathfptan{x}#S
\pgfmathfpacos{x}#S
\pgfmathfpasin{x}#S
\pgfmathfpatan{x}#S
\pgfmathfpcot{x}#S
\pgfmathfpsec{x}#S
\pgfmathfpcosec{x}#S
\pgfmathfpdeg{x}#S
\pgfmathfprad{x}#S
\pgfmathfpsetseed{x}#S
\pgfmathfprnd#S
\pgfmathfprand#S

## fpu pgflibrary
\ifpgfmathfloatparseactive#S
\pgfmathfloatparseactivetrue#S
\pgfmathfloatparseactivefalse#S
\pgflibraryfpuifactive{true code}{false code}#S
\pgfmathfloatscale#S
\pgfmathfloatone#S
\pgfmathfloatparse#S
\pgfmathfloatscientific{x}{y}#S
\pgfmathfloatlessthan{x}{y}#S
\pgfmathfloatgreaterthan{x}{y}#S
\pgfmathfloatmaxtwo{x}{y}#S
\pgfmathfloatmax{x}{y}#S
\pgfmathfloatmin{x}{y}#S
\pgfmathfloatmintwo{x}{y}#S
\pgfmathfloattoextentedprecision{x}#S
\pgfmathfloatsetextprecision{shift}#S
\pgfmathfloatifzero{x}{true code}{false code}#S
\pgfmathfloatiffinite{x}{true code}{false code}#S
\pgfmathfloatifapproxequalrel{x}{y}{true code}{false code}#S
\pgfmathfloatifflags{number}{flag}{true code}{false code}#S
\pgfmathfloatadd{x}{y}#S
\pgfmathfloatsubtract{x}{y}#S
\pgfmathfloatmultiplyfixed{float}{fixed}#S
\pgfmathfloatmultiply{x}{y}#S
\pgfmathfloatdivide{x}{y}#S
\pgfmathfloatsqrt{x}#S
\pgfmathfloatint{x}#S
\pgfmathfloatfloor{x}#S
\pgfmathfloatceil{x}#S
\pgfmathfloatshift{x}{num}#S
\pgfmathfloatsign{x}#S
\pgfmathfloatabserror{x}{y}#S
\pgfmathfloatrelerror{x}{y}#S
\pgfmathfloatmod{x}{y}#S
\pgfmathfloatmodknowsinverse{x}{y}{z}#S
\pgfmathfloatpi#S
\pgfmathfloate#S
\pgfmathfloatdeg{x in radians}#S
\pgfmathfloatrad{x in degrees}#S
\pgfmathfloatsin{x in degrees}#S
\pgfmathfloatcos{x in degrees}#S
\pgfmathfloattan{x in degrees}#S
\pgfmathfloatcot{x in degrees}#S
\pgfmathfloatatan{x}#S
\pgfmathfloatatantwo{x}{y}#S
\pgfmathfloatsec{x in degrees}#S
\pgfmathfloatcosec{x in degrees}#S
\pgfmathfloatln{x}#S
\pgfmathlog{x}#S
\pgfmathfloatexp{x}#S
\pgfmathfloatrand#S
\pgfmathfloatrnd#S

## graphdrawing.circular pgflibrary
# loads circular gdlibrary
# no new user commands

## graphdrawing pgflibrary
\pgfgdset{options%keyvals}#S
\pgfgdappendtoforwardinglist{paths}#S
\pgfgdcallbackdeclareparameter{key%plain}{type}#S
\pgfgdtriggerrequest#S
\pgfgdcallbackrendercollectionkindstart{kind}{layer}#S
\pgfgdcallbackrendercollectionkindstop{kind}{layer}#S
\pgfgdcallbackrendercollection{kind}{options}#S
\pgfgdevent{name}{parameter}#S
\pgfgdbegineventgroup{parameter}#S
\pgfgdendeventgroup#S
\pgfgdeventgroup{name}#S
\pgfgdsetlatenodeoption{node name}#S
\pgfgdcallbackrendernode{node name}{xmin}{xmax}{ymin}{ymax}{xpos}{ypos}{boxnum}{code}#S
\pgfpositionnodelatername#S
\pgfpositionnodelaterminx#S
\pgfpositionnodelatermaxx#S
\pgfpositionnodelaterminy#S
\pgfpositionnodelatermaxy#S
\pgfgdedge{node1}{node2}{edge dir}{edge opts}{edge nodes}#S
\pgfgdprepareedge#S
\pgfgdaddprepareedgehook{code}#S
\pgfgdsetedgecallback{macro}#S
\pgfgddefaultedgecallback{node1}{node2}{options}{auxtext}{alg options}{bend info}{animations}#S
\pgfgdcallbackbeginshipout#S
\pgfgdcallbackendshipout#S
\pgfgdcallbackbeginnodeshipout#S
\pgfgdcallbackendnodeshipout#S
\pgfgdcallbackbeginedgeshipout#S
\pgfgdcallbackendedgeshipout#S
\pgfgdcallbackcreatevertex{node name}{shape}{options}{text}#S
\pgfgdbeginlayout#S
\pgfgdendlayout#S
\pgfgdsubgraphnode{node name}{node options}{node text}#S
\pgfgdsubgraphnodecontents{arg}#S
\pgfgdbeginrequest#S
\pgfgdendrequest#S
\ifpgfgdlayoutscopeactive#S
\pgfgdlayoutscopeactivetrue#S
\pgfgdlayoutscopeactivefalse#S
\pgfgdsetrequestcallback{macro}#S
\ifpgfgdgraphdrawingscopeactive#S
\pgfgdgraphdrawingscopeactivetrue#S
\pgfgdgraphdrawingscopeactivefalse#S
\pgfgdbeginscope#S
\ifpgfgdresumecoroutine#S
\pgfgdresumecoroutinetrue#S
\pgfgdresumecoroutinefalse#S
\pgfgdendscope#S
\pgfgdaddspecificationhook{code}#S
\usegdlibrary{list of libraries%keyvals}#S
#keyvals:\usegdlibrary#c
trees
layered
force
circular
phylogenetics
routing
#endkeyvals

## graphdrawing.examples pgflibrary
# loads graphdrawing pgflibrary and examples gdlibrary
# no new user commands

## graphdrawing.force pgflibrary
# loads graphdrawing pgflibrary and force gdlibrary
# no new user commands

## graphdrawing.layered pgflibrary
# loads graphdrawing pgflibrary and layered gdlibrary
# no new user commands

## graphdrawing.trees pgflibrary
# loads graphdrawing and graphdrawing.layered pgflibraries and trees gdlibrary
# no new user commands

## intersections pgflibrary
# loads fpu pgflibrary
\pgfintersectionsortbyfirstpath#S
\pgfintersectionsortbysecondpath#S
\pgfpointintersectionsolution{number}#S
\pgfintersectiongetsolutionsegmentindices{number}{macro1}{macro2}#S
\pgfintersectionsolutions#S
\pgfintersectiongetsolutiontimes{number}{macro1}{macro2}#S
\pgfintersectionofpaths{path1}{path2}#S
\pgfiflinesintersect{line1}{line2}{true}{false}#S
\pgfintersectionoflineandcurve{p1}{p2}{q1}{q2}{q3}{q4}#S
\pgfintersectiontolerance#S
\pgfintersectiontoleranceupperbound#S
\pgfintersectiontolerancefactor#S
\pgfpointintersectionofcurves{p1}{p2}{p3}{p4}{q1}{q2}{q3}{q4}{number}#S
\pgfintersectionofcurves{p1}{p2}{p3}{p4}{q1}{q2}{q3}{q4}#S
\pgfintersectionsolutionsortbytime#S

## lindenmayersystems pgflibrary
\pgflsystemstep#S
\pgflsystemrandomizesteppercent#S
\pgflsystemrandomizeanglepercent#S
\pgfdeclarelindenmayersystem{name}{specification}#S
\pgflsystemcurrentstep#S
\pgflsystemcurrentleftangle#S
\pgflsystemcurrentrightangle#S
\pgflsystemrandomizestep#S
\pgflsystemrandomizerightangle#S
\pgflsystemrandomizeleftangle#S
\pgflsystemdrawforward#S
\pgflsystemmoveforward#S
\pgflsystemturnright#S
\pgflsystemturnleft#S
\pgflsystemsavestate#S
\pgflsystemrestorestate#S
\pgflindenmayersystem{name}{axiom}{order}#S

## luamath pgflibrary
\ifpgfluamathshowerrormessage#S
\pgfluamathshowerrormessagetrue#S
\pgfluamathshowerrormessagefalse#S
\ifpgfluamathenableTeXfallback#S
\pgfluamathenableTeXfallbacktrue#S
\pgfluamathenableTeXfallbackfalse#S
\ifpgfluamathcomputationactive#S
\pgfluamathcomputationactivetrue#S
\pgfluamathcomputationactivefalse#S
\ifpgfluamathparseractive#S
\pgfluamathparseractivetrue#S
\pgfluamathparseractivefalse#S
\pgfluamathgetresult{lua expr}#S
\pgfluamathone#S
\pgfluamathfloatone#S
\pgfluamathreciprocal{lua expr}#S
\pgfluamathpointnormalised{expr}#S
\ifpgfluamathunitsdeclared#S
\pgfluamathunitsdeclaredtrue#S
\pgfluamathunitsdeclaredfalse#S
\ifpgfluamathusedTeXfallback#S
\pgfluamathusedTeXfallbacktrue#S
\pgfluamathusedTeXfallbackfalse#S
\pgfluamathparse{expr}#S

## patterns pgflibrary
# no new user commands

## patterns.meta pgflibrary
\pgfifpatternundefined{name}#S
\pgfdeclarepattern{config%keyvals}#S
#keyvals:\pgfdeclarepattern#c
name=%<name%>
type=#uncolored,colored,form only,inherently colored
x=##L
y=##L
parameters=
defaults=
bottom left=%<pgf point%>
top right=%<pgf point%>
tile size=%<pgf point%>
tile transformation=%<pgf transformation%>
code=%<code%>
set up code=%<code%>
#endkeyvals
\pgfpatternalias{name1}{name2}#S

## plothandlers pgflibrary
\pgfplothandlercurveto#S
\pgfsetplottension{tension}#S
\pgfplothandlerclosedcurve#S
\pgfplothandlerxcomb#S
\pgfplothandlerycomb#S
\pgfplotxzerolevelstreamstart#S
\pgfplotxzerolevelstreamend#S
\pgfplotxzerolevelstreamnext#S
\pgfplotyzerolevelstreamstart#S
\pgfplotyzerolevelstreamend#S
\pgfplotyzerolevelstreamnext#S
\pgfplotxzerolevelstreamconstant{dimen%l}#S
\pgfplotyzerolevelstreamconstant{dimen%l}#S
\pgfplotbarwidth#S
\pgfplotbarshift#S
\pgfplothandlerybar#S
\pgfplothandlerxbar#S
\pgfplothandlerybarinterval#S
\pgfplothandlerxbarinterval#S
\pgfplothandlerconstantlineto#S
\pgfplothandlerconstantlinetomarkright#S
\pgfplothandlerconstantlinetomarkmid#S
\pgfplothandlerjumpmarkright#S
\pgfplothandlerjumpmarkleft#S
\pgfplothandlerjumpmarkmid#S
\pgfplothandlerpolarcomb#S
\pgfplothandlermark{mark code}#S
\pgfsetplotmarkrepeat{repeat count}#S
\pgfsetplotmarkphase{index}#S
\pgfplothandlermarklisted{code}{positions}#S
\pgfdeclareplotmark{name}{code}#S
\pgfsetplotmarksize{size%l}#S
\pgfplotmarksize#S
\pgfuseplotmark{name}#S
\pgfplothandlergaplineto#S
\pgfplothandlergapcycle#S

## plotmarks pgflibrary
# no new user commands

## profiler pgflibrary
\pgfprofilenew{name}#S
\pgfprofilenewforenvironment{envname}#S
\pgfprofilenewforenvironment[profiler entry name]{envname}#S
\pgfprofilecs#S
\pgfprofileenv#S
\pgfprofilenewforcommand{macro}{args}#S
\pgfprofilenewforcommand[profiler entry name]{macro}{args}#S
\pgfprofilenewforcommandpattern{macro}{arg pattern}{invocation pattern}#S
\pgfprofilenewforcommandpattern[profiler entry name]{macro}{arg pattern}{invocation pattern}#S
\pgfprofileshowinvocationsfor{profiler entry name}#S
\pgfprofileshowinvocationsexpandedfor{profiler entry name}#S
\pgfprofileinvokecommand{arg}#S
\pgfprofilestart{profiler entry name}#S
\pgfprofileend{profiler entry name}#S
\pgfprofileifisrunning{profiler entry name}{true code}{false code}#S
\pgfprofilesetrel{profiler entry name}#S
\pgfprofilepostprocess#S
\pgfprofileforeachentryinCSV{list}{macro}#S
\pgfprofilestackpush{arg}#S
\pgfprofilestackpop{arg}#S
\pgfprofilestacktop{arg}#S
\pgfprofilestackifempty{arg1}{arg2}#S
\pgfprofiletotwodigitstr{arg}#S

## shadings pgflibrary
# no new user commands

## shapes pgflibrary
# loads shapes.geometric, shapes.misc, and shapes.symbols pgflibraries
# no new user commands

## shapes.arrows pgflibrary
\getsinglearrowpoints#S
\xoutersep#S
\youtersep#S
\cosechalftipangle#S
\sechalftipangle#S
\tanhalftipangle#S
\arrowtip#S
\beforearrowtip#S
\beforearrowhead#S
\afterarrowtail#S
\arrowtipanchor#S
\beforearrowtipanchor#S
\beforearrowheadanchor#S
\afterarrowtailanchor#S
\getdoublearrowpoints#S
\shaftwidth#S
\arrowboxpoints#S
\halfboxwidth#S
\halfboxheight#S
\westextend#S
\eastextend#S
\northextend#S
\southextend#S
\arrowheadextend#S
\arrowheadindent#S
\arrowtipmiterangle#S
\arrowheadangles#S
\cosecarrowtipmiterangle#S
\beforearrowheadmiterangle#S
\cosecbeforearrowheadmiterangle#S
\beforearrowtipmiterangle#S
\cosecbeforearrowtipmiterangle#S
\arrowboxcorner#S

## shapes.callouts pgflibrary
# loads shapes.symbols pgflibrary
\ellipsecalloutpoints#S
\xpathradius#S
\ypathradius#S
\pointerarc#S
\calloutpointer#S
\pointerradius#S
\calloutpointeranchor#S
\beforecalloutangle#S
\aftercalloutangle#S
\beforecalloutpointer#S
\aftercalloutpointer#S
\sinpointerangle#S
\cospointerangle#S
\rectanglecalloutpoints#S
\xtemp#S
\ytemp#S
\xlength#S
\ylength#S
\pointerwidth#S
\borderpoint#S
\fourthpoint#S
\borderangle#S

## shapes.gates.ee pgflibrary
\northeast#S
\southwest#S

## shapes.gates.ee.IEC pgflibrary
\northeast#S
\southwest#S

## shapes.gates.logic pgflibrary
# no new user commands

## shapes.gates.logic.IEC pgflibrary
# loads shapes.gates.logic
\innerhalfwidth#S
\innerhalfheight#S
# others same as shapes.gates.logic.US

## shapes.gates.logic.US pgflibrary
# loads shapes.gates.logic
\ifpgfgateanchorsuseboundingrectangle#S
\pgfgateanchorsuseboundingrectangletrue#S
\pgfgateanchorsuseboundingrectanglefalse#S
\halfside#S
\outerxsep#S
\outerysep#S
\halfwidth#S
\halfheight#S
\tipanchor#S
\numinputs#S
\invertedradius#S
\outerinvertedradius#S
\dimensions#S
\centerpoint#S
\midpoint#S
\basepoint#S
\externalangle#S
\halflinewidth#S

## shapes.geometric pgflibrary
\centerpoint#S
\radius#S
\pgfsetshapeaspect{value}#S
\pgfshapeaspect#S
\pgfshapeaspectinverse#S
\outernortheast#S
\totalstarpoints#S
\anglestep#S
\calculateradii#S
\outerradius#S
\angletofirstpoint#S
\angletosecondpoint#S
\anchorouterradius#S
\anchorinnerradius#S
\innerradius#S
\outerradius#S
\startangle#S
\midpoint#S
\angle#S
\externalx#S
\externaly#S
\firstangle#S
\secondangle#S
\sides#S
\anchorradius#S
\installtrapeziumparameters#S
\rotate#S
\leftangle#S
\rightangle#S
\halfheight#S
\halfwidth#S
\leftextension#S
\rightextension#S
\outersep#S
\externalradius#S
\basepoint#S
\lowerleftpoint#S
\upperleftpoint#S
\upperrightpoint#S
\lowerrightpoint#S
\lowerleftmiter#S
\upperleftmiter#S
\upperrightmiter#S
\lowerrightmiter#S
\lowerleftborderpoint#S
\upperleftborderpoint#S
\upperrightborderpoint#S
\lowerrightborderpoint#S
\angletolowerleft#S
\angletoupperleft#S
\angletoupperright#S
\angletolowerright#S
\rotatedbasepoint#S
\baseangletolowerleft#S
\baseangletoupperleft#S
\baseangletoupperright#S
\baseangletolowerright#S
\rotatedmidpoint#S
\midangletolowerleft#S
\midangletoupperleft#S
\midangletoupperright#S
\midangletolowerright#S
\referencepoint#S
\installsemicircleparameters#S
\defaultradius#S
\semicircleradius#S
\semicirclecenterpoint#S
\centerpointdiff#S
\arcstartborder#S
\arcendborder#S
\arcstartcorner#S
\arcendcorner#S
\angletoarcstartborder#S
\angletoarcendborder#S
\angletoarcstartcorner#S
\angletoarcendcorner#S
\baseangletoarcstartborder#S
\baseangletoarcendborder#S
\baseangletoarcstartcorner#S
\baseangletoarcendcorner#S
\midangletoarcstartborder#S
\midangletoarcendborder#S
\midangletoarcstartcorner#S
\midangletoarcendcorner#S
\basesemicirclecenterdiff#S
\midsemicirclecenterdiff#S
\firstpoint#S
\secondpoint#S
\sineangle#S
\reciprocalradius#S
\trianglepoints#S
\halfapexangle#S
\tanhalfapexangle#S
\cothalfapexangle#S
\sinhalfapexangle#S
\cosechalfapexangle#S
\apex#S
\lowerleft#S
\apexanchor#S
\lowerleftanchor#S
\lowerrightanchor#S
\installkiteparameters#S
\halfuppervertexangle#S
\halflowervertexangle#S
\sinehalfuppervertexangle#S
\cosechalfuppervertexangle#S
\sinehalflowervertexangle#S
\deltay#S
\kitehalfwidth#S
\kiteheight#S
\kitedepth#S
\toppoint#S
\bottompoint#S
\leftpoint#S
\rightpoint#S
\topmiter#S
\bottommiter#S
\topborderpoint#S
\bottomborderpoint#S
\leftborderpoint#S
\rightborderpoint#S
\angletotoppoint#S
\angletoleftpoint#S
\angletobottompoint#S
\angletorightpoint#S
\baseangletotoppoint#S
\baseangletoleftpoint#S
\baseangletobottompoint#S
\baseangletorightpoint#S
\midangletotoppoint#S
\midangletoleftpoint#S
\midangletobottompoint#S
\midangletorightpoint#S
\installdartparameters#S
\halftipangle#S
\halftailangle#S
\cothalftipangle#S
\dartlength#S
\deltax#S
\taillength#S
\halftailseparation#S
\tippoint#S
\tailcenterpoint#S
\lefttailpoint#S
\righttailpoint#S
\tipmiter#S
\tailcentermiter#S
\righttailmiter#S
\tipborderpoint#S
\tailcenterborderpoint#S
\lefttailborderpoint#S
\righttailborderpoint#S
\angletotip#S
\angletotailcenter#S
\angletolefttail#S
\angletorighttail#S
\baseangletotip#S
\baseangletotailcenter#S
\baseangletolefttail#S
\baseangletorighttail#S
\midangletotip#S
\midangletotailcenter#S
\midangletolefttail#S
\midangletorighttail#S
\installcircularsectorparameters#S
\halfangle#S
\sinehalfangle#S
\cosechalfangle#S
\coshalfangle#S
\cosechalfangle#S
\cothalfangle#S
\centermiter#S
\centeroffset#S
\borderradius#S
\cornerradius#S
\sectorcenter#S
\arcstart#S
\sectorcenterborder#S
\angletosectorcenterborder#S
\ifpgfcylinderusescustomfill#S
\pgfcylinderusescustomfilltrue#S
\pgfcylinderusescustomfillfalse#S
\getcylinderpoints#S
\xradius#S
\yradius#S
\cylindercenter#S
\beforetop#S
\afterbottom#S
\beforetopanchor#S
\afterbottomanchor#S
\externalpoint#S

## shapes.misc pgflibrary
\westarc#S
\eastarc#S
\roundedrectanglepoints#S
\halftextwidth#S
\halftextheight#S
\xoffset#S
\arcwidth#S
\chordwidth#S
\concavexshift#S
\convexxshift#S
\northeastcorner#S
\southeastcorner#S
\southwestcorner#S
\northwestcorner#S
\getchamferedrectanglepoints#S
\tanangle#S
\cotangle#S
\beforenortheast#S
\afternortheast#S
\beforesouthwest#S
\aftersouthwest#S

## shapes.multipart pgflibrary
\pgfnodepartlowerbox#S
\loweranchor#S
\pgfnodeparttwobox#S
\pgfnodepartthreebox#S
\pgfnodepartfourbox#S
\pgfnodepartonebox#S
\pgfnodepartsecondbox#S
\pgfnodepartthirdbox#S
\pgfnodepartfourthbox#S
\ifpgfrectanglesplithorizontal#S
\pgfrectanglesplithorizontaltrue#S
\pgfrectanglesplithorizontalfalse#S
\ifpgfrectanglesplitdrawsplits#S
\pgfrectanglesplitdrawsplitstrue#S
\pgfrectanglesplitdrawsplitsfalse#S
\ifpgfrectanglesplitignoreemptyparts#S
\pgfrectanglesplitignoreemptypartstrue#S
\pgfrectanglesplitignoreemptypartsfalse#S
\ifpgfrectanglesplitusecustomfill#S
\pgfrectanglesplitusecustomfilltrue#S
\pgfrectanglesplitusecustomfillfalse#S
\rectanglesplitparameters#S
\parts#S
\innerxsep#S
\innerysep#S
\radii#S

## shapes.symbols pgflibrary
\calculatestarburstpoints#S
\totalpoints#S
\xinnerradius#S
\yinnerradius#S
\looppoints#S
\thirdpoint#S
\miterlength#S
\angletemp#S
\miterangle#S
\first#S
\second#S
\ifpgfcloudanchorsuseellipse#S
\pgfcloudanchorsuseellipsetrue#S
\pgfcloudanchorsuseellipsefalse#S
\ifpgfcloudignoresaspect#S
\pgfcloudignoresaspecttrue#S
\pgfcloudignoresaspectfalse#S
\getradii#S
\puffs#S
\tempangle#S
\arcradiusquotient#S
\archeightquotient#S
\halfarcangle#S
\coshalfanglestep#S
\xouterradius#S
\youterradius#S
\quarterarc#S
\halfcomplementarc#S
\arc#S
\sechalfcomplementarc#S
\sinhalfcomplementarc#S
\sinquarterarc#S
\cosquarterarc#S
\tanquarterarc#S
\arcendpoint#S
\arcfirstpoint#S
\arcstartpoint#S
\arcrotate#S
\sinarcrotate#S
\cosarcrotate#S
\arcradius#S
\controlscale#S
\controlone#S
\arcmidpoint#S
\halfchordlength#S
\segmentheight#S
\controltwo#S
\arcslope#S
\halfanglestep#S
\endangle#S
\lastangle#S
\miterpoint#S
\anglealpha#S
\anglebeta#S
\miterradius#S
\anchorangle#S
\outerarcradius#S
\circlecenterpoint#S
\installsignalparameters#S
\pointerangle#S
\halfpointerangle#S
\cosechalfpointerangle#S
\quarterpointerangle#S
\cosecquarterpointerangle#S
\secquarterpointerangle#S
\complementquarterpointerangle#S
\pointerapexmiter#S
\tocornermiter#S
\fromcornermiter#S
\north#S
\south#S
\east#S
\west#S
\southeast#S
\northwest#S
\northmiter#S
\southmiter#S
\eastmiter#S
\westmiter#S
\northeastmiter#S
\southeastmiter#S
\southwestmiter#S
\northwestmiter#S
\anchornorth#S
\anchorsouth#S
\anchoreast#S
\anchorwest#S
\anchornortheast#S
\anchorsouthwest#S
\anchorsoutheast#S
\anchornorthwest#S
\tapedimensions#S
\topbendstyle#S
\bottombendstyle#S
\bendyradius#S
\outerbendyradius#S
\innerbendyradius#S
\bendxradius#S
\outerbendxradius#S
\innerbendxradius#S
\outerhalfwidth#S
\cothalfanglein#S
\cothalfangleout#S
\installparameters#S
\tailheight#S
\tailextend#S
\tailangle#S
\tailbottomangle#S
\tailtopangle#S
\base#S
\mid#S

## svg.path pgflibrary
# loads parser pgfmodule
\pgfpathsvg{path}#S

## timelines pgflibrary
# loads animations pgflibrary
\pgftimelinebegin#S
\pgftimelineend#S
\pgftimelineentry{time}{object}{attribute}{value}#S

## animations pgfmodule
## pgfmoduleanimations.code.tex
## └── pgfsysanimations.code.tex
##     └── pgfmoduledecorations.code.tex
# from pgfsysanimations.code.tex
\pgfsysanimationsloaded#S
\pgfsysanimsnapshot{time}#S
\pgfsysanimsnapshotafter{time}#S
\pgfsysanimate{attribute%keyvals}#S
#keyvals:\pgfsysanimate#c,\pgfanimateattribute#c,\pgfanimateattributecode#c
opacity
fillopacity
strokeopacity
visibility
strokecolor
fillcolor
path
linewidth
dash
translate
scale
rotate
skewx
skewy
motion
viewbox
#endkeyvals
\pgfsysanimkeyrestartalways#S
\pgfsysanimkeyrestartnever#S
\pgfsysanimkeyrestartwhennotactive#S
\pgfsysanimkeyrepeat{number}#S
\pgfsysanimkeyrepeatindefinite#S
\pgfsysanimkeyrepeatdur{seconds}#S
\pgfsysanimkeyfreezeatend#S
\pgfsysanimkeyremoveatend#S
\pgfsysanimkeytime{time}{entryx}{entryy}{exitx}{exity}#S
\pgfsysanimkeybase#S
\pgfsysanimkeysnapshotstart{time offset}#S
\pgfsysanimkeyoffset{time offset}{begin or end}#S
\pgfsysanimkeysyncbegin{id}{type}{time offset}{begin or end}#S
\pgfsysanimkeysyncend{id}{type}{time offset}{begin or end}#S
\pgfsysanimkeyevent{id}{type}{event name}{time offset}{begin or end}#S
\pgfsysanimkeyrepeatevent{id}{type}{repeat count}{time offset}{begin or end}#S
\pgfsysanimkeyaccesskey{character}{time offset}{begin or end}#S
\pgfsysanimkeyaccumulate#S
\pgfsysanimkeynoaccumulate#S
\pgfsysanimkeywhom{id}{type}#S
\pgfsysanimkeyrotatealong#S
\pgfsysanimkeymovealong{path}#S
\pgfsysanimkeytipmarkers{start marker}{end marker}#S
\pgfsysanimkeycanvastransform{pre}{post}#S
\pgfsysanimvalcurrent#S
\pgfsysanimvalnone#S
\pgfsysanimvaltext{text}#S
\pgfsysanimvalscalar{number}#S
\pgfsysanimvaldimension{dimension}#S
\pgfsysanimvalcolor{color}#S
\pgfsysanimvalcolorrgb{red}{green}{blue}#S
\pgfsysanimvalcolorcmyk{cyan}{magenta}{yellow}{black}#S
\pgfsysanimvalcolorcmy{cyan}{magenta}{yellow}#S
\pgfsysanimvalcolorgray{gray value}#S
\pgfsysanimvalpath{path commands}#S
\pgfsysanimvaltranslate{x-dimen}{y-dimen}#S
\pgfsysanimvalscale{x-scale}{y-scale}#S
\pgfsysanimvalviewbox{x1}{y1}{x2}{y2}#S
\pgfsysanimvaldash{pattern}{phase}#S
# from pgfmoduleanimations.code.tex
\pgfanimateattribute{attribute%keyvals}{options}#S
\pgfanimateattributecode{attribute%keyvals}{code}#S
\pgfsnapshot{time}#S
\pgfsnapshotafter{time}#S
\pgfparsetime{time}#S
\pgfanimationset{keyvals}#S

## bending pgfmodule
# loads nonlineartransformations pgfmodule and curvilinear pgflibrary
# no new user commands

## datavisualization pgfmodule
# loads oo and shapes pgfmodules and fpu and plothandler pgflibraries
\pgfdvbeforesurvey#S
\pgfdvbeginsurvey#S
\pgfdvendsurvey#S
\pgfdvaftersurvey#S
\pgfdvbeforevisualization#S
\pgfdvbeginvisualization#S
\pgfdvendvisualization#S
\pgfdvaftervisualization#S
\pgfdvpathmovetotoken#S
\pgfdvpathlinetotoken#S
\pgfdvdirectionfromtoken#S
\pgfdvdirectiontotoken#S
\pgfdvdirectionattoken#S
\pgfdatapoint#S
\pgfdvmapdatapointtocanvas#S
\pgfpointdvdatapoint#S
\pgfpointdvlocaldatapoint#S
\ifpgfdvhandled#S
\pgfdvhandledtrue#S
\pgfdvhandledfalse#S
\pgfpathdvmoveto#S
\pgfpathdvlineto#S
\pgfpointdvdirection{code1}{code2}#S
\pgfdata{inline data}#S
\pgfdata[options%keyvals]{inline data}#S
#keyvals:\pgfdata#c
read from file=%<file name%>
inline
format=#TeX code,named,table
every data
new set=%<name%>
store in set=%<name%>
use set=%<name%>
#endkeyvals
\pgfdeclaredataformat{name}{catcodecode}{startcode}{line args}{linecode}{emptylinecode}{endcode}#S
\pgfeoltext#S
\pgfeol#S
\pgfdvmathenter{macro%cmd}{expression}#Sd
\pgfdvmathvalue#S
\pgfdvmathexitbyprinting{variable}#S
\pgfdvmathexitbyscientificformat{macro%cmd}{variable}#Sd
\pgfdvmathexitbyserializing{macro%cmd}{variable}#Sd
\pgfdvmathadd{macro%cmd}{variable1}{variable2}#Sd
\pgfdvmathsub{macro%cmd}{variable1}{variable2}#Sd
\pgfdvmathmul{macro%cmd}{variable1}{variable2}#Sd
\pgfdvmathdiv{macro%cmd}{variable1}{variable2}#Sd
\pgfdvmathmulfixed{macro%cmd}{variable1}{variable2}#Sd
\pgfdvmathln{macro%cmd}{variable}#Sd
\pgfdvmathlog{macro%cmd}{variable}#Sd
\pgfdvmathexp{macro%cmd}{variable}#Sd
\pgfdvmathpowten{macro%cmd}{variable}#Sd
\pgfdvmathfloor{macro%cmd}{variable}#Sd
\pgfdvmathunaryop{macro%cmd}{operation}{variable}#Sd
\pgfdvmathbinop{macro%cmd}{operation}{var1}{var2}#Sd
\pgfdvmathifless{var1}{var2}{true}{false}#S
\ifpgfdvnewstream#S
\pgfdvnewstreamtrue#S
\pgfdvnewstreamfalse#S
\pgfdvvisualizerfilter{text}#S
\pgfdvnamedvisualizerfilter#S
\pgfdvdeclarestylesheet{name}{settings}#S
\ifpgfdvfilterpassed#S
\pgfdvfilterpassedtrue#S
\pgfdvfilterpassedfalse#S
\pgfdvmathalwaysloge#S
\pgfdvmathalwayslnten#S
\pgfdvmathalwayszero#S
\pgfdvmathalwaysone#S

## decorations pgfmodule
\pgfdecoratedcompleteddistance#S
\pgfdecoratedremainingdistance#S
\pgfdecoratedinputsegmentcompleteddistance#S
\pgfdecoratedinputsegmentremainingdistance#S
\pgfdecorationsegmentamplitude#S
\pgfdecorationsegmentlength#S
\pgfdecorationsegmentangle#S
\pgfdecorationsegmentaspect#S
\pgfmetadecorationsegmentamplitude#S
\pgfmetadecorationsegmentlength#S
\ifpgfdecoratepathhascorners#S
\pgfdecoratepathhascornerstrue#S
\pgfdecoratepathhascornersfalse#S
\pgfdeclaredecoration{name}{initial state}{states}#S
\state{name}{code}#S
\state{name}[options%keyvals]{code}#S
#keyvals:\state#c
switch if less than=%<dimen%> to %<new state%>
switch if input segment less than=%<dimen%> to %<new state%>
width=##L
repeat state=%<repetitions%>
next state=%<new state%>
if input segment is closepath={%<options%>}
auto end on length=##L
auto corner on length=##L
persistent precomputation=%<precode%>
persistent postcomputation=%<postcode%>
#endkeyvals
\pgfifdecoration{name}{if code}{else code}#S
\pgfdeclaremetadecoration{name}{initial state}{states}#S
\pgfifmetadecoration{name}{if code}{else code}#S
\decoration{name}#S
\beforedecoration{before code}#S
\afterdecoration{after code}#S
\pgfmetadecoratedpathlength#S
\pgfmetadecoratedcompleteddistance#S
\pgfmetadecoratedinputsegmentcompleteddistance#S
\pgfmetadecoratedinputsegmentremainingdistance#S
\pgfdecoratebeforecode#S
\pgfdecorateaftercode#S
\pgfdecoratepath{name}{path commands}#S
\pgfdecoratecurrentpath{name}#S
\begin{pgfdecoration}{name}#S
\end{pgfdecoration}#S
\pgfdecoration{name}#S
\endpgfdecoration#S
\pgfdecorationpath#S
\pgfdecoratedpath#S
\pgfdecorateexistingpath#S
\pgfdecoratedpathlength#S
\pgfpointdecoratedpathfirst#S
\pgfpointdecoratedpathlast#S
\pgfpointdecoratedinputsegmentfirst#S
\pgfpointdecoratedinputsegmentlast#S
\pgfsetdecorationsegmenttransformation{code}#S
\pgfmetadecoratedremainingdistance#S
\pgfpointmetadecoratedpathfirst#S
\pgfpointmetadecoratedpathlast#S
\pgfdecoratedinputsegmentlength#S
\pgfdecoratedangle#S
\pgfdecoratedinputsegmentstartangle#S
\pgfdecoratedinputsegmentendangle#S
\pgfdecorationcurrentinputsegment#S
\pgfdecorationnextinputsegmentobject#S
\pgfdecorationinputsegmentmoveto#S
\pgfdecorationinputsegmentlineto#S
\pgfdecorationinputsegmentcurveto#S
\pgfdecorationinputsegmentclosepath#S
\pgfdecorationinputsegmentlast#S
\ifpgfdecoraterectangleclockwise#S
\pgfdecoraterectangleclockwisetrue#S
\pgfdecoraterectangleclockwisefalse#S
\begin{pgfmetadecoration}{name}#S
\end{pgfmetadecoration}#S
\pgfmetadecoration{name}#S
\endpgfmetadecoration#S

## matrix pgfmodule
# loads shapes pgfmodule
\ifpgfmatrix#S
\pgfmatrixtrue#S
\pgfmatrixfalse#S
\pgfmatrixcurrentrow#S
\pgfmatrixcurrentcolumn#S
\pgfmatrixbeforeassemblenode{code}#S
\pgfsetmatrixrowsep{sep list}#S
\pgfsetmatrixcolumnsep{sep list}#S
\pgfmatrixrowsep#S
\pgfmatrixcolumnsep#S
\pgfmatrix{shape}{anchor}{name}{usage}{shift}{precode}{matrix cells}#S
\pgfmatrixnextcell#S
\pgfmatrixnextcell[additional sep list]#S
\pgfmatrixbegincode#S
\pgfmatrixendcode#S
\pgfmatrixemptycode#S
\pgfmatrixendrow#S
\pgfmatrixendrow[additional sep list]#S

## nonlineartransformations pgfmodule
\pgftransformnonlinearflatness#S
\pgfsettransformnonlinearflatness{dimen%l}#S

## oo pgfmodule
\pgfooclass{class%plain}{body}#S
\pgfooclass(list of superclasses){class%plain}{body}#S
\attribute#S
\method#S
\pgfoosuper(%<class,object handle%>).%<<method name>%>(%<args%>)#S
\pgfoovalueof{attribute}#S
\pgfooget{attribute}{macro%cmd}#Sd
\pgfooset{attribute}{value}#S
\pgfooeset{attribute}{value}#S
\pgfoolet{attribute}{macro}#S
\pgfooappend{attribute}{value}#S
\pgfooprefix{attribute}{value}#S
\pgfoonew{cmd}#Sd
\pgfoothis#S
\pgfooobj{id}#S
\pgfoogc#S

## parser pgfmodule
\pgfparserparse{parser name}#S
\pgfparserdef{parser name}{state}{symbol meaning}{action}#S
\pgfparserdef{parser name}{state}{symbol meaning}[args]{action}#S
\pgfparserlet{parser1}{state1}{meaning1}{meaning2}#S
\pgfparserlet{parser1}{state1}{meaning1}[opt1][opt2]{meaning2}#S
\pgfparserdefunknown{parser name}{state}{action}#S
\pgfparserdeffinal{parser name}{action}#S
\pgfparserswitch{state}#S
\pgfparserifmark{arg}{true}{false}#S
\pgfparserreinsert#S
\pgfparserstate#S
\pgfparsertoken#S
\pgfparserletter#S
\pgfparserset{options%keyvals}#S
#keyvals:\pgfparserset#c
silent#true,false
status#true,false
#endkeyvals

## plot pgfmodule
\pgfplotstreamstart#S
\pgfplotstreampoint{point}#S
\pgfplotstreampointoutlier{point}#S
\pgfplotstreampointundefined#S
\pgfplotstreamnewdataset#S
\pgfplotstreamspecial{text}#S
\pgfplotstreamend#S
\pgfdeclareplothandler{macro%cmd}{args}{options%keyvals}#Sd
#keyvals:\pgfdeclareplothandler#c
start=%<code%>
end=%<code%>
point=%<code%>
jump=%<code%>
special=%<code%>
point macro=%<macro%>
special macro=%<macro%>
start macro=%<macro%>
end macro=%<macro%>
jump macro=%<macro%>
#endkeyvals
\pgfsetlinetofirstplotpoint#S
\pgfsetmovetofirstplotpoint#S
\pgfplothandlerlineto#S
\pgfplothandlerpolygon#S
\pgfplothandlerdiscard#S
\pgfplothandlerrecord{macro%cmd}#Sd
\pgfplotxyfile{file}#S
\pgfplotxyzfile{file}#S
\pgfplotgnuplot{gnuplot function}#S
\pgfplotgnuplot[prefix]{gnuplot function}#S
\pgfplotfunction{variable%cmd}{sample list}{point}#Sd

## shapes pgfmodule
\pgfnodeparttextbox#S
\pgfmultipartnode{shape}{anchor}{name}{path usage cmd}#S
\pgfnode{shape}{anchor}{label text}{name}{path usage cmd}#S
\pgfpositionnodelater{macro}#S
\pgfpositionnodelatername#S
\pgfpositionnodelaterminx#S
\pgfpositionnodelatermaxx#S
\pgfpositionnodelaterminy#S
\pgfpositionnodelatermaxy#S
\ifpgflatenodepositioning#S
\pgflatenodepositioningtrue#S
\pgflatenodepositioningfalse#S
\pgfpositionnodelaterbox#S
\pgfpositionnodenow{coordinate}#S
\pgffakenode{node name}#S
\pgfnodepostsetupcode{node name}{code}#S
\pgfnodealias{new name}{existing name}#S
\pgfnoderename{new name}{existing name}#S
\pgfcoordinate{name}{coordinate}#S
\pgfdeclaregenericanchor{anchor}{code}#S
\pgfpointanchor{node}{anchor}#S
\pgfpointshapeborder{node}{point}#S
\pgfgetnodeparts{macro}{shape name}#Sd
\pgfdeclareshape{shape name}{shape spec}#S
\centerpoint#S
\ifpgfshapeborderusesincircle#S
\pgfshapeborderusesincircletrue#S
\pgfshapeborderusesincirclefalse#S
\northeast#S
\southwest#S
\radius#S
\nodeparts{list of node parts}#S
\savedanchor{cmd}{code}#Sd
\saveddimen{cmd}{code}#Sd
\savedmacro{cmd}{code}#Sd
\addtosavedmacro{macro}#S
\anchor{name}{code}#S
\deferredanchor{name}{code}#S
\anchorborder{code}#S
\backgroundpath{code}#S
\foregroundpath{code}#S
\behindbackgroundpath{code}#S
\beforebackgroundpath{code}#S
\behindforegroundpath{code}#S
\beforeforegroundpath{code}#S
\inheritsavedanchors#S
\inheritsavedanchors[from={%<shape name%>}]#S
\inheritbehindbackgroundpath#S
\inheritbehindbackgroundpath[from={%<shape name%>}]#S
\inheritbackgroundpath#S
\inheritbackgroundpath[from={%<shape name%>}]#S
\inheritbeforebackgroundpath#S
\inheritbeforebackgroundpath[from={%<shape name%>}]#S
\inheritbehindforegroundpath#S
\inheritbehindforegroundpath[from={%<shape name%>}]#S
\inheritforegroundpath#S
\inheritforegroundpath[from={%<shape name%>}]#S
\inheritbeforeforegroundpath#S
\inheritbeforeforegroundpath[from={%<shape name%>}]#S
\inheritanchor#S
\inheritanchor[from={%<shape name%>}]{name}#S
\inheritanchorborder#S
\inheritanchorborder[from={%<shape name%>}]#S

## sorting pgfmodule
\pgfsortingbuckets#S
\pgfsortinginit{number of buckets}#S
\pgfsortinginsert{bucket}{code}#S
\pgfsortingexecute#S
