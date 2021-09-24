# tabularray package
# Matthew Bertucci 9/21/2021 for v2021N

\begin{tblr}{preamble%keyvals}#\tabular
\end{tblr}

#keyvals:\begin{tblr}#c
colspec=
rowspec=
width=##L
hspan=#default,even,minimal
vspan=#default,even
stretch=
columns=
rows=
cells=
hlines=
vlines=
leftsep=##L
rightsep=##L
colsep=##L
abovesep=##L
belowsep=##L
rowsep=##L
rulesep=##L
rowhead=
rowfoot=
column
row
cell
vline
hline
#endkeyvals

\SetTblrInner{options%keyvals}
\SetTblrInner[envname]{options%keyvals}#N

#keyvals:\SetTblrInner
colspec=
rowspec=
width=##L
hspan=#default,even,minimal
vspan=#default,even
stretch=
columns=
rows=
cells=
hlines=
vlines=
leftsep=##L
rightsep=##L
colsep=##L
abovesep=##L
belowsep=##L
rowsep=##L
rulesep=##L
rowhead=
rowfoot=
#endkeyvals

\SetTblrOuter{options%keyvals}
\SetTblrOuter[envname]{options%keyvals}#N

#keyvals:\SetTblrOuter
long
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
theme=
caption=
entry=
label=
#endkeyvals

\multirow{rows}{width}{contents}#/tblr,longtblr
\multirow[pos%keyvals]{rows}{width}{contents}#/tblr,longtblr

#keyvals:\multirow
t
b
c
#endkeyvals

\SetCell{%<options%>}#/tblr,longtblr
\SetCell[r=%<rows%>,c=%<columns%>]{%<options%>}#/tblr,longtblr

#keyvals:\SetCell#c
halign=#l,c,r
valign=#t,m,b,h,f
l
c
r
t
m
b
h
f
wd=##L
bg=#%color
fg=#%color
font=
preto=
appto=
cmd=
#endkeyvals

\SetRow{styles%keyvals}#/tblr,longtblr

#keyvals:\SetRow#c
halign=#l,c,r
valign=#t,m,b,h,f
l
c
r
t
m
b
h
f
ht=##L
wd=##L
bg=#%color
fg=#%color
font=
abovesep=##L
abovesep+=##L
belowsep=##L
belowsep+=##L
rowsep=##L
rowsep+=##L
preto=
appto=
cmd=
#endkeyvals

\SetColumn{styles%keyvals}#/tblr,longtblr

#keyvals:\SetColumn#c
halign=#l,c,r
valign=#t,m,b,h,f
l
c
r
t
m
b
h
f
wd=##L
co=
bg=#%color
fg=#%color
font=
leftsep=##L
leftsep+=##L
rightsep=##L
rightsep+=##L
colsep=##L
colsep+=##L
preto=
appto=
cmd=
#endkeyvals

\NewColumnType{name}{definition}
\NewColumnType{name}[number][optarg]{definition}
\NewRowType{name}{definition}
\NewRowType{name}[number][optarg]{definition}
\NewColumnRowType{name}{definition}#*
\NewColumnRowType{name}[number][optarg]{definition}#*

\NewTableCommand{cmd}{definition}#d

\hline
\hline[options%keyvals]
\cline{arg}
\cline[options%keyvals]{arg}

#keyvals:\hline#c,\cline#c
dash=#solid,dashed,dotted
dashed
dotted
text=
wd=##L
fg=#%color
#endkeyvals

\NewChildSelector#*

\leftsep#*
\rightsep#*
\abovesep#*
\belowsep#*

\SetTblrTracing{settings%keyvals}#*

#keyvals:\SetTblrTracing
all
none
+row
+column
#endkeyvals

\NewTblrTheme{name}{specs}

\begin{longtblr}{preamble}#\tabular
\begin{longtblr}[outer specs%keyvals]{preamble}#\tabular
\end{longtblr}

#keyvals:\begin{longtblr}#c
long
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
theme=
caption=
entry=
label=
note
remark
#endkeyvals

\SetTblrStyle{part}{specs%keyvals}

#keyvals:\SetTblrStyle#c
fg=#%color
font=
halign=#l,c,r
l
c
r
indent=##L
hang=##L
#endkeyvals

\TblrNote{mark-symbol}#/tblr,longtblr

\DefTblrTemplate{template}{type}{contents}#*
\SetTblrTemplate{template}{type}#*
\UseTblrTemplate{template}{type}#*
\ExpTblrTemplate
\InsertTblrText{arg}#*
\InsertTblrNoteTag#*
\InsertTblrNoteText#*
\InsertTblrRemarkTag#*
\InsertTblrRemarkText#*
\MapTblrNotes{arg}#*
\MapTblrRemarks{arg}#*

\UseTblrLibrary{library%keyvals}

#keyvals:\UseTblrLibrary#c
booktabs
diagbox
siunitx
varwidth
#endkeyvals
