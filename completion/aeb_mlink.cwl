# aeb_mlink package
# Matthew Bertucci 2022/05/10 for v2.3.6

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:hyperref
#include:eforms
#include:refcount
#include:soul

#keyvals:\usepackage/aeb_mlink#c
dvipsone
dvips
dblevel=#0,1,2
urlOpts={%<url package options%>}
# options passed to eforms
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

\mlhypertext{link text%text}
\mlhypertext[modifications]{link text%text}
\mlsetLink{link text%text}
\mlsetLink[modifications]{link text%text}
\mlhyperlink{target name}{link text%text}
\mlhyperlink[modifications]{target name}{link text%text}
\mlhyperref{label%ref}{text}
\mlhyperref[modifications]{label%ref}{text}
\mlnameref{label%ref}
\mlnameref[modifications]{label%ref}
\mlNameref{label%ref}
\mlNameref[modifications]{label%ref}
\mlhref{URL}{text}#U
\mlhref[modifications]{URL}{text}#U
\mlurl{URL}#U
\mlurl[modifications]{URL}#U
\mlfixOn
\mlfixOff
\mlfix{y|n}
\mlcs{csname}
\OldStyleBoxesOn
\OldStyleBoxesOff
\mlMarksOn
\mlMarksOff
\turnSyllbCntOn
\turnSyllbCntOff

# not documented
\aebnameref{label}#*r
\atPage{label}#*r
\bWebCustomize#S
\CMT{arg}#*
\CurrentBorderColor#*
\eWebCustomize#S
\FixupProc#*
\iffixmlinks#S
\iflinknotformed#S
\ifmllinktotalchanged#S
\ifmlmarks#S
\ifoldstylequads#S
\ifSmallRect#S
\isWindow#*
\itsunderline#S
\labelRef{label}#*r
\linknotformedfalse#S
\linknotformedtrue#S
\mlcsarg{arg1}{arg2}#S
\mldb{arg1}{arg2}#*
\mldblevel#*
\mldbModeOff#*
\mldbModeOn#*
\mlDict#*
\mlinkstotal#S
\mllinktotalchangedfalse#S
\mllinktotalchangedtrue#S
\mllnkcontainer{arg}#*
\mlmarksfalse#S
\mlmarkstrue#S
\mlMaxNSylls#*
\mlpgMsg#S
\MrkLnkLtr#*
\oldstylequadsfalse#S
\oldstylequadstrue#S
\pboxRect#*
\pgmonitoring#*
\removelastspace#*
\revCrackAt#*
\setQuadBox#*
\SmallRectfalse#S
\smallRectTF#*
\SmallRecttrue#S
\syllableCnt#*
\theView#*