# sankey package
# Matthew Bertucci 1/18/2022 for v3.0

#include:etoolbox
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydubins

\sankeyset{options%keyvals}

\begin{sankeydiagram}
\begin{sankeydiagram}[options%keyvals]
\end{sankeydiagram}

\sankeynode{node parameters%keyvals}
\sankeynode[options]{node parameters%keyvals}
\sankeynodestart{node parameters%keyvals}
\sankeynodestart[options]{node parameters%keyvals}
\sankeynodeend{node parameters%keyvals}
\sankeynodeend[options]{node parameters%keyvals}

#keyvals:\sankeynode#c,\sankeynodestart#c,\sankeynodeend#c
name=%<name%>
quantity=%<quantity%>
angle=%<degrees%>
at={%<x,y%>}
anchor=#center,left,right
as=%<name%>
forked={%<qty1/name1,qty2/name2,...%>}
fork anchor=%<node%>.%<anchor%>
#endkeyvals

#keyvals:\sankeynode#c
start#true,false
end#true,false
#endkeyvals

\sankeygetnodeqty{node name}
\sankeyqtytolen{quantity}
\sankeygetnodeorient{node name}

\sankeyadvance{node name}{distance%l}
\sankeyadvance[options%keyvals]{node name}{distance%l}
\sankeyadvance*{node name}{distance%l}
\sankeyadvance*[options%keyvals]{node name}{distance%l}

\sankeyturn{node name}{angle}
\sankeyturn[options%keyvals]{node name}{angle}
\sankeyturn*{node name}{angle}
\sankeyturn*[options%keyvals]{node name}{angle}

\sankeyturnleft{node name}{angle}
\sankeyturnleft[options%keyvals]{node name}{angle}
\sankeyturnleft*{node name}{angle}
\sankeyturnleft*[options%keyvals]{node name}{angle}

\sankeyturnleftbackward{node name}{angle}
\sankeyturnleftbackward[options%keyvals]{node name}{angle}
\sankeyturnleftbackward*{node name}{angle}
\sankeyturnleftbackward*[options%keyvals]{node name}{angle}

\sankeyturnright{node name}{angle}
\sankeyturnright[options%keyvals]{node name}{angle}
\sankeyturnright*{node name}{angle}
\sankeyturnright*[options%keyvals]{node name}{angle}

\sankeyturnrightbackward{node name}{angle}
\sankeyturnrightbackward[options%keyvals]{node name}{angle}
\sankeyturnrightbackward*{node name}{angle}
\sankeyturnrightbackward*[options%keyvals]{node name}{angle}

\sankeyoutin{nodeA}{nodeB}
\sankeyoutin[options%keyvals]{nodeA}{nodeB}

\sankeydubins{nodeA}{nodeB}
\sankeydubins[options%keyvals]{nodeA}{nodeB}

\sankeystart{node name}
\sankeystart[options%keyvals]{node name}

\sankeyend{node name}
\sankeyend[options%keyvals]{node name}

\sankeyfork{node name}{qty1/name1,qty2/name2,...}
\sankeyfork[options%keyvals]{node name}{qty1/name1,qty2/name2,...}

\sankeynodealias{orig name}{clone name}

#keyvals:\sankeyset#c
every diagram/.style={%<options%>}
debug color/.style={%<options%>}
debug line/.style={%<options%>}
debug normal/.style={%<options%>}
debug label/.style={%<options%>}
#endkeyvals

#keyvals:\sankeyset#c,\begin{sankeydiagram}#c,\sankeyadvance#c,\sankeyadvance*#c,\sankeyturn#c,\sankeyturn*#c,\sankeyturnleft#c,\sankeyturnleft*#c,\sankeyturnleftbackward#c,\sankeyturnleftbackward*#c,\sankeyturnright#c,\sankeyturnright*#c,\sankeyturnrightbackward#c,\sankeyturnrightbackward*#c,\sankeyoutin#c,\sankeydubins#c,\sankeystart#c,\sankeyend#c,\sankeyfork#c
ratio quantity=%<number%>
ratio length=##L
ratio=%<distance%>/%<number%>
rotate=%<degrees%>
minimum radius=##L
outin steps=%<integer%>
fill/.style={%<options%>}
draw/.style={%<options%>}
start style=#none,simple,arrow
end style=#none,simple,arrow
new start style={%<name%>}{%<fill path%>}{%<draw path%>}
new end style={%<name%>}{%<fill path%>}{%<draw path%>}
debug#true,false
every node/.style={%<node parameters%>}
debug color=#%color
#endkeyvals

\name#*
\qty#*
\orient#*
\pos#*
