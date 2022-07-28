# texdraw package
# Matthew Bertucci 2022/07/27 for v2019-04-18

#include:graphics

\begin{texdraw}#\pictureHighlight
\end{texdraw}

\centertexdraw{TeXdraw commands}
\everytexdraw{TeXdraw commands}

\drawdim %<dim%>
\move (x y)
\lvec (x y)
\avec (x y)
\rmove (dx dy)
\rlvec (dx dy)
\ravec (dx dy)
\linewd %<width%>
\lpatt (pattern)
\setgray %<level%>
\arrowheadtype t:%<type%>
\arrowheadsize l:%<length%> w:%<width%>
\htext (x y){text}
\htext{text}
\vtext (x y){text}
\vtext{text}
\rtext td:%<angle%> (x y){text}
\rtext td:%<angle%> {text}
\textref h:%<h-ref%> v:%<v-ref%>
\lcir r:%<radius%>
\fcir f:%<level%> r:%<radius%>
\lellip rx:%<x-radius%> ry:%<y-radius%>
\fellip f:%<level%> rx:%<x-radius%> ry:%<y-radius%>
\larc r:%<radius%> sd:%<start-angle%> ed:%<end-angle%>
\clvec (x1 y1)(x2 y2)(x3 y3)
\lfill f:%<level%>
\ifill f:%<level%>
\bsegment
\esegment
\savecurrpos (*%<px%> *%<py%>)
\savepos (%<x y%>)(*%<px%> *%<py%>)
\setunitscale %<scale%>
\relunitscale %<value%>
\setsegscale %<scale%>
\relsegscale %<value%>
\drawbb
\writeps{ps-commands}
\getpos (%<x y%>)%<\mx\my%>
\realmult {%<value1%>}{%<value2%>}%<\prod%>
\realmult{value1}{value2}{cmd}#Sd

# for plaintex
\btexdraw#S
\etexdraw#S

# not documented
\TeXdrawId#S
\coordtopix {dimen}{pixels}#*
\getsympos (%<x y%>)%<\mx\my%>#*
\intdiv{numerator}{denominator}{macro%cmd}#*d
\listtopix (list){macro%cmd}#*d
\pixtobp{pixels}{macro%cmd}#*d
\pixtocoord{pixels}{macro%cmd}#*d
\pixtodim{pixels}{dimen}#*
\rottxt{arg1}{arg2}
\setRevDate#S
\sppix %<num%>/%<unit%>
\writetx{ps-commands}#*