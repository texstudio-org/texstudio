# tikz-timing package
# Matthew Bertucci updated 12/13/2021 for v0.7f

#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarybackgrounds
#include:tikzlibrarydecorations.pathmorphing
#include:environ

\texttiming{characters}
\texttiming[init char/TikZ keys]{characters}

\timing
\timing[TikZ options]

\begin{tikztimingtable}#\tabular
\end{tikztimingtable}
\extracode#/tikztimingtable
\extracode[TikZ keys]#/tikztimingtable
\endextracode#/tikztimingtable
\begin{extracode}#/tikztimingtable
\begin{extracode}[TikZ keys]#/tikztimingtable
\end{extracode}#/tikztimingtable
\tablegrid#/tikztimingtable
\tablegrid[TikZ keys]#/tikztimingtable
\tablegrid*#/tikztimingtable
\tablegrid*[TikZ keys]#/tikztimingtable
\fulltablegrid#/tikztimingtable
\fulltablegrid[TikZ keys]#/tikztimingtable
\nrows#*
\rowdist#*
\coldist#*
\twidth#*
\horlines{list}#/tikztimingtable
\horlines[TikZ keys]{list}#/tikztimingtable
\vertlines{list}#/tikztimingtable
\vertlines[TikZ keys]{list}#/tikztimingtable
\tableheader{description title%text}{signal title%text}#/tikztimingtable
\tableheader[TikZ keys]{description title%text}{signal title%text}#/tikztimingtable
\tablerules#/tikztimingtable
\tablerules[TikZ keys]#/tikztimingtable
\begin{background}#\pictureHighlight
\begin{background}[TikZ keys]
\end{background}
\background#*
\endbackground#*

\tikztimingsetwscale{math expr}#*
\setwscale{math expr}#*
\wscale#*
\xunit#*
\yunit#*
\slope#*
\lslope#*
\zslope#*
\dslope#*

\tikztimingmetachar{meta char}{char group}#*
\tikztimingmetachar{meta char}[args]{char group}#*

\usetikztiminglibrary{libraries%keyvals}
\usetikztiminglibrary[options]{libraries%keyvals}#*
\usetikztiminglibrary[options]{libraries%keyvals}[date]#*

#keyvals:\usetikztiminglibrary
arrows
either
overlays
clockarrows
columntype
nicetabs
counters
advnodes
ifsym
interval
beamer
#endkeyvals

# from columntype tikztiminglibrary
\celltiming{arg}#S
\endcelltiming#S

# from counters tikztiminglibrary
\tikztimingcounter{char}#*
\tikztimingsetcounter{char}{pgfmath expr}#*

# from ifsym tikztiminglibrary
\RaisingEdge#S
\FallingEdge#S
\ShortPulseHigh#S
\ShortPulseLow#S
\PulseHigh#S
\PulseLow#S
\LongPulseHigh#S
\LongPulseLow#S
\textifsym#S

# from advnodes tikztiminglibrary
\anchoralias{arg1}{arg2}#S
\anchorpoints#S
\anchorpoint#S
\fromchar#S
\tochar#S

# not documented
\tikztimingwidth#*
\timingwidth#*
\timingheight#*
\charc#*
\charb#*
\abc#*
\list#*
\fwidth#*
\gslope#*
\style#*
\bgstyle#*
\nstyle#*
\newdraw#*
\newdraw[TikZ options]#*
\newdrawns#*
\newdrawns[TikZ options]#*
\code{code}#*
\tikztimingsetslope{value}#*
\tikztimingsetdslope{value}#*
\tikztimingsetzslope{value}#*
\tikztiminguse{char}{code}#*
\tikztimingdef{char}{code}#*
\tikztimingcpy{char1}{char2}#*
\tikztiminglet{char1}{char2}#*
\tikztimingchar{char}{code1}{code2}#*
\tikztimingecopy{char1}{char2}#*
