# tabularray package
# Matthew Bertucci 7/4/2021

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

\SetTblrInner[opt env name]{keyvals}

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

\SetTblrOuter[opt env name]{keyvals}

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

\multirow[keyvals]{rows}{width}{contents}#/tblr,longtblr

#keyvals:\multirow
t
b
c
#endkeyvals

\SetCell[r=%<rows%>,c=%<columns%>]{keyvals}#/tblr,longtblr

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

\SetRow{keyvals}#/tblr,longtblr

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

\SetColumn{keyvals}#/tblr,longtblr

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

\NewColumnType{name}[number][optarg]{definition}#d
\NewRowType{name}[number][optarg]{definition}#d
\NewColumnRowType{name}[number][optarg]{definition}#*d

\NewTableCommand{command}{definition}#d

\hline[keyvals]#/tblr,longtblr
\cline[keyvals]{arg}#/tblr,longtblr

#keyvals:\hline#c,\cline#c
dash=#solid,dashed,dotted
dashed
dotted
text=
wd=##L
fg=#%color
#endkeyvals

\NewChildSelector#*

\leftsep#/tblr
\rightsep#/tblr
\abovesep#/tblr
\belowsep#/tblr

\SetTblrTracing{keyvals}#*

#keyvals:\SetTblrTracing
all
none
+row
+column
#endkeyvals

\NewTblrTheme{name}{specs}

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

\TblrNote{arg}#/tblr,longtblr

\DefTblrTemplate{arg1}{arg2}{arg3}#*d
\SetTblrTemplate{arg1}{arg2}#*
\UseTblrTemplate{arg1}{arg2}#*
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
#endkeyvals