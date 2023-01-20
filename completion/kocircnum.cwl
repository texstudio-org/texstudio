# kocircnum package
# ponte-vecchio 2023-01-17 for v1.2.1

#include:tikz
#include:tikzlibraryshadings
#include:tikzlibraryshapes
#include:fontspec

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
\hcrcircnum[%<options%>]{%<number%>}
\hcrcircnum*[%<options%>]{%<number%>}
\hcrcircnumsetup{%<options%>}
\restorehcrcircnumsetup

#keyvals:\hcrcircnum#c,\hcrcircnum*#c,\hcrcircnumsetup#c
shape=#circle,box,rectangle
white
black
color=#%color
font=%<font commands%>
reset
#endkeyvals

## 2.4 hzcircnum
\hzcircnum{%<number%>}
\hzcircnum*{%<number%>}
\hzcircnum[%<args%keyvals]{%<number%>}
\hzcircnum*[%<args%>%keyvals]{%<number%>}
\hzcircnumsetup{%<args%>%keyvals}
\restorehzcircnumsetup

#keyvals:\hzcircnum#c,\hzcircnum*#c,\hzcircnumsetup#c
shape=#circle,circ,rectangle,rect,oval,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
sep=##L
raise=##L
Raise=##L
font=%<font commands%>
fontplus=%<font commands%>
base=%<text%>
reset
#endkeyvals

## 2.5 tikzcircnum
\tikzcircnum{%<number%>}
\tikzcircnum*{%<number%>}
\tikzcircnum[%<options%>]{%<number%>}
\tikzcircnum*[%<options%>]{%<number%>}
\tikzcircnumsetup{%<options%>}
\tikzcircnumonce[%<options%>]{%<number%>}
\settikzcircnumsetup{%<options%>}
\restoretikzcircnumsetup
\declaretikzcircnumsmallsetup#*
\declaretikzcircnumbigsetup#*

#keyvals:\tikzcircnum#c,\tikzcircnum*#c,\tikzcircnumsetup#c,\tikzcircnumonce#c,\settikzcircnumsetup#c
shape=#circle,rectangle,ball
color=#%color
bgcolor=#%color
fgcolor=#%color
bdcolor=#%color
colorinv=#%color
round=##L
raise=##L
Raise=##L
sep=##L
sepplus=##L
font=%<font commands%>
fontplus=%<font commands%>
base=%<text%>
bdwidth=##L
linewidth=##L
reset
#endkeyvals

## 2.6 Defaults
\circnum{%<number%>}
\circnum[%<options%>]{%<number%>}
\circnum*{%<number%>}
\circnum*[%<options%>]{%<number%>}
\circnumsetup{%<options%>}
\restorecircnumsetup
\Cnum{%<counter%>}

# default hcr
#keyvals:\circnum#c,\circnum*#c,\circnumsetup#c
shape=#circle,circ,rectangle,rect,oval,ball
white
black
color=#%color
font=%<font commands%>
reset
#endkeyvals

#ifOption:hz
#keyvals:\circnum#c,\circnum*#c,\circnumsetup#c
bgcolor=#%color
fgcolor=#%color
sep=##L
raise=##L
Raise=##L
font=%<font commands%>
fontplus=%<font commands%>
base=%<text%>
#endkeyvals
#endif

#ifOption:tikz
#keyvals:\circnum#c,\circnum*#c,\circnumsetup#c
bgcolor=#%color
fgcolor=#%color
bdcolor=#%color
colorinv=#%color
round=##L
raise=##L
Raise=##L
sep=##L
sepplus=##L
font=%<font commands%>
fontplus=%<font commands%>
base=%<text%>
bdwidth=##L
linewidth=##L
#endkeyvals
#endif

# not documented
\forcerestoretikzcircnumsetup#S
\hcrannonum{arg1}{arg2}{arg3}#S
\hcrnumberboxblack{arg}#S
\hcrnumberboxwhite{arg}#S
\hcrnumbercircleblack{arg}#S
\hcrnumbercirclewhite{arg}#S
\hcrnumberrectangleblack{arg}#S
\hcrnumberrectanglewhite{arg}#S
\hzballnum{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}#S
\hzcirclenum{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}#S
\hzovalnum{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}#S
\hzrectanglenum{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}#S
