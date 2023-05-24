# quantikz2 tikzlibrary
# 2023/05/24 for v1.0.1

#include:xargs
#include:ifthen
#include:xstring
#include:etoolbox
#include:mathtools
#include:pgfmath
#include:environ
#include:tikzlibrarycd
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibraryshapes.symbols
#include:tikzlibraryshapes.misc
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.markings
#include:tikzlibrarymath

\begin{quantikz}#\math,array
\begin{quantikz}[options%keyvals]#\math,array
\end{quantikz}

#keyvals:\begin{quantikz}#c
wire types={%<list%>}
thin lines
transparent
classical gap=##L
align equals at=%<n%>
slice all
remove end slices=%<n%>
slice titles=%<text%>
slice style={%<TikZ keys%>}
slice label style={%<TikZ keys%>}
vertical slice labels
# useful options inherited from tikz and tikzcd
column sep=##L
row sep=##L
between origins
color=#%color
#endkeyvals

\col#*

\setwiretype{type}
\setwiretype[n]{type}
\wire{type}
\wire[dir]{type}
\wire[dir][n]{type}
\wire[dir][n][TikZ keys]{type}
\wireoverride{type}

\qwbundle{label text}
\qwbundle[options%keyvals]{label text}

#keyvals:\qwbundle#c
style={%<TikZ keys%>}
Strike Height=##L
Strike Width=##L
#endkeyvals

\permute{list}
\linethrough
\push{label text}
\phantomgate{label text}
\hphantomgate{label text}

\phase{label text}
\phase[options%keyvals]{label text}

#keyvals:\phase#c
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
#endkeyvals

\lstick{label text}
\lstick[options%keyvals]{label text}
\midstick{label text}
\midstick[options%keyvals]{label text}
\rstick{label text}
\rstick[options%keyvals]{label text}

#keyvals:\lstick#c,\midstick#c,\rstick#c
%<n%>
wires=%<n%>
label style={%<TikZ keys%>}
brackets=#none,left,right,both
braces=
#endkeyvals

\gate{label text}
\gate[options%keyvals]{label text}
\gate[options%keyvals][min width]{label text}
\gate[options%keyvals][min width][min height]{label text}

#keyvals:\gate#c
%<n%>
wires=%<n%>
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
disable auto height
swap
#endkeyvals

\gateinput{label text}
\gateinput[options%keyvals]{label text}
\gateoutput{label text}
\gateoutput[options%keyvals]{label text}

#keyvals:\gateinput#c,\gateoutput#c
%<n%>
wires=%<n%>
label style={%<TikZ keys%>}
braces=
#endkeyvals

\meter{label text}
\meter[options%keyvals]{label text}
\meter[options%keyvals][min width]{label text}
\meter[options%keyvals][min width][min height]{label text}
\metercw{label text}
\metercw[options%keyvals]{label text}
\metercw[options%keyvals][min width]{label text}
\metercw[options%keyvals][min width][min height]{label text}

#keyvals:\meter#c,\metercw#c
%<n%>
wires=%<n%>
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
disable auto height
#endkeyvals

\measure{label text}
\measure[TikZ keys]{label text}
\measuretab{label text}
\measuretab[TikZ keys]{label text}
\meterD{label text}
\meterD[TikZ keys]{label text}
\inputD{label text}
\inputD[TikZ keys]{label text}

\swap{n}
\swap[options%keyvals]{n}

#keyvals:\swap#c
partial swap=%<text%>
partial position=%<factor%>
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
vertical wire=#q,c,b
#endkeyvals

\ctrl{n}
\ctrl[options%keyvals]{n}
\octrl{n}
\octrl[options%keyvals]{n}

#keyvals:\ctrl#c,\octrl#c
style={%<TikZ keys%>}
wire style={%<TikZ keys%>}
vertical wire=#q,c,b
#endkeyvals

#keyvals:\ctrl#c
open
#endkeyvals

\control{}
\control[options%keyvals]{}
\ocontrol{}
\ocontrol[options%keyvals]{}

#keyvals:\control#c,\ocontrol#c
style={%<TikZ keys%>}
#endkeyvals

#keyvals:\control#c
open
#endkeyvals

\targ{}
\targ[options%keyvals]{}
\targX{}
\targX[options%keyvals]{}

#keyvals:\targ#c,\targX#c
style={%<TikZ keys%>}
#endkeyvals

\gategroup{label text}
\gategroup[options%keyvals]{label text}

#keyvals:\gategroup#c
%<n%>
wires=%<n%>
steps=%<m%>
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
background
#endkeyvals

\slice{label text}
\slice[options%keyvals]{label text}

#keyvals:\slice#c
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
#endkeyvals

\makeebit{label text}
\makeebit[options%keyvals]{label text}

#keyvals:\makeebit#c
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
angle=%<degrees%>
#endkeyvals

\trash{label text}
\trash[TikZ keys]{label text}
\ground{label text}
\ground[TikZ keys]{label text}
\wave
\wave[TikZ keys]
\verticaltext{label text}

\ket{arg%formula}
\bra{arg%formula}
\proj{arg%formula}
\braket{arg1%formula}{arg2%formula}
\forceredefine#*

\ghost{label text}
\ghost[min width]{label text}
\ghost[min width][min height]{label text}

\pgfdeclareanchoralias{arg1}{arg2}{arg3}#*
\pgfaddtoshape{arg1}{arg2}#*

# not documented
\DivideRowsCols#S
\expandedwire{arg1}{arg2}{arg3}{arg4}#S
\fullwire{arg1}{arg2}{arg3}{arg4}#S
\ifcsstringeitheror{arg1}{arg2}{arg3}{arg4}#S
\ifnodedefined{arg1}{arg2}{arg3}#S
\importwiretypes{arg}#S
\maketransparent#S
\resetstyles#S
\resetwiretypes#S
\setmiddle{arg}#S
\sliceallr#S
\sliceallvr#S
\vqwexplicit{arg1}{arg2}#S

# deprecated
\cw#S
\cwbend{arg}#S
\qw#S
\vcw{arg}#S
\vqw{arg}#S
