# eforms package
# Matthew Bertucci 2/7/2022 for v2.4.3

#include:ifpdf
#include:ifxetex
#include:ifluatex
#include:calc
#include:hyperref
#include:insdljs
#include:taborder

#keyvals:\usepackage/eforms#c
dvipsone
dvips
pdftex
luatex
dvipdfm
dvipdfmx
xetex
textures
preview
useui
setcorder
# options passed to insdljs
nodljs
debug
execJS
nopro
reqjs
!reqjs
usealtadobe
#endkeyvals

\ifpreview#*
\previewtrue#*
\previewfalse#*
\previewOn
\previewOff
\pmpvOn
\pmpvOff
\tops{preview%text}{display%text}
\pmpvMrk{mark}

\pushButton{title%text}{width}{height}
\pushButton[modifications]{title%text}{width}{height}
\everyPushButton{modifications}
\checkBox{title%text}{width}{height}{on-name}
\checkBox[modifications]{title%text}{width}{height}{on-name}
\everyCheckBox{modifications}
\radioButton{title%text}{width}{height}{on-name}
\radioButton[modifications]{title%text}{width}{height}{on-name}
\everyRadioButton{modifications}
\listBox{title%text}{width}{height}{array}
\listBox[modifications]{title%text}{width}{height}{array}
\everyListBox{modifications}
\comboBox{title%text}{width}{height}{array}
\comboBox[modifications]{title%text}{width}{height}{array}
\everyComboBox{modifications}
\textField{title%text}{width}{height}
\textField[modifications]{title%text}{width}{height}
\everyTextField{modifications}
\sigField{title%text}{width}{height}
\sigField[modifications]{title%text}{width}{height}
\everySigField{modifications}

\makeXasPDOn
\makeXasPDOff
\makePDasXOn
\makePDasXOff
\olBdry
\cgBdry
\cgBdry[length]
\cgBdry*
\cgBdry*[length]
\volBdry
\vcgBdry
\vcgBdry[length]
\efKern{length1%l}{length2%l}

\setLink{link text}
\setLink[modifications]{link text%text}
\everyLink{modifications}
\setLinkText{link text}#*
\setLinkText[modifications]{link text%text}#*
\setLinkBbox{width}{height}[position]{link content%text}
\setLinkBbox[modifications]{width}{height}[position]{link content%text}
\Page#*

#ifOption:useui
\ui{keyvals}
#keyvals:\ui
border=#visible,invisible
linewidth=#thin,medium,thick
highlight=#none,invert,outline,inset,push
bordercolor={%<R G B%>}
linestyle=#solid,dashed,underlined,beveled,inset
dasharray=%<number%>
linktxtcolor=#%color
annotflags=#hidden,print,-print,noview,lock
fieldflags=#readonly,required,noexport,multiline,password,notoggleoff,radio,pushbutton,combo,edit,sort,fileselect,multiselect,nospellcheck,noscrolling,comb,radiosinunison,commitonchange,richtext
maxlength=%<number%>
tooltip={%<text%>}
default=%<text%>
value=%<text%>
rotate=#0,90,180,270
bgcolor={%<R G B%>}
uptxt={%<text%>}
downtxt={%<text%>}
rollovertxt={%<text%>}
normappr=%<string%>
rollappr=%<string%>
downappr=%<string%>
importicons=#yes,no
layout=#labelonly,icononly,icontop,iconbottom,iconleft,iconright,labelover
scalewhen=#always,never,iconbig,iconsmall
scale=#proportional,nonproportional
position={%<x y%>}
fitbounds#true,false
appr={%<specs%>}
align=#left,centered,right
textfont=%<font name%>
textsize=%<number%>
textcolor=%<number%>
autocenter=#yes,no
inline=#yes,no
presets=%<\cmd%>
symbolchoice=#check,circle,cross,diamond,square,star
rectW=##L
rectH=##L
width=##L
height=##L
scalefactor=%<factor%>
goto={%<KV-pairs%>}
js={%<script%>}
mouseup={%<script%>}
mousedown={%<script%>}
onenter={%<script%>}
onexit={%<script%>}
onfocus={%<script%>}
onblur={%<script%>}
format={%<script%>}
keystroke={%<script%>}
validate={%<script%>}
calculate={%<script%>}
pageopen={%<script%>}
pageclose={%<script%>}
pagevisible={%<script%>}
pageinvisible={%<script%>}
lock={%<KV-pairs%>}
#endkeyvals
#endif

\FHidden
\FPrint
\FNoView
\FLock
\FNoPrint

\FfReadOnly
\FfRequired
\FfNoExport
\FfMultiline
\FfPassword
\FfNoToggleToOff
\FfRadio
\FfPushButton
\FfCombo
\FfEdit
\FfSort
\FfFileSelect
\FfMultiSelect
\FfDoNotSpellCheck
\FfDoNotScroll
\FfComb
\FfRadiosInUnison
\FfCommitOnSelChange
\FfRichText

\textFontDefault{font spec}
\textSizeDefault{number}

\Ff{flag}
\F{flag}
\TU{tooltip text}
\W{0|1}
\S{S|D|B|I|U}
\R{degrees}
\BC{color}
\BG{color}
\mkIns{MK keyval}
\textFont{font spec}
\textSize{number}
\textColor{color}
\DV{string}
\V{string}
\A{actions}
\AA{actions}
\Color{color}
\Border{num1 num2 num3}
\D{num1 num2}
\AP{appearance dictionary}
\AS{appearance state}
\MK{dictionary}
\CA{text}
\RC{text}
\AC{text}
\I{XObject}
\RI{XObject}
\IX{XObject}
\importIcons{y|n}
\TP{0|1|2|3|4|5|6}
\SW{A|B|S|N}
\ST{A|P}
\PA{num1 num2}
\FB{true|false}
\Q{0|1|2}
\DA{default appearance}
\MaxLen{number}
\Lock{field}
\rectW{length}
\rectH{length}
\width{length}
\height{length}
\scalefactor{factor}
\rawPDF{PDF-KVPs}
\autoCenter{y|n}
\inline{y|n}
\presets{%<\cmd%>}
\symbolchoice{choice%keyvals}
#keyvals:\symbolchoice
check
circle
cross
diamond
square
star
#endkeyvals
\cmd{cmd-args}
\linktxtcolor{color}
\defaultlinkcolor#*
\mlstrut{strut}
\mlcrackat{number}
\mlhyph{y|n}
\mlignore{0|1}
\mlcrackinsat{LaTeX content}

\AAMouseUp{JS code%definition}
\AAMouseDown{JS code%definition}
\AAMouseEnter{JS code%definition}
\AAMouseExit{JS code%definition}
\AAOnFocus{JS code%definition}
\AAOnBlur{JS code%definition}
\AAFormat{JS code%definition}
\AAKeystroke{JS code%definition}
\AAValidate{JS code%definition}
\AACalculate{JS code%definition}
\AAPageOpen{JS code%definition}
\AAPageClose{JS code%definition}
\AAPageVisible{JS code%definition}
\AAPageInvisible{JS code%definition}

\definePath{cmd}{URL}#d

# not documented
\argii#S
\argiv#S
\argv#S
\Bbox#S
\btnSpcr{arg1}#S
\calcOrder{arg1}#S
\calcTextField#S
\centerWidget{arg1}#S
\checkBoxDefaults#S
\comboBoxDefaults#S
\csarg{arg1}{arg2}#S
\efCalcOrder#S
\efHxError#S
\efPreviewOnRule#S
\efrestore#S
\efrestorei{arg1}#S
\efsave#S
\efsavei{arg1}#S
\efSupprIndent#S
\eqtemp#S
\eqTextField#S
\getFfValue#S
\getFValue#S
\HexGlyph{arg1}{arg2}#S
\HGERROR#S
\inlineCenter#S
\inputCalcOrderJS#S
\isRadioParent#S
\isRadiosInUnison#S
\labelRef{arg1}#S
\lckAction{arg1}#S
\lckActionTst{arg1}#S
\lckAll#S
\lckArgs#S
\lckExcludeFields#S
\lckGetFieldsFor{arg1}{arg2}#S
\lckIncludeFields#S
\listBoxDefaults#S
\mlfixOff#S
\mlfixOn#S
\mlhypertext{arg1}{arg2}#S
\mlsetLink#S
\N#S
\nameuse#S
\Next{arg1}#S
\noexpandiii#S
\passthruCLOpts#S
\pmcaOff#S
\pmcaOn#S
\PMPV{arg1}#S
\pmpvCA#S
\pmpvCAOff#S
\pmpvCAOn#S
\pmpvFmt#S
\pmpvFmtCtrl#S
\pmpvV#S
\pmpvVOff#S
\pmpvVOn#S
\processAppArgs{arg1}{arg2}#S
\protectedKeys#S
\pushButtonDefaults#S
\radioButtonDefaults#S
\radioChoices{arg1}#S
\radioKids{arg1}#S
\reqPkg#S
\rPage#S
\setLinkPbox#S
\sigFieldDefaults#S
\taggedPDF#S
\textFieldDefaults#S
\toggleAttachmentsPanel{arg1}{arg2}#S
\txtRef{arg1}#S
\unicodeStr#S
\unicodeStrSAVE#S
\useNewRadiosOff#S
\useNewRadiosOn#S
\Win#S