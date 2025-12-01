# flowfram package
# Matthew Bertucci 2025/11/24 for v2.0

#include:rerunfilecheck
#include:graphics
#include:afterpage
#include:etoolbox
#include:color

\flowframsetup{options%keyvals}

#keyvals:\usepackage/flowfram#c,\flowframsetup
adjust-toc=#header,notheader,off
backmatter-sections=#no-change,no-number
toc-thumbtabs=#aligned,unaligned,true,false
unstarred-thumbtabs#true,false
matter-thumbtabs=#main-only,all,not-front,not-back
thumbtab-links=#toc-only,all,none
thumbtab-text=#rotate,rotate-right,rotate-left,stack,normal
thumbtabs=#title,number,both,none
sections-extra-option=#thumbtab-only,original-and-thumbtab,as-original
dynamic-page-style=#adjust,noadjust
dynamic-header-case=#uc,no-change
dynamic-subheader-case=#uc,no-change
dynamic-page-style-header-font=%<code%>
dynamic-page-style-subheader-font=%<code%>
dynamic-empty-page-style=#empty,plain,headings,myheadings,ignore,hide,show
LR
RL
column-changes=#ignore,clearpage,switch
pages=#relative,absolute
adjust-pre-chapter#true,false
verbose#true,false
draft
final
prohibit-frame-rotation#true,false
norotate
rotate#true,false
ttbtitle
ttbnotitle
ttbnum
ttbnonum
color#true,false
nocolor
#endkeyvals

\begin{dynamiccontents}{IDN}
\begin{dynamiccontents}[options%keyvals]{IDN}
\end{dynamiccontents}
\begin{dynamiccontents*}{IDL}
\begin{dynamiccontents*}[options%keyvals]{IDL}
\end{dynamiccontents*}
\begin{staticcontents}{IDN}
\begin{staticcontents}[options%keyvals]{IDN}
\end{staticcontents}
\begin{staticcontents*}{IDL}
\begin{staticcontents*}[options%keyvals]{IDL}
\end{staticcontents*}
\begin{staticfigure}
\end{staticfigure}
\begin{statictable}
\end{statictable}

\adjustcolsep#*
\afterminitocskip#*
\appenddfminitoc*{IDL}
\appenddfminitoc{IDN}
\appenddynamiccontents*[options%keyvals]{IDL}{contents%text}
\appenddynamiccontents*{IDL}{contents%text}
\appenddynamiccontents[options%keyvals]{IDN}{contents%text}
\appenddynamiccontents{IDN}{contents%text}
\beforeminitocskip#*
\chapterfirstpagestyle#*
\ChapterInDynamic{ID}
\cleartoevenpage
\computebottomedge{length}
\computeflowframearea*{IDL list}
\computeflowframearea{IDN list}
\computeleftedgeeven{length}
\computeleftedgeodd{length}
\computerightedgeeven{length}
\computerightedgeodd{length}
\computetopedge{length}
\continueonframe[text]{ID}
\continueonframe{ID}
\defaultthumbtabtype#*
\dfchapterclearpage#*
\dfEvenFooterStyle{text}#*
\dfEvenHeaderStyle{text}#*
\dfOddFooterStyle{text}#*
\dfOddHeaderStyle{text}#*
\dfswapoddeven{IDN}
\disablethumbtabs
\dynamicaddexclusion{IDN}{page list}
\dynamicframeevenx{IDN}
\dynamicframeeveny{IDN}
\dynamicframeheight{IDN}
\dynamicframewidth{IDN}
\dynamicframex{IDN}
\dynamicframey{IDN}
\dynamicsetexclusion{IDN}{page list}
\dynamicsetpagelist{IDN}{page list}
\dynamicswitchoffnext*{IDL list}
\dynamicswitchoffnextodd*{IDL list}
\dynamicswitchoffnextoddonly*{IDL list}
\dynamicswitchoffnextoddonly{IDN list}
\dynamicswitchoffnextodd{IDN list}
\dynamicswitchoffnextonly*{IDL list}
\dynamicswitchoffnextonly{IDN list}
\dynamicswitchoffnext{IDN list}
\dynamicswitchonnext*{IDL list}
\dynamicswitchonnextodd*{IDL list}
\dynamicswitchonnextoddonly*{IDL list}
\dynamicswitchonnextoddonly{IDN list}
\dynamicswitchonnextodd{IDN list}
\dynamicswitchonnextonly*{IDL list}
\dynamicswitchonnextonly{IDN list}
\dynamicswitchonnext{IDN list}
\enableminitoc
\enableminitoc[section type]
\enablethumbtabs
\FFabove#*
\FFaboveleft#*
\FFaboveright#*
\ffareaheight#*
\ffareawidth#*
\ffareax#*
\ffareay#*
\FFbelow#*
\FFbelowleft#*
\FFbelowright#*
\ffchapterdefaultfont#*
\ffchapterheadstyle#*
\ffchapternamenumfont{text}#*
\ffchapternamenum{name}{number}#*
\ffchapterpostheadskip#*
\ffchapterpostnamenum#*
\ffchapterpreheadskip#*
\ffchaptertitlefont{text}#*
\ffcolumnseprule#*
\ffcontinuedtextfont{text}#*
\ffcontinuedtextlayout{text}#*
\ffdefaultcontinuetext#*
\ffdefaultdynamiccontinuetext{IDN1}{IDN2}#*
\ffdefaultpostcontinued#*
\ffdefaultstaticcontinuetext{IDN1}{IDN2}#*
\ffdynamicpostcontinued{IDN1}{IDN2}#*
\ffhrule{offset}{width}{height}#*
\fflabelfont#*
\fflabelsep#*
\FFleft#*
\FFoverlap#*
\ffprechapterhook#*
\FFright#*
\ffruledeclarations#*
\ffstaticpostcontinued{IDN1}{IDN2}#*
\ffswapoddeven{IDN}
\fftolerance#*
\ffvadjustfalse
\ffvadjusttrue
\ffvrule{offset}{width}{height}#*
\finishthispage
\flowaddexclusion{IDN}{page list}
\flowframchapterheader{text}#*
\flowframeevenx{IDN}
\flowframeeveny{IDN}
\flowframeheight{IDN}
\flowframerule#*
\flowframesep#*
\flowframeshowlayout
\flowframewidth{IDN}
\flowframex{IDN}
\flowframey{IDN}
\flowframheaderchapprefix#*
\flowframheadersep#*
\FlowFramRestoreOR
\flowframsectionheader{text}#*
\FlowFramUnrestoreOR
\flowsetexclusion{IDN}{page list}
\flowsetpagelist{IDN}{page list}
\flowswitchoffnext*{IDL list}
\flowswitchoffnextodd*{IDL list}
\flowswitchoffnextoddonly*{IDL list}
\flowswitchoffnextoddonly{IDN list}
\flowswitchoffnextodd{IDN list}
\flowswitchoffnextonly*{IDL list}
\flowswitchoffnextonly{IDN list}
\flowswitchoffnext{IDN list}
\flowswitchonnext*{IDL list}
\flowswitchonnextodd*{IDL list}
\flowswitchonnextoddonly*{IDL list}
\flowswitchonnextoddonly{IDN list}
\flowswitchonnextodd{IDN list}
\flowswitchonnextonly*{IDL list}
\flowswitchonnextonly{IDN list}
\flowswitchonnext{IDN list}
\framebreak
\framebreak[n]
\getdynamicbounds*{IDL}
\getdynamicbounds{IDN}
\getdynamicid{cmd}{IDL}#d
\getdynamiclabel{IDN}
\getflowbounds*{IDL}
\getflowbounds{IDN}
\getflowid{cmd}{IDL}#d
\getflowlabel{IDN}
\getstaticbounds*{IDL}
\getstaticbounds{IDN}
\getstaticid{cmd}{IDL}#d
\getstaticlabel{IDN}
\ifffvadjust
\iflefttorightcolumns
\IfSavedRelativeLocationAbove{label}{true code}{false code}
\IfSavedRelativeLocationBelow{label}{true code}{false code}
\IfSavedRelativeLocationEq{label}{command}{true code}{false code}
\IfSavedRelativeLocationLeft{label}{true code}{false code}
\IfSavedRelativeLocationRight{label}{true code}{false code}
\ifshowframebbox
\ifshowmargins
\ifshowtypeblock
\inserthrule[xleft][xright]{type1%keyvals}{IDN1}{type2}{IDN2}
\inserthrule[xleft]{type1%keyvals}{IDN1}{type2}{IDN2}
\inserthrule{type1%keyvals}{IDN1}{type2}{IDN2}
\insertvrule[ytop][ybottom]{type1%keyvals}{IDN1}{type2}{IDN2}
\insertvrule[ytop]{type1%keyvals}{IDN1}{type2}{IDN2}
\insertvrule{type1%keyvals}{IDN1}{type2}{IDN2}
\labelflowidn{label}#l
\labelflow{label}#l
\lefttorightcolumnsfalse
\lefttorightcolumnstrue
\makebackgroundframe[page list]{IDL}
\makebackgroundframe{IDL}
\makedfheaderfooter
\makethumbtabs[yoffset]{height}
\makethumbtabs[yoffset]{height}[section type]
\makethumbtabs{height}
\makethumbtabs{height}[section type]
\minitocstyle{contents%text}#*
\Ncolumn[page list]{n}
\Ncolumn[page list]{n}[label]
\Ncolumnbottom[page list]{type%keyvals}{n}{top height}
\Ncolumnbottom[page list]{type%keyvals}{n}{top height}[label]
\Ncolumnbottominarea[page list]{type%keyvals}{n}{top height}{width}{height}{x}{y}
\Ncolumnbottominarea[page list]{type%keyvals}{n}{top height}{width}{height}{x}{y}[label]
\Ncolumnbottominarea{type%keyvals}{n}{top height}{width}{height}{x}{y}
\Ncolumnbottominarea{type%keyvals}{n}{top height}{width}{height}{x}{y}[label]
\Ncolumnbottom{type%keyvals}{n}{top height}
\Ncolumnbottom{type%keyvals}{n}{top height}[label]
\NcolumnDbottom[page list]{n}{top height}
\NcolumnDbottom[page list]{n}{top height}[label]
\NcolumnDbottominarea[page list]{n}{top height}{width}{height}{x}{y}
\NcolumnDbottominarea[page list]{n}{top height}{width}{height}{x}{y}[label]
\NcolumnDbottominarea{n}{top height}{width}{height}{x}{y}
\NcolumnDbottominarea{n}{top height}{width}{height}{x}{y}[label]
\NcolumnDbottom{n}{top height}
\NcolumnDbottom{n}{top height}[label]
\NcolumnDtop[page list]{n}{top height}
\NcolumnDtop[page list]{n}{top height}[label]
\NcolumnDtopinarea[page list]{n}{top height}{width}{height}{x}{y}
\NcolumnDtopinarea[page list]{n}{top height}{width}{height}{x}{y}[label]
\NcolumnDtopinarea{n}{top height}{width}{height}{x}{y}
\NcolumnDtopinarea{n}{top height}{width}{height}{x}{y}[label]
\NcolumnDtop{n}{top height}
\NcolumnDtop{n}{top height}[label]
\Ncolumninarea[page list]{n}{width}{height}{x}{y}
\Ncolumninarea[page list]{n}{width}{height}{x}{y}[label]
\Ncolumninarea{n}{width}{height}{x}{y}
\Ncolumninarea{n}{width}{height}{x}{y}[label]
\NcolumnSbottom[page list]{n}{top height}
\NcolumnSbottom[page list]{n}{top height}[label]
\NcolumnSbottominarea[page list]{n}{top height}{width}{height}{x}{y}
\NcolumnSbottominarea[page list]{n}{top height}{width}{height}{x}{y}[label]
\NcolumnSbottominarea{n}{top height}{width}{height}{x}{y}
\NcolumnSbottominarea{n}{top height}{width}{height}{x}{y}[label]
\NcolumnSbottom{n}{top height}
\NcolumnSbottom{n}{top height}[label]
\NcolumnStop[page list]{n}{top height}
\NcolumnStop[page list]{n}{top height}[label]
\NcolumnStopinarea[page list]{n}{top height}{width}{height}{x}{y}
\NcolumnStopinarea[page list]{n}{top height}{width}{height}{x}{y}[label]
\NcolumnStopinarea{n}{top height}{width}{height}{x}{y}
\NcolumnStopinarea{n}{top height}{width}{height}{x}{y}[label]
\NcolumnStop{n}{top height}
\NcolumnStop{n}{top height}[label]
\Ncolumntop[page list]{type%keyvals}{n}{top height}
\Ncolumntop[page list]{type%keyvals}{n}{top height}[label]
\Ncolumntopinarea[page list]{type%keyvals}{n}{top height}{width}{height}{x}{y}
\Ncolumntopinarea[page list]{type%keyvals}{n}{top height}{width}{height}{x}{y}[label]
\Ncolumntopinarea{type%keyvals}{n}{top height}{width}{height}{x}{y}
\Ncolumntopinarea{type%keyvals}{n}{top height}{width}{height}{x}{y}[label]
\Ncolumntop{type%keyvals}{n}{top height}
\Ncolumntop{type%keyvals}{n}{top height}[label]
\Ncolumn{n}
\Ncolumn{n}[label]
\newdynamicframe*[page list]{width}{height}{x}{y}
\newdynamicframe*[page list]{width}{height}{x}{y}[label]
\newdynamicframe*{width}{height}{x}{y}
\newdynamicframe*{width}{height}{x}{y}[label]
\newdynamicframe[page list]{width}{height}{x}{y}
\newdynamicframe[page list]{width}{height}{x}{y}[label]
\newdynamicframe{width}{height}{x}{y}
\newdynamicframe{width}{height}{x}{y}[label]
\newflowframe*[page list]{width}{height}{x}{y}
\newflowframe*[page list]{width}{height}{x}{y}[label]
\newflowframe*{width}{height}{x}{y}
\newflowframe*{width}{height}{x}{y}[label]
\newflowframe[page list]{width}{height}{x}{y}
\newflowframe[page list]{width}{height}{x}{y}[label]
\newflowframe{width}{height}{x}{y}
\newflowframe{width}{height}{x}{y}[label]
\newframe*[page list]{type}{width}{height}{x}{y}
\newframe*[page list]{type}{width}{height}{x}{y}[label]
\newframe*{type}{width}{height}{x}{y}
\newframe*{type}{width}{height}{x}{y}[label]
\newframe[page list]{type}{width}{height}{x}{y}
\newframe[page list]{type}{width}{height}{x}{y}[label]
\newframe{type}{width}{height}{x}{y}
\newframe{type}{width}{height}{x}{y}[label]
\newstaticframe*[page list]{width}{height}{x}{y}
\newstaticframe*[page list]{width}{height}{x}{y}[label]
\newstaticframe*{width}{height}{x}{y}
\newstaticframe*{width}{height}{x}{y}[label]
\newstaticframe[page list]{width}{height}{x}{y}
\newstaticframe[page list]{width}{height}{x}{y}[label]
\newstaticframe{width}{height}{x}{y}
\newstaticframe{width}{height}{x}{y}[label]
\onecolumn[page list]
\onecolumn[page list][label]
\onecolumnbottom[page list]{type%keyvals}{top height}
\onecolumnbottom[page list]{type%keyvals}{top height}[label]
\onecolumnbottominarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}
\onecolumnbottominarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}[label]
\onecolumnbottominarea{type%keyvals}{top height}{width}{height}{x}{y}
\onecolumnbottominarea{type%keyvals}{top height}{width}{height}{x}{y}[label]
\onecolumnbottom{type%keyvals}{top height}
\onecolumnbottom{type%keyvals}{top height}[label]
\onecolumnDbottom[page list]{top height}
\onecolumnDbottom[page list]{top height}[label]
\onecolumnDbottominarea[page list]{top height}{width}{height}{x}{y}
\onecolumnDbottominarea[page list]{top height}{width}{height}{x}{y}[label]
\onecolumnDbottominarea{top height}{width}{height}{x}{y}
\onecolumnDbottominarea{top height}{width}{height}{x}{y}[label]
\onecolumnDbottom{top height}
\onecolumnDbottom{top height}[label]
\onecolumnDtop[page list]{top height}
\onecolumnDtop[page list]{top height}[label]
\onecolumnDtopinarea[page list]{top height}{width}{height}{x}{y}
\onecolumnDtopinarea[page list]{top height}{width}{height}{x}{y}[label]
\onecolumnDtopinarea{top height}{width}{height}{x}{y}
\onecolumnDtopinarea{top height}{width}{height}{x}{y}[label]
\onecolumnDtop{top height}
\onecolumnDtop{top height}[label]
\onecolumninarea[page list]{width}{height}{x}{y}
\onecolumninarea[page list]{width}{height}{x}{y}[label]
\onecolumninarea{width}{height}{x}{y}
\onecolumninarea{width}{height}{x}{y}[label]
\onecolumnSbottom[page list]{top height}
\onecolumnSbottom[page list]{top height}[label]
\onecolumnSbottominarea[page list]{top height}{width}{height}{x}{y}
\onecolumnSbottominarea[page list]{top height}{width}{height}{x}{y}[label]
\onecolumnSbottominarea{top height}{width}{height}{x}{y}
\onecolumnSbottominarea{top height}{width}{height}{x}{y}[label]
\onecolumnSbottom{top height}
\onecolumnSbottom{top height}[label]
\onecolumnStop[page list]{top height}
\onecolumnStop[page list]{top height}[label]
\onecolumnStopinarea[page list]{top height}{width}{height}{x}{y}
\onecolumnStopinarea[page list]{top height}{width}{height}{x}{y}[label]
\onecolumnStopinarea{top height}{width}{height}{x}{y}
\onecolumnStopinarea{top height}{width}{height}{x}{y}[label]
\onecolumnStop{top height}
\onecolumnStop{top height}[label]
\onecolumntop[page list]{type%keyvals}{top height}
\onecolumntop[page list]{type%keyvals}{top height}[label]
\onecolumntopinarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}
\onecolumntopinarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}[label]
\onecolumntopinarea{type%keyvals}{top height}{width}{height}{x}{y}
\onecolumntopinarea{type%keyvals}{top height}{width}{height}{x}{y}[label]
\onecolumntop{type%keyvals}{top height}
\onecolumntop{type%keyvals}{top height}[label]
\RefSavedRelativeLocation{label}
\relativeframelocation*{type1%keyvals}{IDL1}{type2}{IDL2}
\relativeframelocation{type1%keyvals}{IDN1}{type2}{IDN2}
\reldynamicloc*{IDN1}{IDN2}
\reldynamicloc{IDN1}{IDN2}
\relflowloc*{IDN1}{IDN2}
\relflowloc{IDN1}{IDN2}
\relstaticloc*{IDN1}{IDN2}
\relstaticloc{IDN1}{IDN2}
\SaveRelativeFrameLocation*{label}{type1}{IDL1}{type2}{IDL2}
\SaveRelativeFrameLocation{label}{type1}{IDN1}{type2}{IDN2}
\sdfparindent#*
\setalldynamicframes{keyvals}
\setallflowframes{keyvals}
\setallstaticframes{keyvals}
\setdynamiccontents*[options%keyvals]{IDN}{contents%text}
\setdynamiccontents*{IDL}{contents%text}
\setdynamiccontents[options%keyvals]{IDN}{contents%text}
\setdynamiccontents{IDN}{contents%text}
\setdynamicframe*{IDL list}{keyvals}
\setdynamicframe{IDN list}{keyvals}
\setffdraftcolor#*
\setffdrafttypeblockcolor#*
\setflowframe*{IDL list}{keyvals}
\setflowframe{IDN list}{keyvals}
\SetOneColumnFrame*{ID}
\SetOneColumnFrame{ID}
\setstaticcontents*[options%keyvals]{IDL}{contents%text}
\setstaticcontents*{IDL}{contents%text}
\setstaticcontents[options%keyvals]{IDN}{contents%text}
\setstaticcontents{IDN}{contents%text}
\setstaticframe*{IDL list}{keyvals}
\setstaticframe{IDN list}{keyvals}
\setthumbtabindex{n}{keyvals}
\setthumbtab{n}{keyvals}
\SetTwoColumnFrames[header type][header id]{col1}[header col1]{col2}
\SetTwoColumnFrames[header type][header id]{col1}[header col1]{col2}[header col2]
\SetTwoColumnFrames[header type][header id]{col1}{col2}
\SetTwoColumnFrames[header type]{col1}[header col1]{col2}
\SetTwoColumnFrames[header type]{col1}[header col1]{col2}[header col2]
\SetTwoColumnFrames[header type]{col1}{col2}
\SetTwoColumnFrames[header type]{col1}{col2}[header col2]
\SetTwoColumnFrames[header type]{col1}{col2}[header col2]
\SetTwoColumnFrames{col1}[header col1]{col2}
\SetTwoColumnFrames{col1}[header col1]{col2}[header col2]
\SetTwoColumnFrames{col1}{col2}
\SetTwoColumnFrames{col1}{col2}[header col2]
\sfswapoddeven{IDN}
\showframebboxfalse
\showframebboxtrue
\showmarginsfalse
\showmarginstrue
\showtypeblockfalse
\showtypeblocktrue
\staticaddexclusion{IDN}{page list}
\staticframeevenx{IDN}
\staticframeeveny{IDN}
\staticframeheight{IDN}
\staticframewidth{IDN}
\staticframex{IDN}
\staticframey{IDN}
\staticsetexclusion{IDN}{page list}
\staticsetpagelist{IDN}{page list}
\staticswitchoffnext*{IDL list}
\staticswitchoffnextodd*{IDL list}
\staticswitchoffnextoddonly*{IDL list}
\staticswitchoffnextoddonly{IDN list}
\staticswitchoffnextodd{IDN list}
\staticswitchoffnextonly*{IDL list}
\staticswitchoffnextonly{IDN list}
\staticswitchoffnext{IDN list}
\staticswitchonnext*{IDL list}
\staticswitchonnextodd*{IDL list}
\staticswitchonnextoddonly*{IDL list}
\staticswitchonnextoddonly{IDN list}
\staticswitchonnextodd{IDN list}
\staticswitchonnextonly*{IDL list}
\staticswitchonnextonly{IDN list}
\staticswitchonnext{IDN list}
\theabsolutepage#*
\thedisplayedframe#*
\themaxdynamic#*
\themaxflow#*
\themaxstatic#*
\themaxthumbtabs#*
\thethisframe#*
\thumbtabformat{text}{height}#*
\thumbtabhyperlinkformat{anchor}{text}{height}#*
\thumbtabindex
\thumbtabindex[page list]
\thumbtabindexformat{anchor}{text}{height}#*
\thumbtabregularformat{anchor}{text}{height}#*
\thumbtabwidth#*
\twocolumn[page list]
\twocolumn[page list][label]
\twocolumnbottom[page list]{type%keyvals}{top height}
\twocolumnbottom[page list]{type%keyvals}{top height}[label]
\twocolumnbottominarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}
\twocolumnbottominarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}[label]
\twocolumnbottominarea{type%keyvals}{top height}{width}{height}{x}{y}
\twocolumnbottominarea{type%keyvals}{top height}{width}{height}{x}{y}[label]
\twocolumnbottom{type%keyvals}{top height}
\twocolumnbottom{type%keyvals}{top height}[label]
\twocolumnDbottom[page list]{top height}
\twocolumnDbottom[page list]{top height}[label]
\twocolumnDbottominarea[page list]{top height}{width}{height}{x}{y}
\twocolumnDbottominarea[page list]{top height}{width}{height}{x}{y}[label]
\twocolumnDbottominarea{top height}{width}{height}{x}{y}
\twocolumnDbottominarea{top height}{width}{height}{x}{y}[label]
\twocolumnDbottom{top height}
\twocolumnDbottom{top height}[label]
\twocolumnDtop[page list]{top height}
\twocolumnDtop[page list]{top height}[label]
\twocolumnDtopinarea[page list]{top height}{width}{height}{x}{y}
\twocolumnDtopinarea[page list]{top height}{width}{height}{x}{y}[label]
\twocolumnDtopinarea{top height}{width}{height}{x}{y}
\twocolumnDtopinarea{top height}{width}{height}{x}{y}[label]
\twocolumnDtop{top height}
\twocolumnDtop{top height}[label]
\twocolumninarea[page list]{width}{height}{x}{y}
\twocolumninarea[page list]{width}{height}{x}{y}[label]
\twocolumninarea{width}{height}{x}{y}
\twocolumninarea{width}{height}{x}{y}[label]
\twocolumnSbottom[page list]{top height}
\twocolumnSbottom[page list]{top height}[label]
\twocolumnSbottominarea[page list]{top height}{width}{height}{x}{y}
\twocolumnSbottominarea[page list]{top height}{width}{height}{x}{y}[label]
\twocolumnSbottominarea{top height}{width}{height}{x}{y}
\twocolumnSbottominarea{top height}{width}{height}{x}{y}[label]
\twocolumnSbottom{top height}
\twocolumnSbottom{top height}[label]
\twocolumnStop[page list]{top height}
\twocolumnStop[page list]{top height}[label]
\twocolumnStopinarea[page list]{top height}{width}{height}{x}{y}
\twocolumnStopinarea[page list]{top height}{width}{height}{x}{y}[label]
\twocolumnStopinarea{top height}{width}{height}{x}{y}
\twocolumnStopinarea{top height}{width}{height}{x}{y}[label]
\twocolumnStop{top height}
\twocolumnStop{top height}[label]
\twocolumntop[page list]{type%keyvals}{top height}
\twocolumntop[page list]{type%keyvals}{top height}[label]
\twocolumntopinarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}
\twocolumntopinarea[page list]{type%keyvals}{top height}{width}{height}{x}{y}[label]
\twocolumntopinarea{type%keyvals}{top height}{width}{height}{x}{y}
\twocolumntopinarea{type%keyvals}{top height}{width}{height}{x}{y}[label]
\twocolumntop{type%keyvals}{top height}
\twocolumntop{type%keyvals}{top height}[label]
\typeblockheight#L
\typeblockoffsety#L
\typeblockwidth#L
\vcolumnsep#*


# commands below doubled with #S to get color completion
\vtwotone{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotone[page list]{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotone[page list][xoffset]{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotone{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotone[page list]{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotone[page list][xoffset]{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vNtone{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtone[%<pages%>]{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtone[%<pages%>][%<xoffset%>]{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vtwotonebottom{top height}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonebottom[page list]{top height}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonebottom[page list][xoffset]{top height}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonebottom{top height}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonebottom[page list]{top height}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonebottom[page list][xoffset]{top height}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonetop{top height}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonetop[page list]{top height}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonetop[page list][xoffset]{top height}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\vtwotonetop{top height}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonetop[page list]{top height}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vtwotonetop[page list][xoffset]{top height}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\vNtonebottom{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonebottom[%<pages%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonebottom[%<pages%>][%<xoffset%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonetop{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonetop[%<pages%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\vNtonetop[%<pages%>][%<xoffset%>]{%<H%>}{%<N%>}{%<width1%>}{%<color1%>}{%<IDL1%>}%<...{widthN}{colorN}{IDLN}%>
\htwotone{height1}{color1}{IDL1}{height2}{color2}{IDL2}
\htwotone[page list]{height1}{color1}{IDL1}{height2}{color2}{IDL2}
\htwotone[page list][yoffset]{height1}{color1}{IDL1}{height2}{color2}{IDL2}
\htwotone{height1}{color}{IDL1}{height2}{color}{IDL2}#S
\htwotone[page list]{height1}{color}{IDL1}{height2}{color}{IDL2}#S
\htwotone[page list][yoffset]{height1}{color}{IDL1}{height2}{color}{IDL2}#S
\hNtone{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtone[%<pages%>]{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtone[%<pages%>][%<yoffset%>]{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\htwotoneleft{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneleft[page list]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneleft[page list][xoffset]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneleft{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneleft[page list]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneleft[page list][xoffset]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneright{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneright[page list]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneright[page list][xoffset]{W}{width1}{color1}{IDL1}{width2}{color2}{IDL2}
\htwotoneright{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneright[page list]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\htwotoneright[page list][xoffset]{W}{width1}{color}{IDL1}{width2}{color}{IDL2}#S
\hNtoneleft{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneleft[%<pages%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneleft[%<pages%>][%<yoffset%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneright{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneright[%<pages%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>
\hNtoneright[%<pages%>][%<yoffset%>]{%<W%>}{%<N%>}{%<height1%>}{%<color1%>}{%<IDL1%>}%<...{heightN}{colorN}{IDLN}%>

#keyvals:\setflowframe,\setflowframe*,\setallflowframes,\setstaticframe,\setstaticframe*,\setallstaticframes,\setdynamicframe,\setdynamicframe*,\setalldynamicframes,\setthumbtab,\setthumbtabindex
label=%<IDL%>
pages={%<page list%>}
excludepages={%<page list%>}
hide#true,false
hidethis#true,false
clear#true,false
parindent=##L
style=%<style csname%>
shape=%<shape command%>
valign=#c,t,b
margin=#left,right,inner,outer
offset=##L
width=##L
height=##L
x=##L
y=##L
evenx=##L
eveny=##L
oddx=##L
oddy=##L
angle=%<degrees%>
border=%<frame csname%>
bordercolor=#%color
backcolor=#%color
textcolor=#%color
html={%<keyvals%>}
#endkeyvals

#keyvals:\relativeframelocation,\relativeframelocation*,\onecolumntopinarea,\twocolumntopinarea,\Ncolumntopinarea,\onecolumnbottominarea,\twocolumnbottominarea,\Ncolumnbottominarea,\onecolumntop,\twocolumntop,\Ncolumntop,\onecolumnbottom,\twocolumnbottom,\Ncolumnbottom,\insertvrule,\inserthrule
flow
static
dynamic
#endkeyvals

## not documented in user guide
\adjustheight{height}#*
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
\dfcontinuedfalse#*
\dfcontinuedtrue#*
\dominitoc{IDN}#*
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
\flowframetextcol#*
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
\tocandthumbtabindex#*
\usedframebreakfalse#*
\usedframebreaktrue#*