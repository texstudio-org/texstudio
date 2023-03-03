# tabularray package
# Matthew Bertucci 2023/02/28 for v2023A

#include:ninecolors

\begin{tblr}{preamble}#\tabular
\begin{tblr}[outer specs%keyvals]{preamble}#\tabular
\end{tblr}

\SetTblrOuter{options%keyvals}
\SetTblrOuter[envname]{options%keyvals}

#keyvals:\SetTblrOuter#c
halign=#l,c,r
valign=#t,m,b
l
c
r
t
m
b
headsep=##L
footsep=##L
presep=##L
postsep=##L
theme=%<theme%>
caption=%<caption text%>
entry=%<short caption text%>
label=##l
baseline=#t,T,m,b,B,%<row number%>
long
tall
expand
#endkeyvals

\SetTblrInner{options%keyvals}
\SetTblrInner[envname]{options%keyvals}

#keyvals:\SetTblrInner#c,\begin{tblr}#c,\begin{+matrix}#c,\begin{+bmatrix}#c,\begin{+Bmatrix}#c,\begin{+pmatrix}#c,\begin{+vmatrix}#c,\begin{+Vmatrix}#c,\begin{+cases}#c,\begin{booktabs}#c,\begin{longtabs}#c,\begin{talltabs}#c
colspec={%<col types%>}
rowspec={%<row types%>}
width=##L
hspan=#default,even,minimal
vspan=#default,even
stretch=%<factor%>
columns={%<styles%>}
rows={%<styles%>}
cells={%<styles%>}
hlines
hlines={%<styles%>}
hlines={%<cols%>}{%<styles%>}
vlines
vlines={%<styles%>}
vlines={%<rows%>}{%<styles%>}
leftsep=##L
rightsep=##L
colsep=##L
abovesep=##L
belowsep=##L
rowsep=##L
rulesep=##L
rowhead=%<number%>
rowfoot=%<number%>
column{%<j%>}={%<styles%>}
column
row{%<i%>}={%<styles%>}
row
cell{%<i%>}{%<j%>}={%<styles%>}
cell
vline{%<j%>}={%<index%>}{%<cols%>}{%<styles%>}
vline
hline{%<i%>}={%<index%>}{%<cols%>}{%<styles%>}
hline
measure=#vbox
baseline=#t,T,m,b,B,%<row number%>
delimiter={%<keyvals%>}
#endkeyvals

\SetHline{cols}{styles%keyvals}#*
\SetHline[index]{cols}{styles%keyvals}#*
\SetHlines{cols}{styles%keyvals}#*
\SetHlines[index]{cols}{styles%keyvals}#*
\SetVspace{styles%keyvals}#*
\hline#*
\hline[styles%keyvals]#*
\cline{index}#*
\cline[styles%keyvals]{index}#*

#keyvals:\SetHline#c,\SetHlines#c,\SetVspace#c,\hline#c,\cline#c,\toprule#c,\midrule#c,\cmidrule#c,\bottomrule#c,\cmidrulemore#c,\specialrule#c
dash=#solid,dashed,dotted
solid
dashed
dotted
text=
wd=##L
%<width%>
fg=#%color
%<color%>
leftpos=
rightpos=
endpos#true,false
abovespace=##L
belowspace=##L
abovespace+=##L
belowspace+=##L
#endkeyvals

\therownum#*
\thecolnum#*
\therowcount#*
\thecolcount#*
\tablewidth#*

\SetVline{rows}{styles%keyvals}#*
\SetVline[index]{rows}{styles%keyvals}#*
\SetVlines{rows}{styles%keyvals}#*
\SetVlines[index]{rows}{styles%keyvals}#*
\vline#*
\vline[styles%keyvals]#*
\rline{index}#*
\rline[styles%keyvals]{index}#*

#keyvals:\SetVline#c,\SetVlines#c,\vline#c,\rline#c
dash=#solid,dashed,dotted
solid
dashed
dotted
text=
wd=##L
%<width%>
fg=#%color
%<color%>
abovepos=
belowpos=
#endkeyvals

\SetCell{%<options%>}
\SetCell[r=%<rows%>,c=%<columns%>]{%<options%>}
\SetCells{%<options%>}
\SetCells[r=%<rows%>,c=%<columns%>]{%<options%>}

#keyvals:\SetCell#c,\SetCells#c
halign=#l,c,r
l
c
r
valign=#t,m,b,h,f
t
m
b
h
f
wd=##L
%<width%>
bg=#%color
%<background color%>
fg=#%color
font=%<font commands%>
mode=#math,imath,dmath,text
$
$$
cmd=%<command%>
preto=%<text%>
appto=%<text%>
#endkeyvals

\SetRow{styles%keyvals}#*
\SetRows{styles%keyvals}#*

#keyvals:\SetRow#c,\SetRows#c
halign=#l,c,r
l
c
r
valign=#t,m,b,h,f
t
m
b
h
f
ht=##L
%<height%>
bg=#%color
%<background color%>
fg=#%color
font=%<font commands%>
mode=#math,imath,dmath,text
$
$$
cmd=%<command%>
abovesep=##L
abovesep+=##L
belowsep=##L
belowsep+=##L
rowsep=##L
rowsep+=##L
preto=%<text%>
appto=%<text%>
#endkeyvals

\SetColumn{styles%keyvals}#*
\SetColumns{styles%keyvals}#*

#keyvals:\SetColumn#c,\SetColumns#c
halign=#l,c,r
l
c
r
valign=#t,m,b,h,f
t
m
b
h
f
wd=##L
%<width%>
co=%<coeff%>
bg=#%color
%<background color%>
fg=#%color
font=%<font commands%>
mode=#math,imath,dmath,text
$
$$
cmd=%<command%>
leftsep=##L
leftsep+=##L
rightsep=##L
rightsep+=##L
colsep=##L
colsep+=##L
preto=%<text%>
appto=%<text%>
#endkeyvals

\hborder{options%keyvals}#*

#keyvals:\hborder#c
pagebreak=#yes,no,auto
abovespace=##L
belowspace=##L
abovespace+=##L
belowspace+=##L
#endkeyvals

\vborder{options%keyvals}#*

#keyvals:\vborder#c
leftspace=##L
rightspace=##L
leftspace+=##L
rightspace+=##L
#endkeyvals

\NewColumnType{name}{definition}
\NewColumnType{name}[args][default]{definition}
\NewRowType{name}{definition}
\NewRowType{name}[args][default]{definition}
\NewColumnRowType{name}{definition}#*
\NewColumnRowType{name}[args][default]{definition}#*

\NewTblrEnviron{envname}#N

\NewTableCommand{cmd}{definition}#d
\NewTableCommand{cmd}[args]{definition}#d
\NewTableCommand{cmd}[args][default]{definition}#d

\NewChildSelector{arg1}{arg2}#*
\NewChildSelector{arg1}[opt1][opt2]{arg2}#*

\leftsep#*
\rightsep#*
\abovesep#*
\belowsep#*

\SetTblrTracing{settings%keyvals}#*
\SetTabularrayTracing{settings%keyvals}#S

#keyvals:\SetTblrTracing#c,\SetTabularrayTracing#c
all
none
+row
+column
+text
-text
+command
-command
+option
-option
+theme
-theme
+outer
-outer
+inner
-inner
-column
-row
+cell
-cell
+vline
-vline
+hline
-hline
+colspec
-colspec
+rowspec
-rowspec
+target
-target
+cellspan
-cellspan
+intarray
-intarray
+page
-page
+step
-step
#endkeyvals

\begin{longtblr}{preamble}#\tabular
\begin{longtblr}[outer specs%keyvals]{preamble}#\tabular
\end{longtblr}
\begin{talltblr}{preamble}#\tabular
\begin{talltblr}[outer specs%keyvals]{preamble}#\tabular
\end{talltblr}

#keyvals:\begin{longtblr}#c,\begin{talltblr}#c
headsep=##L
footsep=##L
presep=##L
postsep=##L
theme=#%tblrtheme
caption={%<text%>}
entry={%<text%>}
label=##l
note{%<name%>}={%<text%>}
remark{%<name%>}={%<text%>}
#endkeyvals

\DefTblrTemplate{element%keyvals}{template name}{definition}#*
\DeclareTblrTemplate{element%keyvals}{template name}{definition}#*
\SetTblrTemplate{element%keyvals}{template name}{definition}#*
\UseTblrTemplate{element%keyvals}{default}#*
\ExpTblrTemplate{element%keyvals}{default}#*

#keyvals:\DefTblrTemplate#c,\DeclareTblrTemplate#c,\SetTblrTemplate#c,\UseTblrTemplate#c,\ExpTblrTemplate#c
contfoot-text
contfoot
conthead-text
conthead
conthead-pre
caption-tag
caption-sep
caption-text
caption
caption-lot
capcont
note-tag
note-sep
note-text
note-border
note
remark-tag
remark-sep
remark-text
remark
firsthead
middlehead
lasthead
head
firstfoot
middlefoot
lastfoot
foot
#endkeyvals

\tblrcontfootname#*
\tblrcontheadname#*

\SetTblrStyle{element}{styles%keyvals}

#keyvals:\SetTblrStyle#c
fg=#%color
%<color%>
font=%<commands%>
%<font commands%>
halign=#l,c,r
l
c
r
indent=##L
hang=##L
#endkeyvals

\NewTblrTheme{theme name%specialDef}{specs}#s#%tblrtheme

\TblrNote{mark-symbol}
\InsertTblrText{key%plain}#*
\InsertTblrNoteTag#*
\InsertTblrNoteText#*
\InsertTblrRemarkTag#*
\InsertTblrRemarkText#*
\MapTblrNotes{code}#*
\MapTblrRemarks{code}#*

\NewTblrLibrary{name}{code}#*
\UseTblrLibrary{library%keyvals}#u

#keyvals:\UseTblrLibrary#c
amsmath
booktabs
counter
diagbox
functional
nameref
siunitx
varwidth
zref
#endkeyvals

# miscellaneous undocumented
\LogTblrTracing{arg}#*
\LogTabularrayTracing{arg}#S
\GetTblrStyle{element}{key%plain}#*
\UseTblrAlign{element}#*
\UseTblrIndent{element}#*
\UseTblrHang{element}#*
\UseTblrColor{element}#*
\UseTblrFont{element}#*
\InsertTblrMore{arg}#*
\NewDashStyle{name}{definition}#*
\NewContentCommand{cmd}{definition}#*d
\NewContentCommand{cmd}[args]{definition}#*d
\NewContentCommand{cmd}[args][default]{definition}#*d
\TblrParboxRestore#*
\TblrAlignBoth#*
\TblrAlignLeft#*
\TblrAlignCenter#*
\TblrAlignRight#*
\TblrNewPage#*
\rulewidth#*L
\SetTblrDefault{options}#S
\TblrOverlap#*
\begin{tblrNoHyper}#S
\end{tblrNoHyper}#S
\pagebreak[number]#*
\nopagebreak[number]#*
\lTblrCaptionTl#S
\lTblrEntryTl#S
\lTblrLabelTl#S
\lTblrMeasuringBool#*
\lTblrRefMoreClist#S
