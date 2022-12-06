# msc package
# Matthew Bertucci 2022/05/16 for v2.00

#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.markings
#include:tikzlibraryshapes.misc
#include:tikzlibraryshapes.geometric
#include:tikzlibraryshapes.symbols
#include:xstring
#include:calc

\mscset{options%keyvals}
\begin{msc}{name%text}#\pictureHighlight
\begin{msc}[options%keyvals]{name%text}
\begin{msc}[options%keyvals][pos]{name%text}
\end{msc}
\nextlevel
\nextlevel[level offset]
\declinst{nickname}{instance name above}{instance name within}
\declinst*{nickname}{instance name above}{instance name within}
\mess{name}{sender}{receiver}
\mess{name}{sender}{receiver}[level offset]
\mess[options%keyvals]{name}{sender}{receiver}
\mess[options%keyvals]{name}{sender}{receiver}[level offset]
\mess*{name}{sender}{receiver}
\mess*{name}{sender}{receiver}[level offset]
\mess*[options%keyvals]{name}{sender}{receiver}
\mess*[options%keyvals]{name}{sender}{receiver}[level offset]
\msccomment{text}{instance}
\msccomment[options%keyvals]{text}{instance}
\action{name}{instance}
\action[options%keyvals]{name}{instance}
\action*{name}{instance}
\action*[options%keyvals]{name}{instance}
\naction{name}{instance}
\naction[options%keyvals]{name}{instance}
\naction*{name}{instance}
\naction*[options%keyvals]{name}{instance}
\settimer{name}{instance}
\settimer[options%keyvals]{name}{instance}
\timeout{name}{instance}
\settimer[options%keyvals]{name}{instance}
\stoptimer{name}{instance}
\settimer[options%keyvals]{name}{instance}
\settimeout{name}{instance}
\settimeout{name}{instance}[offset]
\settimeout[options%keyvals]{name}{instance}
\settimeout[options%keyvals]{name}{instance}[offset]
\setstoptimer{name}{instance}
\setstoptimer{name}{instance}[offset]
\setstoptimer[options%keyvals]{name}{instance}
\setstoptimer[options%keyvals]{name}{instance}[offset]
\mscmark{name}{instance}
\mscmark[options%keyvals]{name}{instance}
\measure{name}{instance1}{instance2}
\measure{name}{instance1}{instance2}[offset]
\measure[options%keyvals]{name}{instance1}{instance2}
\measure[options%keyvals]{name}{instance1}{instance2}[offset]
\measure*{name}{instance1}{instance2}
\measure*{name}{instance1}{instance2}[offset]
\measure*[options%keyvals]{name}{instance1}{instance2}
\measure*[options%keyvals]{name}{instance1}{instance2}[offset]
\measurestart{name}{instance}{gate}
\measurestart[options%keyvals]{name}{instance}{gate}
\measurestart*{name}{instance}{gate}
\measurestart*[options%keyvals]{name}{instance}{gate}
\measureend{name}{instance}{gate}
\measureend[options%keyvals]{name}{instance}{gate}
\measureend*{name}{instance}{gate}
\measureend*[options%keyvals]{name}{instance}{gate}
\lost{name}{gate}{instance}
\lost[options%keyvals]{name}{gate}{instance}
\found{name}{gate}{instance}
\found[options%keyvals]{name}{gate}{instance}
\condition{text}{instance list}
\condition[options%keyvals]{text}{instance list}
\condition*{text}{instance list}
\condition*[options%keyvals]{text}{instance list}
\ncondition{text}{instance list}
\ncondition[options%keyvals]{text}{instance list}
\ncondition*{text}{instance list}
\ncondition*[options%keyvals]{text}{instance list}
\order{sender}{receiver}
\order{sender}{receiver}[level offset]
\order[options%keyvals]{sender}{receiver}
\order[options%keyvals]{sender}{receiver}[level offset]
\regionstart{type}{instance}
\regionstart[options%keyvals]{type}{instance}
\regionend{instance}
\dummyinst{created instance}
\dummyinst[options%keyvals]{created instance}
\startinst{instance name}{text above}{text inside}
\startinst[options%keyvals]{instance name}{text above}{text inside}
\create{name}{creator}{instance name}{text above}{text inside}
\create[options%keyvals]{name}{creator}{instance name}{text above}{text inside}
\stop{instance}
\stop[options%keyvals]{instance}
\stop*{instance}
\stop*[options%keyvals]{instance}
\referencestart{nickname}{text}{left instance}{right instance}
\referencestart[options%keyvals]{nickname}{text}{left instance}{right instance}
\referenceend{nickname}
\referenceend[options%keyvals]{nickname}
\inlinestart{nickname}{operator}{left instance}{right instance}
\inlinestart[options%keyvals]{nickname}{operator}{left instance}{right instance}
\inlineseparator{nickname}
\inlineseparator[options%keyvals]{nickname}
\inlineend{nickname}
\inlineend[options%keyvals]{nickname}
\inlineend*{nickname}
\inlineend*[options%keyvals]{nickname}
\gate{gate name}{instance name}
\gate[options%keyvals]{gate name}{instance name}
\gate*{gate name}{instance name}
\gate*[options%keyvals]{gate name}{instance name}
\begin{hmsc}{name%text}#\pictureHighlight
\begin{hmsc}{name%text}(llx,lly)(urx,ury)
\begin{hmsc}[options%keyvals]{name%text}
\begin{hmsc}[options%keyvals]{name%text}(llx,lly)(urx,ury)
\end{hmsc}
\hmscstartsymbol{nickname}
\hmscstartsymbol{nickname}(x,y)
\hmscstartsymbol[options%keyvals]{nickname}
\hmscstartsymbol[options%keyvals]{nickname}(x,y)
\hmscendsymbol{nickname}
\hmscendsymbol{nickname}(x,y)
\hmscendsymbol[options%keyvals]{nickname}
\hmscendsymbol[options%keyvals]{nickname}(x,y)
\hmscreference{nickname}{text}
\hmscreference{nickname}{text}(x,y)
\hmscreference[options%keyvals]{nickname}{text}
\hmscreference[options%keyvals]{nickname}{text}(x,y)
\hmsccondition{nickname}{text}
\hmsccondition{nickname}{text}(x,y)
\hmsccondition[options%keyvals]{nickname}{text}
\hmsccondition[options%keyvals]{nickname}{text}(x,y)
\hmscconnection{nickname}
\hmscconnection{nickname}(x,y)
\hmscconnection[options%keyvals]{nickname}
\hmscconnection[options%keyvals]{nickname}(x,y)
\begin{mscdoc}{name%text}(llx,lly)(urx,ury)#\pictureHighlight
\begin{mscdoc}[headerpos]{name%text}(llx,lly)(urx,ury)
\end{mscdoc}
\reference{text}(x,y)
\separator{y}
\mscdocreferenceheight#*
\mscdocreferencewidth#*
\topnamedist#*
\coregionstart{nickname}
\coregionend{nickname}

#keyvals:\mscset#c,\begin{msc}#c,\mess#c,\mess*#c,\msccomment#c,\action#c,\action*#c,\naction#c,\naction*#c,\settimer#c,\timeout#c,\stoptimer#c,\settimeout#c,\setstoptimer#c,\mscmark#c,\measure#c,\measure*#c,\measurestart#c,\measurestart*#c,\measureend#c,\measureend*#c,\lost#c,\found#c,\condition#c,\condition*#c,\ncondition#c,\ncondition*#c,\order#c,\regionstart#c,\dummyinst#c,\startinst#c,\create#c,\stop#c,\stop*#c,\referencestart#c,\referenceend#c,\inlinestart#c,\inlineseparator#c,\inlineend#c,\inlineend*#c,\gate#c,\gate*#c,\begin{hmsc}#c,\hmscstartsymbol#c,\hmscendsymbol#c,\hmscreference#c,\hmsccondition#c,\hmscconnection#c
above
above left
above right
action height=##L
action width=##L
anchor=#north,south,east,west,north east,north west,south east,south west
arrow scale=%<factor%>
below
below left
below right
condition height=##L
condition overlap=##L
draw frame
draw frame=#%color
draw grid
draw grid=#grid,color grid,none
draw head=#%color
east hmsc margin=##L
environment distance=##L
first level height=##L
foot distance=##L
foot height=##L
gate symbol radius=##L
head height=##L
head top distance=##L
hmsc condition height=##L
hmsc condition width=##L
hmsc connection radius=##L
hmsc keyword=%<keyword%>
hmsc margin=##L
hmsc symbol width=##L
instance distance=##L
instance width=##L
l
label distance=##L
label position=#above,below,above left,above right,below left,below right,left,right
last level height=##L
left
left environment distance=##L
left inline overlap=##L
left reference overlap=##L
level height=##L
level shift=%<integer%>
lost symbol radius=##L
measure distance=##L
measure symbol width=##L
msc keyword=%<keyword%>
msccomment distance=##L
north hmsc margin=##L
offset=%<integer%>
pos=%<real%>
position=#above,below
r
reference height=##L
reference width=##L
right
right environment distance=##L
right inline overlap=##L
right reference overlap=##L
self message width=##L
side=#left,right
small values
south hmsc margin=##L
stop width=##L
timer width=##L
title distance=##L
title position=#left,right,center
title top distance=##L
west hmsc margin=##L
#endkeyvals

# not documented
\mscget{option}#*
\actionheight#*
\actionwidth#*
\addDdraw{instance1}{instance2}{level}{code}#*
\adddraw{instance}{level}{code}#*
\bottomfootdist#*
\conditionheight#*
\conditionoverlap#*
\drawframe{yes|no}#*
\drawinstfoot{yes|no}#*
\drawinsthead{yes|no}#*
\envinstdist#*
\firstlevelheight#*
\gatesymbolradius#*
\hmscconditionheight#*
\hmscconditionwidth#*
\hmscconnectionradius#*
\hmsckeywordstyle#*
\hmscreferenceheight#*
\hmscreferencewidth#*
\hmscstartsymbolwidth#*
\inlineoverlap#*
\instbarwidth#*
\instdist#*
\instfootheight#*
\instheadheight#*
\inststart#*
\inststop#*
\instwidth#*
\labeldist#*
\lastlevelheight#*
\leftnamedist#*
\levelheight#*
\lostsymbolradius#*
\markdist#*
\measuredist#*
\measuresymbolwidth#*
\messarrowscale{factor}#*
\msccommentdist#*
\mscdate#S
\mscdockeywordstyle
\mscdockeywordstyle{arg1}
\mscgetx{arg1}{arg2}
\mscgety{arg1}{arg2}
\msckeywordstyle{text}#*
\mscunit#*
\mscversion#S
\nogrid#*
\referenceoverlap#*
\regionbarwidth#*
\selfmesswidth#*
\sethmsckeyword{keyword}#*
\setmscdockeyword{keyword}#*
\setmsckeyword{keyword}#*
\setmscscale{factor}#*
\setmscvalues{large|normal|small}#*
\showgrid#*
\stopwidth#*
\thickness#*
\timerwidth#*
\topheaddist#*
