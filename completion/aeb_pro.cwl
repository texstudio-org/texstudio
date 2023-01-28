# aeb_pro package
# Matthew Bertucci 2022/07/28 for v2.14

#include:ifpdf
#include:ifxetex
#include:xkeyval
#include:insdljs
#include:forms16be
#include:aeb-comment
#include:calc
#include:eso-pic

# aeb_pro does not load these packages automatically, needs option package={},
# however .cwl format cannot recognize these options so they're listed here;
# similarly with pro option of web
#include:web
#include:eforms

#keyvals:\usepackage/aeb_pro#c
driver=#dvipsone,dvips,pdftex,dvipdfm,textures,dvipdfmx,xetex
useacrobat
nopro
web={%<web options%>}
exerquiz={%<exerquiz options%>}
dljslib={%<dljslib options%>}
eforms={%<eforms options%>}
insdljs={%<insdljs options%>}
eq2db={%<eq2db options%>}
aebxmp={%<aebxmp options%>}
graphicxsp={%<graphicxsp options%>}
hyperref={%<hyperref options%>}
gopro
attachsource={%<ext1,ext2,...%>}
attachments={%<path1,path2,...%>}
optattachments
!optattachments
linktoattachments
childof=%<path%>
btnanime
uselayers
ocganime
#endkeyvals

#ifOption:exerquiz
#include:exerquiz
#endif

#ifOption:dljslib
#include:dljslib
#endif

#ifOption:eq2db
#include:eq2db
#endif

#ifOption:aebxmp
#include:aebxmp
#endif

#ifOption:graphicxsp
#include:graphicxsp
#endif

#ifOption:linktoattachments
# from linkto.def
\begin{attachmentNames}
\end{attachmentNames}
\autolabelNum{num}
\autolabelNum[label]{num}
\autolabelNum*{num}{description%text}
\autolabelNum*[label]{num}{description%text}
\labelName{label%specialDef}{description%text}#s#%unicodestr
\ahyperref{target-label}{text%plain}
\ahyperref[options%keyvals]{target-label}{text%plain}
\ahyperlink{target-label}{text%plain}
\ahyperlink[options%keyvals]{target-label}{text%plain}
\ahyperextract{target-label}{text%plain}
\ahyperextract[options%keyvals]{target-label}{text%plain}
#keyvals:\ahyperref,\ahyperlink,\ahyperextract
goto=#p2c,c2p,c2c
page=%<number%>
view=%<view%>
dest=%<destination%>
open=#usepref,new,existing
border=#visible,invisible
highlight=#none,invert,outline,insert
bordercolor=%<r g b%>
linestyle=#solid,dashed,underlined
linewidth=#thin,medium,thick
preset=%<command%>
#endkeyvals
#keyvals:\ahyperextract
launch=#save,view,viewnosave
#endkeyvals
# not documented
\ahypercolor#S
\attachmentNamesEnv#S
\getdscrptCont#S
\getdscrptStrCont{arg}#S
\HandleDblQuotesfalse#S
\HandleDblQuotestrue#S
\ifHandleDblQuotes#S
\resetahyperDefaults#S
\setahyperDefaults{arg}#S
\targetDictionary#S
#endif

#ifOption:btnanime
## from btnnanime.def
\btnAnime{keyvals}{width}{height}
#keyvals:\btnAnime,\animeSetup
fieldName=%<basename%>
iconName=%<basename%>
nFrames=%<integer%>
type=#loop,palindrome,stopatboundary
poster=#first,last,none
speed=%<milliseconds%>
autorun#true,false
autopause#true,false
autoplayevent=#pageopen,pagevisible
autopauseevent=#pageclose,pageinvisible
ctrlwidth=##L
ctrlheight=##L
ctrlbdrycolor=%<r g b%>
ctrlbdrywidth=#thin,medium,thick
controls=#none,skin1,skin2,skin3,skin4,skin5,skin6
nospeedcontrol
usetworows
#endkeyvals
## from anime_support.def
\placeAnimeCtrlBtnFaces{%<appr-icons%>.pdf}{%<list-of-animes%>}
\placeAnimeCtrlBtnFaces[%<path%>]{%<appr-icons%>.pdf}{%<list-of-animes%>}
\btnanimebtnsep#*
\btnanimerowsep#*
\btnAnimePresets{eforms params}
\btnAnimeCtrlPresets{eforms params}
\animeSetup{keyvals}
\insertCtrlButtons
\insertCtrlButtons[position]
\ctrlButtonsWrapper{code}#*
\btnAnimeCtrlW#*
\btnAnimeCtrlH#*
\btnAnimeGoToFirst
\btnAnimeStepBack
\btnAnimePlayBack
\btnAnimePause
\btnAnimePlayForward
\btnAnimeStepForward
\btnAnimeGoToLast
\btnAnimePlus
\btnAnimeMinus
\btnAnimeFirstAction
\btnAnimeSBAction
\btnAnimePBAction
\btnAnimePauseAction
\btnAnimePFAction
\btnAnimeSFAction
\btnAnimeLastAction
\btnAnimePlusAction
\btnAnimeMinusAction
\widthFirstRow#*
\setspaceBtwnPMBtns{space cmd}
# not documented
\addSpaceBtwnPMBtns#S
\aepnumWidgetsFirstRow{arg1}{arg2}#S
\animeBtnBaseName#S
\animeBtnFieldName#S
\animeBtnSpeed#S
\animeSetupPresets#S
\btnAnimeSkini#S
\btnAnimeSkinii#S
\btnAnimeSkiniii#S
\btnAnimeSkiniv#S
\nFrames#S
\numWidgetsFirstRow#S
\numWidgetsFirstRowV#S
\numWidgetsFirstRowVI#S
\vspacectrlsep#S
#endif

#ifOption:uselayers
## from aeblayers.def
\xBld{layer-name}
\xBld[options%keyvals]{layer-name}
\eBld
#keyvals:\xBld,\animeBld
true
false
print#true,false
#endkeyvals
\DeclareAnime{basename}{speed}{nframes}
\animeBld
\animeBld[options%keyvals]
\backAnimeBtn{width}{height}
\backAnimeBtn[eforms params]{width}{height}
\clearAnimeBtn{width}{height}
\clearAnimeBtn[eforms params]{width}{height}
\forwardAnimeBtn{width}{height}
\forwardAnimeBtn[eforms params]{width}{height}
\defineRC{layer-name}{message%text}
\insertRC{layer-name}
\definePR{layer-name}{message%text}
\insertPR{layer-name}
\nFrames#*
\animBaseName#*
\animSpeed#*
\addJStexHelpEnter{JS code%definition}
\addJStexHelpExit{JS code%definition}
\texHelp{layer-name}{text}
\texHelp*{layer-name}{text}
\resetaddJStexHelp
\begin{rollover}
\end{rollover}
\begin{printRollover}
\end{printRollover}
\proofRollovers
\turnProofingOn
\turnProofingOff
# not documented
\animBldName#S
\animeName{arg}#S
\iftexhelptoggleOff#S
\texHelpIndicator{arg}#S
\texHelpIndicatorColor#S
\texhelptoggleOfffalse#S
\texhelptoggleOfftrue#S
\theocSeq#S
#endif

#ifOption:ocganime
### loads uselayers option
## from ocganime.def
\begin{ocgAnime}{keyvals}
\end{ocgAnime}
#keyvals:\begin{ocgAnime},\animeSetup
ocgAnimeName=%<basename%>
fieldName=%<basename%>
nFrames=%<integer%>
type=#loop,palindrome,stopatboundary
poster=#first,last,none
speed=%<milliseconds%>
autorun#true,false
autopause#true,false
autoplayevent=#pageopen,pagevisible
autopauseevent=#pageclose,pageinvisible
ctrlwidth=##L
ctrlheight=##L
ctrlbdrycolor=%<r g b%>
ctrlbdrywidth=#thin,medium,thick
controls=#none,skin1,skin2,skin3,skin4,skin5,skin6
nospeedcontrol
usetworows
#endkeyvals
## from anime_support.def
\placeAnimeCtrlBtnFaces{%<appr-icons%>.pdf}{%<list-of-animes%>}
\placeAnimeCtrlBtnFaces[%<path%>]{%<appr-icons%>.pdf}{%<list-of-animes%>}
\btnanimebtnsep#*
\btnanimerowsep#*
\btnAnimePresets{eforms params}
\btnAnimeCtrlPresets{eforms params}
\animeSetup{keyvals}
\insertCtrlButtons
\insertCtrlButtons[position]
\ctrlButtonsWrapper{code}#*
\btnAnimeCtrlW#*
\btnAnimeCtrlH#*
\btnAnimeGoToFirst
\btnAnimeStepBack
\btnAnimePlayBack
\btnAnimePause
\btnAnimePlayForward
\btnAnimeStepForward
\btnAnimeGoToLast
\btnAnimePlus
\btnAnimeMinus
\btnAnimeFirstAction
\btnAnimeSBAction
\btnAnimePBAction
\btnAnimePauseAction
\btnAnimePFAction
\btnAnimeSFAction
\btnAnimeLastAction
\btnAnimePlusAction
\btnAnimeMinusAction
\widthFirstRow#*
\setspaceBtwnPMBtns{space cmd}
# not documented
\addSpaceBtwnPMBtns#S
\aepnumWidgetsFirstRow{arg1}{arg2}#S
\animeBtnBaseName#S
\animeBtnFieldName#S
\animeBtnSpeed#S
\animeSetupPresets#S
\btnAnimeSkini#S
\btnAnimeSkinii#S
\btnAnimeSkiniii#S
\btnAnimeSkiniv#S
\nFrames#S
\numWidgetsFirstRow#S
\numWidgetsFirstRowV#S
\numWidgetsFirstRowVI#S
\vspacectrlsep#S
## from aeblayers.def
\xBld{layer-name}
\xBld[options%keyvals]{layer-name}
\eBld
#keyvals:\xBld,\animeBld
true
false
print#true,false
#endkeyvals
\DeclareAnime{basename}{speed}{nframes}
\animeBld
\animeBld[options%keyvals]
\backAnimeBtn{width}{height}
\backAnimeBtn[eforms params]{width}{height}
\clearAnimeBtn{width}{height}
\clearAnimeBtn[eforms params]{width}{height}
\forwardAnimeBtn{width}{height}
\forwardAnimeBtn[eforms params]{width}{height}
\defineRC{layer-name}{message%text}
\insertRC{layer-name}
\definePR{layer-name}{message%text}
\insertPR{layer-name}
\nFrames#*
\animBaseName#*
\animSpeed#*
\addJStexHelpEnter{JS code%definition}
\addJStexHelpExit{JS code%definition}
\texHelp{layer-name}{text}
\texHelp*{layer-name}{text}
\resetaddJStexHelp
\begin{rollover}
\end{rollover}
\begin{printRollover}
\end{printRollover}
\proofRollovers
\turnProofingOn
\turnProofingOff
# not documented
\animBldName#S
\animeName{arg}#S
\iftexhelptoggleOff#S
\texHelpIndicator{arg}#S
\texHelpIndicatorColor#S
\texhelptoggleOfffalse#S
\texhelptoggleOfftrue#S
\theocSeq#S
#endif

## from aebpro.def
\DeclareInitView{keyvals}
#keyvals:\DeclareInitView
layoutmag={%<keyvals%>}
windowoptions={%<keyvals%>}
uioptions={%<keyvals%>}
#endkeyvals
\begin{willClose}
\end{willClose}
\begin{willSave}
\end{willSave}
\begin{didSave}
\end{didSave}
\begin{willPrint}
\end{willPrint}
\begin{didPrint}
\end{didPrint}
\additionalOpenAction{action}
\requiredVersionMsg{message%text}
\alternateDocumentURL{URL}#U
\requiredVersionMsgRedirect{message%text}
\afterRequirementPassedJS{JS code%definition}
\requiresVersion{version-number}
\requiresVersion[warnonly]{%<version-number%>}
\begin{addJSToPageOpen}
\end{addJSToPageOpen}
\begin{addJSToPageClose}
\end{addJSToPageClose}
\begin{addJSToPageOpenAt}{page-ranges}
\end{addJSToPageOpenAt}
\begin{addJSToPageCloseAt}{page-ranges}
\end{addJSToPageCloseAt}
\atPage{label}#r
\begin{everyPageOpen}
\end{everyPageOpen}
\begin{everyPageClose}
\end{everyPageClose}
\canceleveryPageOpen
\canceleveryPageClose
\setDefaultFS{keyvals}
#keyvals:
Trans=#NoTransition,UncoverLeft,UncoverRight,UncoverDown,UncoverUp,UncoverLeftDown,UncoverLeftUp,UncoverRightDown,UncoverRightUp,CoverLeft,CoverRight,CoverDown,CoverUp,CoverLeftDown,CoverLeftUp,CoverRightDown,CoverRightUp,PushLeft,PushRight,PushDown,PushUp,PushLeftDown,PushLeftUp,PushRightDown,PushRightUp,FlyInRight,FlyInLeft,FlyInDown,FlyInUp,FlyOutRight,FlyOutLeft,FlyOutDown,FlyOutUp,FlyIn,FlyOut,Blend,Fade,Random,Dissolve,GlitterRight,GlitterDown,GlitterRightDown,BoxIn,BoxOut,BlindsHorizontal,BlindsVertical,SplitHorizontalIn,SplitHorizontalOut,SplitVerticalIn,SplitVerticalOut,WipeLeft,WipeRight,WipeDown,WipeUp,WipeLeftDown,WipeLeftUp,WipeRightDown,WipeRightUp,Replace,ZoomInDown,ZoomInLeft,ZoomInLeftDown,ZoomInLeftUp,ZoomInRight,ZoomInRightDown,ZoomInRightUp,ZoomInUp,ZoomOutDown,ZoomOutLeft,ZoomOutLeftDown,ZoomOutLeftUp,ZoomOutRight,ZoomOutRightDown,ZoomOutRightUp,ZoomOutUp,CombHorizontal,CombVertical
bgColor=%<JS color%>
timeDelay=%<seconds%>
useTimer#true,false
loop#true,false
cursor=#hidden,delay,visible
escape#true,false
clickAdv#true,false
fullscreen#true,false
usePageTiming#true,false
#endkeyvals
\setPageTransition{keyvals}
\setPageTransitionAt{page-ranges}{keyvals}
#keyvals:\setPageTransition,\setPageTransitionAt
Trans=#NoTransition,UncoverLeft,UncoverRight,UncoverDown,UncoverUp,UncoverLeftDown,UncoverLeftUp,UncoverRightDown,UncoverRightUp,CoverLeft,CoverRight,CoverDown,CoverUp,CoverLeftDown,CoverLeftUp,CoverRightDown,CoverRightUp,PushLeft,PushRight,PushDown,PushUp,PushLeftDown,PushLeftUp,PushRightDown,PushRightUp,FlyInRight,FlyInLeft,FlyInDown,FlyInUp,FlyOutRight,FlyOutLeft,FlyOutDown,FlyOutUp,FlyIn,FlyOut,Blend,Fade,Random,Dissolve,GlitterRight,GlitterDown,GlitterRightDown,BoxIn,BoxOut,BlindsHorizontal,BlindsVertical,SplitHorizontalIn,SplitHorizontalOut,SplitVerticalIn,SplitVerticalOut,WipeLeft,WipeRight,WipeDown,WipeUp,WipeLeftDown,WipeLeftUp,WipeRightDown,WipeRightUp,Replace,ZoomInDown,ZoomInLeft,ZoomInLeftDown,ZoomInLeftUp,ZoomInRight,ZoomInRightDown,ZoomInRightUp,ZoomInUp,ZoomOutDown,ZoomOutLeft,ZoomOutLeftDown,ZoomOutLeftUp,ZoomOutRight,ZoomOutRightDown,ZoomOutRightUp,ZoomOutUp,CombHorizontal,CombVertical
TransDur=%<seconds%>
Speed=#Slow,Medium,Fast
PageDur=%<seconds%>
#endkeyvals
\addtoOptAttachments{list-of-files%file}
\prjinput{file}#i
\prjinclude{file}#i
\prjInputUser{file}#*i
\prjIncludeUser{file}#*i
\begin{docassembly}
\end{docassembly}
\addWatermarkFromFile({kv-pairs});
\importIcon({kv-pairs});
\importSound({kv-pairs});
\appopenDoc({kv-pairs});
\insertPages({kv-pairs});
\importDataObject({kv-pairs});
\executeSave();
\sigInfo{info}
\sigFieldObj("%<obj%>");
\signatureSign
\certifyInvisibleSign
\signatureSetSeedValue(oSeedValue)
\declareImageAndPlacement{keyvals}
#keyvals:\declareImageAndPlacement
name=%<name%>
path=%<file path%>
page=%<pages%>
placement={%<button1,button2,...%>}
#endkeyvals
\declareMultiImages{{%<keyvals1%>}{%<keyvals2%>}%<...%>}
\insertPreDocAssembly
\placeImage{name}{width}{height}
\placeImage[eforms params]{name}{width}{height}
\embedMultiPageImages{keyvals}
#keyvals:\embedMultiPageImages
path=%<file path%>
name=%<base name%>
placement={%<button1,button2,...%>}
firstpage=%<page number%>
lastpage=%<page number%>
#endkeyvals
\makePDFPackage{keyvals}
#keyvals:\makePDFPackage
initview=%<label%>
viewmode=#details,tile,hidden
#endkeyvals
\chngDocObjectTo{cmd}{name}#d
\docSaveAs
# not documented
\addWatermarkFromText#S
\aebAlternateDocumentURL#S
\aebPageAction[opt]{arg1}{arg2}#S
\aebPageAction{arg1}{arg2}#S
\aebpFAP#S
\aebpopentoksP#S
\ahrefexafter#S
\attachFile#S
\browseForDoc#S
\createTemplate#S
\DeclareJSHelper{arg1}{arg2}#S
\earlyAttachForPkgs#S
\extractPages#S
\getcNameFromFileName{arg}#S
\iconNameI{arg}#S
\ifisPDFPackage#S
\importAndSetImages#S
\isPDFPackagefalse#S
\isPDFPackagetrue#S
\jsstrdotsp#S
\jsstrsps#S
\mailDoc#S
\makePDFPortfolio{arg}#S
\placeImageToBtn{arg}#S
\pubAddToDocOpen#S
\requiredVersionNumber#S
\requiredVersionResult{arg1}{arg2}{arg3}#S
\retnAbsPathAs(arg)#S
\setLayoutMag{arg}#S
\setUIOptions{arg}#S
\setWindowOptions{arg}#S
\theDocObject#S

## from aeb_pro.sty
\ifoptattachments#*
\optattachmentstrue#S
\optattachmentsfalse#S
\ifoptattachmentsTaken#*
\optattachmentsTakentrue#S
\optattachmentsTakenfalse#S
\pdfHelp{fieldname}{message%text}{text}
\pdfHelp*{message%text}{text}
\pdfPrintHelp{fieldname}{message%text}{text}
\pdfPrintHelp*{message%text}{text}
\texHelp{layer-name}{text}
\texPrintHelp{layer-name}{text}
\rollormargstring{roll-string}{margin-string}
\pdfPHProof{arg1}{arg2}{arg3}#*
\texPHProof{arg1}{arg2}#*
# not documented
\aebsavehelp#S
\ExecuteOptionsXSAVE{options}#S
\inputAttachmentRelatedFiles#S
\inputBtnAnimeCode#S
\inputCommonAnimeCode#S
\inputOcgAnimeCode#S
\pathToBtnCtrlIcons#S
\pdfHelpCnt#S
\pdfHelpi{arg1}{arg2}{arg3}#S
\pdfHelpIndicator{arg}#S
\pdfHelpIndicatorColor#S
\pdfPrintHelpi{arg1}{arg2}{arg3}#S
webblue#B

## from pro option of web package
#include:pifont
\DeclareDocInfo{keyvals}
#keyvals:\DeclareDocInfo
title={%<text%>}
author={%<name%>}
university={%<university%>}
email=%<email%>
talksite={%<site%>}
talkdate=%<date%>
talkdateLabel={%<text%>}
version=%<version%>
versionLabel={%<text%>}
subject={%<subject%>}
keywords={%<word1,word2,...%>}
copyrightyears={%<years%>}
prepared=%<date%>
preparedLabel={%<text%>}
Title={%<text%>}
authors={%<name1%>}{%<name2%>}%<...%>
Subject={%<subject%>}
Keywords={%<word1,word2,...%>}
lang=%<language%>
copyrightStatus=#True,False
copyrightNotice={%<text%>}
copyrightInfoURL=%<URL%>
authortitle={%<text%>}
descriptionwriter={%<text%>}
customProperties={name=%<name1%>,value=%<value1%>}%<{name=name2,value=value2}...%>
#endkeyvals
\DeclarePageLayout{keyvals}
#keyvals:\DeclarePageLayout
design=#designi,designii,designiii,designiv,designv,designvi,designvii,designviii,designix
screensizeOf=#designi,designii,designiii,designiv,designv,designvi,designvii,designviii,designix
screensize={%<height%>}{%<width%>}
margins={%<left%>}{%<right%>}{%<top%>}{%<bottom%>}
headheight=##L
topmargin=##L
additionalheadsep=##L
marginparsep=##L
marginparwidth=##L
marginparpush=##L
footskip=##L
webfootskip=##L
panelwidth=##L
panelsep=##L
#endkeyvals
\universityLayout{keyvals}
\titleLayout{keyvals}
\authorLayout{keyvals}
#keyvals:\universityLayout,\titleLayout,\authorLayout
fontfamily=#rmfamily,sffamily,ttfamily
fontseries=#bfseries,mdseries
fontshape=#upshape,itshape,scshape,slshape
fontsize=#tiny,scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge
halign=#l,c,r
color=#%color
special=#shadow,framebox,colorbox,fcolorbox,frameboxfit,colorboxfit,fcolorboxfit,custom,default
framecolor=#%color
bgcolor=#%color
shadowcolor=#%color
beforeskip=##L
afterskip=##L
usefont={%<encoding%>}{%<family%>}{%<series%>}{%<shape%>}{%<size%>}
hproportion=%<factor%>
xhalign=#l,c,r
#endkeyvals
\topTitlePageProportion{factor}
\DesignTitlePageTrailer{keyvals}
#keyvals:\DesignTitlePageTrailer
ul=%<text%>
ur=%<text%>
ll=%<text%>
lr=%<text%>
textColor=#%color
bgColor=#%color
borderColor=#%color
fboxsep=##L
fboxrule=##L
graphic=%<imagefile%>
namedgraphic=%<name%>
raise=##L
fontSize=%<fontsize cmd%>
formatting=%<font commands%>
#endkeyvals
\selectTocDings{keyvals}
#keyvals:\selectTocDings
dDing=%<symbol%>
ddDing=%<symbol%>
dddDing=%<symbol%>
dDingColor=#%color
ddDingColor=#%color
dddDingColor=#%color
#endkeyvals
\selectColors{keyvals}
#keyvals:\selectColors
universityColor=#%color
titleColor=#%color
textBgColor=#%color
panelBgColor=#%color
urlColor=#%color
linkColor=#%color
fileColor=#%color
#endkeyvals
\noSectionNumbers
\tocLayout{keyvals}
\sectionLayout{keyvals}
\subsectionLayout{keyvals}
\subsubsectionLayout{keyvals}
#keyvals:\tocLayout,\sectionLayout,\subsectionLayout,\subsubsectionLayout
fontfamily=#rmfamily,sffamily,ttfamily
fontseries=#bfseries,mdseries
fontshape=#upshape,itshape,scshape,slshape
fontsize=#tiny,scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge
halign=#l,c,r
ding=%<symbol%>
color=#%color
special=#shadow,framebox,colorbox,fcolorbox,frameboxfit,colorboxfit,fcolorboxfit,custom,default
framecolor=#%color
bgcolor=#%color
shadowcolor=#%color
beforeskip=##L
afterskip=##L
usefont={%<encoding%>}{%<family%>}{%<series%>}{%<shape%>}{%<size%>}
numdingcolor=#%color
reset=#font,all
#endkeyvals
\shadowhoffset{length}
\shadowvoffset{length}
\customSecHead{TeX code}
\customSubsecHead{TeX code}
\customSubsubsecHead{TeX code}
\preparedLabel{text}#*
\prepared{date}#*
\talkdate{date}#*
\webtalkdate#*
\talkdateLabel{text}#*
\talksite{site}#*
\customUniversity{TeX code}#*
\customTitle{TeX code}#*
\customAuthor{TeX code}#*
\customToc{TeX code}#*
\halignuniversity#*
\haligntitle#*
\halignauthor#*
\halignsection#*
\halignsubsection#*
\halignsubsubsection#*
\haligntoc#*
\subsubDefaultDing{symbol}#*
\sectionTitle#*
\sectionAuthor#*
\sectionUniversity#*
\sectionToc#*
\ifShadow#*
\Shadowtrue#*
\Shadowfalse#*
\useSectionNumbers#*
\dDingToc{symbol}#*
\ddDingToc{symbol}#*
\dddDingToc{symbol}#*
\dDingTocColor{color}#*
\ddDingTocColor{color}#*
\dddDingTocColor{color}#*
