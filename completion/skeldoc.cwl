# skeldoc package
# Matthew Bertucci 2022/07/20 for v0.1.2

#include:xcolor
#include:tabularx
#include:booktabs
#include:hyperref
#include:enotez
#include:marginnote
#include:enumitem

\skelset{options%keyvals}

#keyvals:\skelset
main-color=#%color
full-width=##L
short-width=##L
fill-width=##L
hypersetup={%<hyperref options%>}
min-mpwidth=##L
line-raise=##L
line-height=##L
note-font=%<font commands%>
note-color=#%color
line-width=##L
ref-width=##L
cite-width=##L
cite-left=%<code%>
cite-right=%<code%>
par-lines=%<integer%>
par-first-width=##L
par-width=##L
par-last-width=##L
fig-width=##L
fig-height=##L
caption-lines=%<integer%>
pars-pars=%<integer%>
list-items=%<integer%>
list-item-lines=%<integer%>
tabular-rows=%<integer%>
tabular-colsep=##L
tabular-stretch=%<factor%>
bib-items=%<integer%>
bib-item-lines=%<integer%>
pseudo-lines=%<integer%>
pseudo-head=
pseudo-newlines={%<cmd1,cmd2,...%>}
#endkeyvals

\skelline
\skelline[width]
\skelline{note%text}
\skelline[width]{note%text}

\skelref
\skelref[width]
\skelref{note%text}
\skelref[width]{note%text}

\skelcite
\skelcite[options%keyvals]
\skelcite{note%text}
\skelcite[options%keyvals]{note%text}

#keyvals:\skelcite#c
%<width%>
width=##L
left=%<code%>
right=%<code%>
#endkeyvals

\skelpar
\skelpar[options%keyvals]
\skelpar{note%text}
\skelpar[options%keyvals]{note%text}

#keyvals:\skelpar#c
%<lines%>
lines=%<integer%>
first-width=##L
width=##L
last-width=##L
#endkeyvals

\skelfig
\skelfig[options%keyvals]
\skelfig{note%text}
\skelfig[options%keyvals]{note%text}

#keyvals:\skelfig#c
%<height%>
width=##L
height=##L
#endkeyvals

\skelcaption
\skelcaption[options%keyvals]
\skelcaption{note%text}
\skelcaption[options%keyvals]{note%text}

#keyvals:\skelcaption#c
%<lines%>
lines=%<integer%>
first-width=##L
width=##L
last-width=##L
#endkeyvals

\skelpars
\skelpars[pars]
\skelpars{note%text}
\skelpars[pars]{note%text}

\skelitems
\skelitems[options%keyvals]
\skelitems{note%text}
\skelitems[options%keyvals]{note%text}
\skelenum
\skelenum[options%keyvals]
\skelenum{note%text}
\skelenum[options%keyvals]{note%text}

#keyvals:\skelitems#c,\skelenum#c
%<items%>
items=%<integer%>
item-lines=%<integer%>
#endkeyvals

\skeltabular
\skeltabular[options%keyvals]
\skeltabular{note%text}
\skeltabular[options%keyvals]{note%text}

#keyvals:\skeltabular#c
%<rows%>
rows=%<integer%>
colsep=##L
stretch=%<factor%>
#endkeyvals

\skelbib
\skelbib[options%keyvals]
\skelbib{note%text}
\skelbib[options%keyvals]{note%text}

#keyvals:\skelbib#c
%<items%>
items=%<integer%>
item-lines=%<integer%>
#endkeyvals

\skelpseudo
\skelpseudo[options%keyvals]
\skelpseudo{note%text}
\skelpseudo[options%keyvals]{note%text}

#keyvals:\skelpseudo#c
%<lines%>
lines=%<integer%>
head=
newlines={%<cmd1,cmd2,...%>}
#endkeyvals

\skelnote{note%text}
\printskelnotes

skel-blue#B

\skelversion#S
\skeldate#S