# easyfloats package
# Matthew Bertucci 2022/05/02 for v1.0.0

#include:etoolbox
#include:pgfkeys
#include:float
#include:caption
#include:environ
#include:subcaption
#include:graphicx
#include:array
#include:booktabs

#keyvals:\usepackage/easyfloats#c
graphicx
graphbox
nographic
longtable
nolongtable
booktabs
nobooktabs
array
noarray
allowstandardfloats
#endkeyvals

#ifOption:graphbox
#include:graphbox
#keyvals:\includegraphicobject#c,\includegraphicsubobject#c
hide#true,false
align=#b,c,l,m,t,u
vsmash=#b,c,l,m,n,t,u
hsmash=#c,l,n,r
smash=%<vpos%>%<hpos%>
vshift=##L
hshift=##L
tmargin=##L
bmargin=##L
vmargin=##L
lmargin=##L
rmargin=##L
hmargin=##L
margin=##L
#endkeyvals
#keyvals:\begin{object}#c,\begin{figureobject}#c,\begin{tableobject}#c,\begin{subobject}#c,\includegraphicobject#c,\includegraphicsubobject#c,\objectset#c,\NewObjectStyle#c
graphic hide#true,false
graphic align=#b,c,l,m,t,u
graphic vsmash=#b,c,l,m,n,t,u
graphic hsmash=#c,l,n,r
graphic smash=%<vpos%>%<hpos%>
graphic vshift=##L
graphic hshift=##L
graphic tmargin=##L
graphic bmargin=##L
graphic vmargin=##L
graphic lmargin=##L
graphic rmargin=##L
graphic hmargin=##L
graphic margin=##L
#endkeyvals
#endif

#ifOption:longtable
#include:longtable
#endif

\begin{object}{options%keyvals}#*
\end{object}#*
\begin{figureobject}{options%keyvals}
\end{figureobject}
\begin{tableobject}{options%keyvals}#\tabular
\end{tableobject}

#keyvals:\begin{object}#c,\begin{figureobject}#c,\begin{tableobject}#c,\begin{subobject}#c,\includegraphicobject#c,\includegraphicsubobject#c,\objectset#c,\NewObjectStyle#c
type=%<type%>
float style=#plain,plaintop,ruled,boxed
caption=%<text%>
list caption=%<text%>
details=%<text%>
details sep=%<code%>
label=##l
add label=##l
placement=%<placement%>
align=%<code%>
exec=%<code%>
exec +=%<code%>
graphic alt={%<alt text%>}
graphic bb=%<llx lly urx ury%>
graphic bbllx=
graphic bblly=
graphic bburx=
graphic bbury=
graphic natwidth=
graphic natheight=
graphic hiresbb#true,false
graphic pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
graphic viewport=%<llx lly urx ury%>
graphic trim=%<llx lly urx ury%>
graphic angle=%<degrees%>
graphic origin=
graphic width=##L
graphic height=##L
graphic totalheight=##L
graphic keepaspectratio#true,false
graphic scale=%<factor%>
graphic clip#true,false
graphic draft#true,false
graphic type=%<file type%>
graphic ext=%<file extension%>
graphic read=%<read-file extension%>
graphic command=
graphic quiet
graphic page=%<page number%>
graphic interpolate#true,false
graphic decodearray={%<color array%>}
env=%<envname%>
%<env%> arg=%<value%>
%<env%> args=%<value%>
arg=%<value%>
args=%<value%>
%<env%> arg +=%<value%>
%<env%> args +=%<value%>
arg +=%<value%>
args +=%<value%>
show env args#true,false
warn no caption#true,false
warn no label#true,false
warn other env#true,false
subcaptionbox
subcaptionbox inner pos=#c,l,r,s
subpage
subpage outer pos=#c,t,b,T,B,auto,Auto
subpage height=##L
subpage inner pos=#c,t,b,s
subpage align=%<code%>
#endkeyvals

#keyvals:\begin{object}#c,\begin{figureobject}#c,\begin{tableobject}#c,\includegraphicobject#c,\objectset#c,\NewObjectStyle#c
first head=%<code%>
last foot=%<code%>
head=%<code%>
foot=%<code%>
table head=%<code%>
table break text=%<text%>
table head style=%<code%>
contains subobjects#true,false
subobject linewidth
subobject sep=%<code%>
subobject hor=%<code%>
subobject hor sep=%<code%>
subobject hor sep +=%<code%>
subobject ver=%<code%>
subobject ver sep=%<code%>
subobject ver sep +=%<code%>
subobject exec=%<code%>
subobject exec +=%<code%>
subobject env=%<envname%>
subobject warn no caption#true,false
subobject warn no label#true,false
#endkeyvals

\begin{subobject}{options%keyvals}
\end{subobject}

#keyvals:\begin{subobject}#c,\includegraphicsubobject#c
linewidth=##L
sep=%<code%>
hor=%<code%>
hor sep=%<code%>
hor sep +=%<code%>
ver=%<code%>
ver sep=%<code%>
ver sep +=%<code%>
#endkeyvals

\includegraphicobject{imagefile}#g
\includegraphicobject[options%keyvals]{imagefile}#g
# following line messes with the keyval completion
# \includegraphicobject[style name][options%keyvals]{imagefile}#g
\includegraphicsubobject{imagefile}#g
\includegraphicsubobject[options%keyvals]{imagefile}#g

#keyvals:\includegraphicobject#c,\includegraphicsubobject#c
auto caption#true,false
auto caption strip path#true,false
auto label#true,false
auto label strip path#true,false
warn env#true,false
no env#true,false
# \includegraphics options
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

\objectset{options%keyvals}
\objectset[style names]{options%keyvals}
\graphicobjectstyle{style name}
\NewObjectStyle{style name}{options%keyvals}
\NewObjectStyleGroup{group}{style names}
\AddObjectStyleToGroup{group}{style name}
\AtBeginObject{code}
\AtBeginSubobject{code}
\AtBeginGraphicObject{code}
\ShowObjectStylesInGroup{group}
\ShowObjectStyleOptions{style name}

# not documented
\AppendGraphicobjectOption{option}{value}#*
\AppendOptionToObjectStyle{style name}{option}{value}#*
\AppendOptionToObjectStyleGroup{group}{option}{value}#*
\AppendOptionToObjectStyleGroups{groups}{option}{value}#*
\AppendToOptionsList{macro}{option}{value}#*
\CheckGraphicobjectOption{option}{value}#*
\CheckObjectEnvArgs{option}{value}#*
\CheckObjectGraphicOption{option}{value}#*
\CheckObjectOption{option}{value}#*
\DeprecateStandardFloatObject{envname}{alt object envname}#*
\GobbleLeadingSpaceIn{arg}#*
\IfEndsOn{char}{text}{true}{false}#*
\IfEndsOnPlus{arg}{true}{false}#*
\IfEndsOnSpacePlus{arg}{true}{false}#*
\IfEnvironmentExists{envname}{true}{false}#*
\IfEnvironmentExistsOrIsEmpty{envname}{true}{false}#*
\IfObjectStyleExists{style name}{true}{false}#*
\IfObjectStyleNotGroup{style name}{true}{false}#*
\ObjectAppendEnvargs{macro}#*
\ObjectDefineEnvargs{envname}{arguments}#*
\ObjectDefineEnvargsAuto{arguments}#*
\ObjectDefineEnvargsCheckName{envname}{arguments}#*
\ObjectProcessArgs{option}{value}{else}#*
\ObjectProcessGraphicOption{option}{value}{else}#*
\ObjectProcessKeyPattern{option}{value}{else}#*
\PatchUnderscore{macro}#*
\StripGraphicSpace{arg}#*
\strippath{arg}#*
\StripPlus{arg}#*
\StripSpacePlus{arg}#*