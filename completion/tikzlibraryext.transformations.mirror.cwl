# ext.transformations.mirror tikzlibrary
# 2025/03/19 for v0.6

# loads ext.transformations.mirror pgflibrary

#keyvals:\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
ext/xmirror
ext/xmirror=%<val or coord%>
ext/ymirror
ext/ymirror=%<val or coord%>
ext/mirror x
ext/mirror x=%<coord%>
ext/mirror y
ext/mirror y=%<coord%>
ext/mirror=%<⟨pointA⟩%>--%<⟨pointB⟩%> 
ext/xMirror
ext/xMirror=%<val or coord%>
ext/yMirror
ext/yMirror=%<val or coord%>
ext/Mirror x
ext/Mirror x=%<coord%>
ext/Mirror y
ext/Mirror y=%<coord%>
ext/Mirror=%<⟨pointA⟩%>--%<⟨pointB⟩%> 
#endkeyvals

# from ext.transformations.mirror pgflibrary
\pgfexttransformxmirror{value}#*
\pgfexttransformymirror{value}#*
\pgfexttransformmirror{pointA}{pointB}#*
\pgfextqtransformmirror{point}#*
\pgfexttransformxMirror{value}#*
\pgfexttransformyMirror{value}#*
\pgfexttransformMirror{pointA}{pointB}#*
\pgfextqtransformMirror{point}#*

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
