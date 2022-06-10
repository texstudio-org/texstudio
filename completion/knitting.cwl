# knitting package
# Matthew Bertucci 2022/06/08 for v3

#include:color

#keyvals:\usepackage/knitting#c
chartsonly
#endkeyvals

\chart{knitting-specs}
\chart[placement%keyvals]{knitting-specs}
\>
\<
\|
\textknit{knitting-specs}
\wideincrease{num-stitches}
\widedecrease{num-stitches}
\bobble{text%plain}
\narrowincrease{text%plain}
\narrowdecrease{text%plain}
\pnarrowincrease{text%plain}
\pnarrowdecrease{text%plain}
\purlbackground{knit-spec}
\widesymbol{knit-spec}{num-stitches}
\cableleft{knit-spec1}{knit-spec2}
\cableright{knit-spec1}{knit-spec2}
\cableforeground{knit-spec}
\cablebackground{knit-spec}
\knit{number}
\purl{number}
\Knit{text%plain}{num-stitches}
\Purl{text%plain}{num-stitches}
\knitbox{text%plain}{num-stitches}
\purlbox{text%plain}{num-stitches}
\knitboxforeground#*
\purlboxforeground#*
\knitboxbackground#*
\purlboxbackground#*

\knitgrid
\knitwide
\knitmixed
\knitnogrid

\begin{smallpage}
\end{smallpage}
\begin{fullpages}
\end{fullpages}

\overline{knit-spec}
\overline*{knit-spec}
\underline{knit-spec}
\underline*{knit-spec}

\purlpass{purl-pass-code}
\purlpass[other-code]{purl-pass-code}
\gridpass{grid-pass-code}
\gridpass[other-code]{grid-pass-code}
\mainpass{main-pass-code}
\mainpass[other-code]{main-pass-code}

\knitlinewd
\gridwidth#*
\stitchwd#*
\stitchht#*
\stitchdp#*

\ifgrid
\gridtrue#*
\gridfalse#*
\ifknitsymbol
\knitsymboltrue#*
\knitsymbolfalse#*
\ifchartsonly
\chartsonlytrue#*
\chartsonlyfalse#*

\rn
\therownumber#*
\rnleft
\rnright
\therownumberskip#*
\ifresetrn#*
\resetrntrue
\resetrnfalse
\rnoddonly
\rnevenonly
\rnnormal
\printrightrownumber{arg}#*
\printleftrownumber{arg}#*
\printrownumber{arg}#*
\rownumberwd#*
\numberrow{first-num}{countdown}{last-num}
\rnbox{number}
\rnboxleft{number}
\rnboxright{number}

\stitchcountchart{knitting-specs}
\stitchcountchart[placement%keyvals]{knitting-specs}
\countstitches{knit-spec}
\thestitchcountout
\thestitchcountin
\adjuststitchcount{num-stitches}
\adjuststitchcount[num-incount-stitches]{num-stitches}
\stitchcountwarningbar
\Knitstitchcount{arg1}{arg2}#*
\Purlstitchcount{arg1}{arg2}#*
\knitboxstitchcount{arg1}{arg2}#*
\purlboxstitchcount{arg1}{arg2}#*
\widesymbolspacer{arg1}{arg2}#*
\shortrows{knit-spec}
\nostitchcount
\knitdebug
\printleftstitchcount#*
\printrightstitchcount#*
\printstitchcountchart#*

#keyvals:\chart,\stitchcountchart
left
right
oddleft
oddright
evenleft
evenright
both
#endkeyvals

purlgray#B
knitlinecolor#B
gridcolor#B
forecolor#B
rncolor#B
rnarrowcolor#B

# not documented
\countpass{pass-code}#*
\countpass[other-code]{pass-code}#*
\knitleftarrowhead#*
\knitrightarrowhead#*
\thestitchcountinprev#*