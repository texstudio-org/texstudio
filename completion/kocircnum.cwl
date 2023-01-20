# kocircnum package
# ponte-vecchio 2023-01-17 for v1.2.1

#keyvals:\usepackage/kocircnum#c
hcr
hz
tikz
tikzsmall
tikzbig
#endkeyvals

## 2.3 hcrcircnum
\hcrcircnum{%<number%>}
\hcrcircnum*{%<number%>}
\hcrcircnum[%<args%>%keyvals]{%<number%>}
\hcrcircnum*[%<arg%>%keyvals]{%<number%>}
\hcrcircnumsetup{%<args%>%keyvals}
\restorehcrcircnumsetup

#keyvals:\hcrcircnum#c
shape=%<shape%>#circle,box,rectangle
white
black
color=#%color
font=%<font options%>
reset
#endkeyvals

#keyvals:\hcrcircnumsetup#c
shape=%<shape%>#circle,box,rectangle
color=#%color
#endkeyvals

## 2.4 hzcircnum
\hzcircnum{%<number%>}
\hzcircnum*{%<number%>}
\hzcircnum[%<args%keyvals]{%<number%>}
\hzcircnum*[%<args%>%keyvals]{%<number%>}
\hzcircnumsetup{%<args%>%keyvals}
\restorehzcircnumsetup

#keyvals:\hzcircnum#c,\hzcircnumsetup#c
shape=%<shape%>#circle,circ,rectangle,rect,oval,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
sep=%<sep%>%l
raise=%<dim%>%l
Raise=%<dim%>%l
font=%<font options%>
fontplus=%<font options%>
base
reset
#endkeyvals

## 2.5 tikzcircnum
\tikzcircnum{%<number%>}
\tikzcircnum*{%<number%>}
\tikzcircnum[%<args%>%keyvals]{%<number%>}
\tikzcircnum*[%<args%>%keyvals]{%<number%>}
\tikzcircnumsetup[%<args%>%keyvals]{%<number%>}
\tikzcircnumonce[%<args%>%keyvals]{%<number%>}
\settikzcircnumsetup{%<args%>%keyvals}
\restoretikzcircnumsetup#*
\declaretikzcircnumsmallsetup#*
\declaretikzcircnumbigsetup#*

#keyvals:\tikzcircnum#c,\tikzcircnumsetup#c,\tikzcircnumonce#c,\settikzcircnumsetup#c
shape=%<shape%>#circle,rectangle,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
bdcolor=#%color
colorinv=#%color
round=%<dim%>%l
raise=%<dim%>%l
Raise=%<dim%>%l
sep=%<dim%>%l
sepplus=%<dim%>%l
font=%<font options%>
fontplus=%<font options%>
base=%<text%>
bdwidth=%<dim%>%l
linewidth=%<dim%>%l
reset
#endkeyvals

## 2.6 Defaults
\circnum[%<args%>%keyvals]{%<number%>}
\circnum*[%<args%>%keyvals]{%<number%>}
\circnumsetup{%<args%>%keyvals}
\restorecircnumsetup
\Cnum{%<counter%>}

#ifOption:hcr
#keyvals:\circnum#c,\circnumsetup#c
shape=%<shape%>#circle,circ,rectangle,rect,oval,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
sep=%<sep%>%l
raise=%<dim%>%l
Raise=%<dim%>%l
font=%<font options%>
fontplus=%<font options%>
base
reset
#endkeyvals
#endif

#ifOption:hz
#keyvals:\circnum#c,\circnumsetup#c
shape=%<shape%>#circle,circ,rectangle,rect,oval,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
sep=%<sep%>%l
raise=%<dim%>%l
Raise=%<dim%>%l
font=%<font options%>
fontplus=%<font options%>
base
reset
#endkeyvals
#endif

#ifOption:tikz
#keyvals:\circnum#c,\circnumsetup#c
shape=%<shape%>#circle,rectangle,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
bdcolor=#%color
colorinv=#%color
round=%<dim%>%l
raise=%<dim%>%l
Raise=%<dim%>%l
sep=%<dim%>%l
sepplus=%<dim%>%l
font=%<font options%>
fontplus=%<font options%>
base=%<text%>
bdwidth=%<dim%>%l
linewidth=%<dim%>%l
reset
#endkeyvals
#endif