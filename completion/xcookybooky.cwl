# xcookybooky package
# Matthew Bertucci 2022/10/02 for v1.5

#include:tikz
#include:graphicx
#include:xcolor
#include:ifsym
# loads clock, misc, and weather options of ifsym
#include:cookingsymbols
#include:wrapfig
#include:iflang
#include:ifthen
#include:xkeyval
#include:lettrine
#include:fancyhdr
#include:units
#include:eso-pic
#include:picture
#include:tabulary
#include:framed

#keyvals:\usepackage/xcookybooky#c
handwritten
nowarnings
myconfig
#endkeyvals

#ifOption:handwritten
#include:emerald
#endif

\begin{recipe}{name%text}
\begin{recipe}[options%keyvals]{name%text}
\end{recipe}

#keyvals:\begin{recipe}
preparationtime={%<time%>}
bakingtime={%<time%>}
bakingtemperature={%<temperature%>}
portion={%<portion%>}
calory={%<calory%>}
source={%<source%>}
#endkeyvals

\graph{keyvals}

#keyvals:\graph
small=%<imagefile%>
smallpicturewidth=##L
bigpicturewidth=##L
big=%<imagefile%>
#endkeyvals

\ingredients{ingredients%text}
\ingredients[lines]{ingredients%text}
\preparation{steps%text}
\step
\introduction{text}
\suggestion{text}
\suggestion[headline%text]{text}
\portion{value}
\portion[unit]{value}
\hint{text}

\bakingtemperature{keyvals}

#keyvals:\bakingtemperature
fanoven=%<temperature%>
topbottomheat=%<temperature%>
topheat=%<temperature%>
bottomheat=%<temperature%>
gasstove=%<temperature%>
#endkeyvals

\setRecipeColors{keyvals}

#keyvals:\setRecipeColors
recipename=#%color
intro=#%color
ing=#%color
inghead=#%color
prep=#%color
prephead=#%color
suggestion=#%color
suggestionhead=#%color
separationgraph=#%color
hint=#%color
hinthead=#%color
hintline=#%color
numeration=#%color
#endkeyvals

DarkGreen#B
DarkBlue#B
DarkGray#B

\setRecipeLengths{keyvals}

#keyvals:\setRecipeLengths
pictureheight=##L
bigpicturewidth=##L
smallpicturewidth=##L
introductionwidth=##L
preparationwidth=##L
ingredientswidth=##L
#endkeyvals

\setRecipeSizes{keyvals}

#keyvals:\setRecipeSizes
recipename=%<fontsize commands%>
intro=%<fontsize commands%>
ing=%<fontsize commands%>
inghead=%<fontsize commands%>
prep=%<fontsize commands%>
prephead=%<fontsize commands%>
suggestion=%<fontsize commands%>
hint=%<fontsize commands%>
hinthead=%<fontsize commands%>
#endkeyvals

\setRecipenameFont{family}{encoding}{series}{shape}

\setHeadlines{keyvals}

#keyvals:\setHeadlines
inghead=%<text%>
prephead=%<text%>
hinthead=%<text%>
continuationhead=%<text%>
continuationfoot=%<text%>
preparationtime=%<text%>
bakingtime=%<text%>
bakingtemperature=%<text%>
portion=%<text%>
portionvalue=%<text%>
calory=%<text%>
source=%<text%>
#endkeyvals

\setBackgroundPicture{imagefile}#g
\setBackgroundPicture[options%keyvals]{imagefile}#g

#keyvals:\setBackgroundPicture
width=##L
height=##L
x=##L
y=##L
orientation=#default,pagecenter,textcenter,stockcenter
#endkeyvals

\postingredients{code}#*
\postpreparation{code}#*
\pregraph{code}#*
\preingredients{code}#*
\prepreparation{code}#*
\prerecipeoverview{code}#*
\pretitle{code}#*
\recipesection{title}#*L4
\recipesection[short title]{title}#*L4
\thestep#*

# from clock option of ifsym
\ifclkfamily#*
\textifclk{text%plain}#*
\showclock{hour}{minute}
\Taschenuhr
\VarTaschenuhr
\StopWatchStart
\StopWatchEnd
\Interval
\Wecker
\VarClock

# from misc option of ifsym
\Letter
\Telephone
\SectioningDiamond
\FilledSectioningDiamond
\PaperPortrait
\PaperLandscape
\Cube{integer}
\Irritant
\Fire
\Radiation
\StrokeOne
\StrokeTwo
\StrokeThree
\StrokeFour
\StrokeFive

# from weather option of ifsym
\textweathersymbol{slot}#*
\Sun
\HalfSun
\NoSun
\Fog
\ThinFog
\Rain
\WeakRain
\Hail
\Sleet
\Snow
\Lightning
\Cloud
\RainCloud
\WeakRainCloud
\SunCloud
\SnowCloud
\FilledCloud
\FilledRainCloud
\FilledWeakRainCloud
\FilledSunCloud
\FilledSnowCloud
\wind{integer}{angle}{speed}
\Thermo{integer}