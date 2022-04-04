# flowfram package
# Matthew Bertucci 3/31/2022 for v1.17

#include:ifthen
#include:xkeyval
#include:graphics
#include:afterpage
#include:xfor
#include:etoolbox
#include:color

#keyvals:\usepackage/flowfram#c
pages=#relative,absolute
draft
final
thumbtabs=#title,number,both,none
LR
RL
rotate#true,false
color#true,false
verbose#true,false
#endkeyvals

\begin{staticfigure}
\end{staticfigure}
\begin{statictable}
\end{statictable}

\ifshowtypeblock#*
\showtypeblocktrue
\showtypeblockfalse
\ifshowmargins#*
\showmarginstrue
\showmarginsfalse
\ifshowframebbox#*
\showframebboxtrue
\showframebboxfalse
\flowframeshowlayout

\chapterfirstpagestyle#*
\ffprechapterhook#*

\newflowframe{width}{height}{x}{y}
\newflowframe{width}{height}{x}{y}[label]
\newflowframe[page list]{width}{height}{x}{y}
\newflowframe[page list]{width}{height}{x}{y}[label]
\newflowframe*{width}{height}{x}{y}
\newflowframe*{width}{height}{x}{y}[label]
\newflowframe*[page list]{width}{height}{x}{y}
\newflowframe*[page list]{width}{height}{x}{y}[label]
\getflowlabel{IDN}
\getflowid{cmd}{IDL}#d

\framebreak
\fftolerance#*

\newstaticframe{width}{height}{x}{y}
\newstaticframe{width}{height}{x}{y}[label]
\newstaticframe[page list]{width}{height}{x}{y}
\newstaticframe[page list]{width}{height}{x}{y}[label]
\newstaticframe*{width}{height}{x}{y}
\newstaticframe*{width}{height}{x}{y}[label]
\newstaticframe*[page list]{width}{height}{x}{y}
\newstaticframe*[page list]{width}{height}{x}{y}[label]
\getstaticlabel{IDN}
\getstaticid{cmd}{IDL}#d
\setstaticcontents{IDN}{contents%text}
\setstaticcontents*{IDL}{contents%text}
\begin{staticcontents}{IDN}
\end{staticcontents}
\begin{staticcontents*}{IDL}
\end{staticcontents*}

\newdynamicframe{width}{height}{x}{y}
\newdynamicframe{width}{height}{x}{y}[label]
\newdynamicframe[page list]{width}{height}{x}{y}
\newdynamicframe[page list]{width}{height}{x}{y}[label]
\newdynamicframe*{width}{height}{x}{y}
\newdynamicframe*{width}{height}{x}{y}[label]
\newdynamicframe*[page list]{width}{height}{x}{y}
\newdynamicframe*[page list]{width}{height}{x}{y}[label]
\getdynamiclabel{IDN}
\getdynamicid{cmd}{IDL}#d
\setdynamiccontents{IDN}{contents%text}
\setdynamiccontents*{IDL}{contents%text}
\begin{dynamiccontents}{IDN}
\end{dynamiccontents}
\begin{dynamiccontents*}{IDL}
\end{dynamiccontents*}
\appenddynamiccontents{IDN}{contents%text}
\appenddynamiccontents*{IDL}{contents%text}

\dfchaphead{IDN}
\dfchaphead*{IDL}
\DFchapterstyle{text}#*
\DFschapterstyle{text}#*

\makedfheaderfooter

\continueonframe{ID}
\continueonframe[continuation text%text]{ID}
\ffcontinuedtextlayout{text}#*
\ffcontinuedtextfont{text}#*

\setflowframe{IDN list}{keyvals}
\setflowframe*{IDL list}{keyvals}
\setallflowframes{keyvals}
\setstaticframe{IDN list}{keyvals}
\setstaticframe*{IDL list}{keyvals}
\setallstaticframes{keyvals}
\setdynamicframe{IDN list}{keyvals}
\setdynamicframe*{IDL list}{keyvals}
\setalldynamicframes{keyvals}

\ffswapoddeven{IDN}
\sfswapoddeven{IDN}
\dfswapoddeven{IDN}

\flowsetpagelist{IDN}{pages}
\dynamicsetpagelist{IDN}{pages}
\staticsetpagelist{IDN}{pages}
\flowsetexclusion{IDN}{pages}
\dynamicsetexclusion{IDN}{pages}
\staticsetexclusion{IDN}{pages}
\flowaddexclusion{IDN}{pages}
\dynamicaddexclusion{IDN}{pages}
\staticaddexclusion{IDN}{pages}

\simpar#*

\flowswitchonnext{IDN list}
\flowswitchonnext*{IDL list}
\flowswitchoffnext{IDN list}
\flowswitchoffnext*{IDL list}
\flowswitchonnextodd{IDN list}
\flowswitchonnextodd*{IDL list}
\flowswitchoffnextodd{IDN list}
\flowswitchoffnextodd*{IDL list}
\flowswitchonnextonly{IDN list}
\flowswitchonnextonly*{IDL list}
\flowswitchoffnextonly{IDN list}
\flowswitchoffnextonly*{IDL list}
\flowswitchonnextoddonly{IDN list}
\flowswitchonnextoddonly*{IDL list}
\flowswitchoffnextoddonly{IDN list}
\flowswitchoffnextoddonly*{IDL list}
\dynamicswitchonnext{IDN list}
\dynamicswitchonnext*{IDL list}
\dynamicswitchoffnext{IDN list}
\dynamicswitchoffnext*{IDL list}
\dynamicswitchonnextodd{IDN list}
\dynamicswitchonnextodd*{IDL list}
\dynamicswitchoffnextodd{IDN list}
\dynamicswitchoffnextodd*{IDL list}
\dynamicswitchonnextonly{IDN list}
\dynamicswitchonnextonly*{IDL list}
\dynamicswitchoffnextonly{IDN list}
\dynamicswitchoffnextonly*{IDL list}
\dynamicswitchonnextoddonly{IDN list}
\dynamicswitchonnextoddonly*{IDL list}
\dynamicswitchoffnextoddonly{IDN list}
\dynamicswitchoffnextoddonly*{IDL list}
\staticswitchonnext{IDN list}
\staticswitchonnext*{IDL list}
\staticswitchoffnext{IDN list}
\staticswitchoffnext*{IDL list}
\staticswitchonnextodd{IDN list}
\staticswitchonnextodd*{IDL list}
\staticswitchoffnextodd{IDN list}
\staticswitchoffnextodd*{IDL list}
\staticswitchonnextonly{IDN list}
\staticswitchonnextonly*{IDL list}
\staticswitchoffnextonly{IDN list}
\staticswitchoffnextonly*{IDL list}
\staticswitchonnextoddonly{IDN list}
\staticswitchonnextoddonly*{IDL list}
\staticswitchoffnextoddonly{IDN list}
\staticswitchoffnextoddonly*{IDL list}

\computeleftedgeodd{length}
\computeleftedgeeven{length}
\computetopedge{length}
\computebottomedge{length}
\computerightedgeodd{length}
\computerightedgeeven{length}
\computeflowframearea{IDN list}
\computeflowframearea*{IDL list}

\getstaticbounds{IDN}
\getstaticbounds*{IDL}
\getflowbounds{IDN}
\getflowbounds*{IDL}
\getdynamicbounds{IDN}
\getdynamicbounds*{IDL}
\ffareawidth
\ffareaheight
\ffareax
\ffareay

\relativeframelocation{type1%keyvals}{IDN1}{type2}{IDN2}
\relativeframelocation*{type1%keyvals}{IDL1}{type2}{IDL2}
\FFaboveleft#*
\FFaboveright#*
\FFbelowleft#*
\FFbelowright#*
\FFleft#*
\FFright#*
\FFabove#*
\FFbelow#*
\FFoverlap#*

\reldynamicloc{IDN1}{IDN2}
\reldynamicloc*{IDN1}{IDN2}
\relstaticloc{IDN1}{IDN2}
\relstaticloc*{IDN1}{IDN2}
\relflowloc{IDN1}{IDN2}
\relflowloc*{IDN1}{IDN2}

\ifffvadjust#*
\ffvadjusttrue
\ffvadjustfalse
\onecolumn[pages]
\twocolumn[pages]
\Ncolumn{n}
\Ncolumn[pages]{n}
\onecolumninarea{width}{height}{x}{y}
\onecolumninarea[pages]{width}{height}{x}{y}
\twocolumninarea{width}{height}{x}{y}
\twocolumninarea[pages]{width}{height}{x}{y}
\Ncolumninarea{n}{width}{height}{x}{y}
\Ncolumninarea[pages]{n}{width}{height}{x}{y}

\onecolumntopinarea{type%keyvals}{H}{width}{height}{x}{y}
\onecolumntopinarea[pages]{type%keyvals}{H}{width}{height}{x}{y}
\twocolumntopinarea{type%keyvals}{H}{width}{height}{x}{y}
\twocolumntopinarea[pages]{type%keyvals}{H}{width}{height}{x}{y}
\Ncolumntopinarea{type%keyvals}{n}{H}{width}{height}{x}{y}
\Ncolumntopinarea[pages]{type%keyvals}{n}{H}{width}{height}{x}{y}
\onecolumnbottominarea{type%keyvals}{H}{width}{height}{x}{y}
\onecolumnbottominarea[pages]{type%keyvals}{H}{width}{height}{x}{y}
\twocolumnbottominarea{type%keyvals}{H}{width}{height}{x}{y}
\twocolumnbottominarea[pages]{type%keyvals}{H}{width}{height}{x}{y}
\Ncolumnbottominarea{type%keyvals}{n}{H}{width}{height}{x}{y}
\Ncolumnbottominarea[pages]{type%keyvals}{n}{H}{width}{height}{x}{y}
\onecolumnStopinarea{H}{width}{height}{x}{y}
\onecolumnStopinarea[pages]{H}{width}{height}{x}{y}
\onecolumnDtopinarea{H}{width}{height}{x}{y}
\onecolumnDtopinarea[pages]{H}{width}{height}{x}{y}
\onecolumntop{type%keyvals}{H}
\onecolumntop[pages]{type%keyvals}{H}
\onecolumnStop{H}
\onecolumnStop[pages]{H}
\onecolumnDtop{H}
\onecolumnDtop[pages]{H}
\twocolumnStopinarea{H}{width}{height}{x}{y}
\twocolumnStopinarea[pages]{H}{width}{height}{x}{y}
\twocolumnDtopinarea{H}{width}{height}{x}{y}
\twocolumnDtopinarea[pages]{H}{width}{height}{x}{y}
\twocolumntop{type%keyvals}{H}
\twocolumntop[pages]{type%keyvals}{H}
\twocolumnStop{H}
\twocolumnStop[pages]{H}
\twocolumnDtop{H}
\twocolumnDtop[pages]{H}
\NcolumnStopinarea{n}{H}{width}{height}{x}{y}
\NcolumnStopinarea[pages]{n}{H}{width}{height}{x}{y}
\NcolumnDtopinarea{n}{H}{width}{height}{x}{y}
\NcolumnDtopinarea[pages]{n}{H}{width}{height}{x}{y}
\Ncolumntop{type%keyvals}{n}{H}
\Ncolumntop[pages]{type%keyvals}{n}{H}
\NcolumnStop{n}{H}
\NcolumnStop[pages]{n}{H}
\NcolumnDtop{n}{H}
\NcolumnDtop[pages]{n}{H}
\onecolumnSbottominarea{H}{width}{height}{x}{y}
\onecolumnSbottominarea[pages]{H}{width}{height}{x}{y}
\onecolumnDbottominarea{H}{width}{height}{x}{y}
\onecolumnDbottominarea[pages]{H}{width}{height}{x}{y}
\onecolumnbottom{type%keyvals}{H}
\onecolumnbottom[pages]{type%keyvals}{H}
\onecolumnSbottom{H}
\onecolumnSbottom[pages]{H}
\onecolumnDbottom{H}
\onecolumnDbottom[pages]{H}
\twocolumnSbottominarea{H}{width}{height}{x}{y}
\twocolumnSbottominarea[pages]{H}{width}{height}{x}{y}
\twocolumnDbottominarea{H}{width}{height}{x}{y}
\twocolumnDbottominarea[pages]{H}{width}{height}{x}{y}
\twocolumnbottom{type%keyvals}{H}
\twocolumnbottom[pages]{type%keyvals}{H}
\twocolumnSbottom{H}
\twocolumnSbottom[pages]{H}
\twocolumnDbottom{H}
\twocolumnDbottom[pages]{H}
\NcolumnSbottominarea{n}{H}{width}{height}{x}{y}
\NcolumnSbottominarea[pages]{n}{H}{width}{height}{x}{y}
\NcolumnDbottominarea{n}{H}{width}{height}{x}{y}
\NcolumnDbottominarea[pages]{n}{H}{width}{height}{x}{y}
\Ncolumnbottom{type%keyvals}{n}{H}
\Ncolumnbottom[pages]{type%keyvals}{n}{H}
\NcolumnSbottom{n}{H}
\NcolumnSbottom[pages]{n}{H}
\NcolumnDbottom{n}{H}
\NcolumnDbottom[pages]{n}{H}

\iflefttorightcolumns#*
\lefttorightcolumnstrue
\lefttorightcolumnsfalse

# commands below doubled with #S to get color completion
\vtwotone{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotone[pages]{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotone[pages][xoffset]{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotone{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotone[pages]{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotone[pages][xoffset]{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vNtone{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtone[%<pages%>]{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtone[%<pages%>][%<xoffset%>]{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vtwotonebottom{H}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonebottom[pages]{H}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonebottom[pages][xoffset]{H}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonebottom{H}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonebottom[pages]{H}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonebottom[pages][xoffset]{H}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonetop{H}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonetop[pages]{H}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonetop[pages][xoffset]{H}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonetop{H}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonetop[pages]{H}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonetop[pages][xoffset]{H}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vNtonebottom{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonebottom[%<pages%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonebottom[%<pages%>][%<xoffset%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonetop{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonetop[%<pages%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonetop[%<pages%>][%<xoffset%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\htwotone{height1}{color1}{IDL1}{height2}{color2}{IDL2}
\htwotone[pages]{height1}{color1}{IDL1}{height2}{color2}{IDL2}
\htwotone[pages][yoffset]{height1}{color1}{IDL1}{height2}{color2}{IDL2}
\htwotone{height1}{color}{IDL1}{height2}{color}{IDL2}#S
\htwotone[pages]{height1}{color}{IDL1}{height2}{color}{IDL2}#S
\htwotone[pages][yoffset]{height1}{color}{IDL1}{height2}{color}{IDL2}#S
\hNtone{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtone[%<pages%>]{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtone[%<pages%>][%<yoffset%>]{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\htwotoneleft{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneleft[pages]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneleft[pages][xoffset]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneleft{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneleft[pages]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneleft[pages][xoffset]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneright{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneright[pages]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneright[pages][xoffset]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneright{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneright[pages]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneright[pages][xoffset]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\hNtoneleft{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneleft[%<pages%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneleft[%<pages%>][%<yoffset%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneright{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneright[%<pages%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneright[%<pages%>][%<yoffset%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>

\makebackgroundframe{IDL}
\makebackgroundframe[pages]{IDL}

\insertvrule{type1%keyvals}{IDN1}{type2}{IDN2}
\insertvrule[ytop]{type1%keyvals}{IDN1}{type2}{IDN2}
\insertvrule[ytop][ybottom]{type1%keyvals}{IDN1}{type2}{IDN2}
\ffcolumnseprule#*
\ffvrule{offset}{width}{height}#*
\inserthrule{type1%keyvals}{IDN1}{type2}{IDN2}
\inserthrule[xleft]{type1%keyvals}{IDN1}{type2}{IDN2}
\inserthrule[xleft][xright]{type1%keyvals}{IDN1}{type2}{IDN2}
\ffhrule{offset}{width}{height}#*
\ffruledeclarations#*

\makethumbtabs{height}
\makethumbtabs{height}[section type]
\makethumbtabs[yoffset]{height}
\makethumbtabs[yoffset]{height}[section type]
\thumbtabwidth#*
\thumbtabindex
\enablethumbtabs
\disablethumbtabs
\tocandthumbtabindex
\thumbtabindexformat{arg1}{arg2}{arg3}#*
\thumbtabformat{arg1}{arg2}#*
\setthumbtab{n}{keyvals}
\setthumbtabindex{n}{keyvals}
\themaxthumbtabs#*

\enableminitoc
\enableminitoc[section type]
\appenddfminitoc{IDN}
\appenddfminitoc*{IDL}
\minitocstyle{contents%text}#*
\beforeminitocskip#*
\afterminitocskip#*

\setffdraftcolor#*
\setffdrafttypeblockcolor#*
\fflabelfont#*

\fflabelsep#*
\flowframesep#*
\flowframerule#*
\sdfparindent#*
\vcolumnsep#*

\labelflowidn{label}#l
\labelflow{label}#l

\themaxflow#*
\thethisframe#*
\thedisplayedframe#*
\themaxstatic#*
\themaxdynamic#*
\theabsolutepage#*

\adjustheight{height}

#keyvals:\setflowframe,\setflowframe*,\setallflowframes,\setstaticframe,\setstaticframe*,\setallstaticframes,\setdynamicframe,\setdynamicframe*,\setalldynamicframes,\setthumbtab,\setthumbtabindex
width=##L
height=##L
x=##L
y=##L
evenx=##L
eveny=##L
oddx=##L
oddy=##L
valign=#c,t,b
label=%<text%>
border=%<frame csname%>
offset=##L
bordercolor=#%color
textcolor=#%color
backcolor=#%color
pages={%<page list%>}
excludepages={%<page list%>}
hide#true,false
hidethis#true,false
margin=#left,right,inner,outer
clear#true,false
style=%<style csname%>
angle=%<degrees%>
shape=%<shape command%>
#endkeyvals

#keyvals:\relativeframelocation,\relativeframelocation*,\onecolumntopinarea,\twocolumntopinarea,\Ncolumntopinarea,\onecolumnbottominarea,\twocolumnbottominarea,\Ncolumnbottominarea,\onecolumntop,\twocolumntop,\Ncolumntop,\onecolumnbottom,\twocolumnbottom,\Ncolumnbottom,\insertvrule,\inserthrule
flow
static
dynamic
#endkeyvals

## not documented in user guide
\adjustcolsep#*
\aligntocfalse#*
\aligntoctrue#*
\checkifframeabove*{type1}{IDL1}{type2}{IDL2}#*
\checkifframeabove{type1}{IDN1}{type2}{IDN2}#*
\checkifframebelow*{type1}{IDL1}{type2}{IDL2}#*
\checkifframebelow{type1}{IDN1}{type2}{IDN2}#*
\checkifframeleft*{type1}{IDL1}{type2}{IDL2}#*
\checkifframeleft{type1}{IDN1}{type2}{IDN2}#*
\checkifframeright*{type1}{IDL1}{type2}{IDL2}#*
\checkifframeright{type1}{IDN1}{type2}{IDN2}#*
\defaultthumbtabtype#*
\dfcontinuedfalse#*
\dfcontinuedtrue#*
\dominitoc{IDN}#*
\dynamicframeevenx{IDN}#*
\dynamicframeeveny{IDN}#*
\dynamicframex{IDN}#*
\dynamicframey{IDN}#*
\emulateonecolumn#S
\emulatetwocolumn#S
\evencheckifframeabove*{type1}{IDL1}{type2}{IDL2}#*
\evencheckifframeabove{type1}{IDN1}{type2}{IDN2}#*
\evencheckifframebelow*{type1}{IDL1}{type2}{IDL2}#*
\evencheckifframebelow{type1}{IDN1}{type2}{IDN2}#*
\evencheckifframeleft*{type1}{IDL1}{type2}{IDL2}#*
\evencheckifframeleft{type1}{IDN1}{type2}{IDN2}#*
\evencheckifframeright*{type1}{IDL1}{type2}{IDL2}#*
\evencheckifframeright{type1}{IDN1}{type2}{IDN2}#*
\ffaddtoadjustframeshook{code}#*
\ffpshpar#*
\finishthispage#*
\FLFabovefalse#*
\FLFabovetrue#*
\FLFbelowfalse#*
\FLFbelowtrue#*
\FLFleftfalse#*
\FLFlefttrue#*
\FLForgpar#S
\FLFrightfalse#*
\FLFrighttrue#*
\flowframecol#*
\flowframeevenx{IDN}#*
\flowframeeveny{IDN}#*
\flowframeheight{IDN}#*
\flowframetextcol#*
\flowframewidth{IDN}#*
\flowframex{IDN}#*
\flowframey{IDN}#*
\footnotecolor#*
\getdynamicevenbounds*{IDN}#*
\getdynamicevenbounds{IDN}#*
\getflowevenbounds*{IDN}#*
\getflowevenbounds{IDN}#*
\getstaticevenbounds*{IDN}#*
\getstaticevenbounds{IDN}#*
\globalnormalmargin#*
\globalreversemargin#*
\ifaligntoc#*
\ifdfcontinued#*
\ifFLFabove#*
\ifFLFbelow#*
\ifFLFleft#*
\ifFLFright#*
\ifusedframebreak#*
\newframe[pages]{type}{width}{height}{x}{y}#*
\newframe{type}{width}{height}{x}{y}#*
\oddcheckifframeabove*{type1}{IDL1}{type2}{IDL2}#*
\oddcheckifframeabove{type1}{IDN1}{type2}{IDN2}#*
\oddcheckifframebelow*{type1}{IDL1}{type2}{IDL2}#*
\oddcheckifframebelow{type1}{IDN1}{type2}{IDN2}#*
\oddcheckifframeleft*{type1}{IDL1}{type2}{IDL2}#*
\oddcheckifframeleft{type1}{IDN1}{type2}{IDN2}#*
\oddcheckifframeright*{type1}{IDL1}{type2}{IDL2}#*
\oddcheckifframeright{type1}{IDN1}{type2}{IDN2}#*
\oldpar#S
\rotateframe{angle}{text}#*
\setframes#*
\setinitialframe{IDN}#*
\setmargin#*
\staticframeevenx{IDN}#*
\staticframeeveny{IDN}#*
\staticframex{IDN}#*
\staticframey{IDN}#*
\theHdisplayedframe#S
\theHthisframe#S
\theminitoc#*
\thumbtab{arg1}{arg2}{arg3}{arg4}#S
\tocandhumbtabindex#*
\usedframebreakfalse#*
\usedframebreaktrue#*