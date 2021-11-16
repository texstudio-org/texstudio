# pgfcore package
# Benito van der Zander, 14 May 2011, init contribute
# jsundermeyer@sf.net, 16 Jul 2014, 19 Sep 2015
# Tim Hoffmann, 1 Dec 2016, 9 Feb 2017
# muzimuzhi, 8 Jul 2020
# Matthew Bertucci 11/14/2021 for v3.1.9a

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
#     │   └── pgfcoreexternal.code.tex
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
\pgfimage[options%keyvals]{imagefile}#*
\pgfimage{imagefile}#*
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
