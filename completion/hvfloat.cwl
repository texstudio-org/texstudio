# hvfloat package
# Matthew Bertucci 11/24/2021 for v2.34

#include:caption
#include:varwidth
#include:subcaption
#include:atbegshi
#include:picture
#include:trimclip
#include:expl3
#include:multido
#include:graphicx
#include:xkeyval
#include:ifoddpage
#include:afterpage
#include:stfloats

#ifOption:hyperref
#include:hyperref
#endif

\hvFloatSet{options%keyvals}
\hvFloatSetDefaults

\hvFloat{float type}{object}{caption%text}{label}#l
\hvFloat{float type}{object}[short caption%text]{caption%text}{label}#*l
\hvFloat[options%keyvals]{float type}{object}{caption%text}{label}#l
\hvFloat[options%keyvals]{float type}{object}[short caption%text]{caption%text}{label}#*l
\hvFloat*{float type}{object}{caption%text}{label}#l
\hvFloat*{float type}{object}[short caption%text]{caption%text}{label}#*l
\hvFloat*[options%keyvals]{float type}{object}{caption%text}{label}#l
\hvFloat*[options%keyvals]{float type}{object}[short caption%text]{caption%text}{label}#*l

\figcaption{caption%text}
\figcaption[short caption%text]{caption%text}
\tabcaption{caption%text}
\tabcaption[short caption%text]{caption%text}
\tabcaptionbelow{caption%text}
\tabcaptionbelow[short caption%text]{caption%text}

\hvDefFloatStyle{name}{options%keyvals}

#keyvals:\hvFloatSet,\hvFloat,\hvFloat*,\hvDefFloatStyle
floatPos=%<float pos%>
rotAngle=%<angle%>
capWidth=%<n, w, or <number>%>
capAngle=%<integer%>
capPos=#before,top,left,after,bottom,right,inner,outer,evenPage
capVPos=#bottom,center,top
objectPos=#left,center,right
objectAngle=%<integer%>
floatCapSep=##L
useOBox#true,false
onlyText#true,false
nonFloat#true,false
wide#true,false
objectFrame#true,false
style=%<style%>
capFormat={%<caption settings%>}
subcapFormat={%<subcaption settings%>}
fullpage#true,false
FullPage#true,false
FULLPAGE#true,false
doublePage#true,false
doublePAGE#true,false
doubleFULLPAGE#true,false
vFill#true,false
sameHeight#true,false
multiFloat#true,false
subFloat#true,false
separatorLine#true,false
bindCorr=##L
#endkeyvals

\begin{hvFloatEnv}
\begin{hvFloatEnv}[width]
\end{hvFloatEnv}

\IncludeGraphics{imagefile}#*g
\IncludeGraphics[keyvals]{imagefile}#*g

#keyvals:\includegraphics,\IncludeGraphics
columnWidth#true,false
fullpage#true,false
FullPage#true,false
FULLPAGE#true,false
doubleFULLPAGE#true,false
doublefullPage#true,false
doubleFULLPAGEbindCorr#true,false
#endkeyvals

#keyvals:\IncludeGraphics
alt=
bb=
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=
trim=
angle=
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=
clip#true,false
draft#true,false
type=
ext=
read=
command=
quiet
page=
interpolate#true,false
decodearray=
#endkeyvals

\LenToUnit{length}#*
\drawSepLine#*
\getMultiCaptionAndLabel#*
\getMultiObjectAndLabel#*
\getMultiSubCaptionAndLabel#*
\getMultiSubObjectAndLabel#*
\getSingleCaptionAndLabel#*
\hvObjectBox#*
\restoreCaptionSkip#*
\saveCaptionSkip#*
\setBottomCaption#*
\setDefaults#*
\setPageObject#*
\defhvstyle{name}{options}#S
\hvFloatFileVersion#S