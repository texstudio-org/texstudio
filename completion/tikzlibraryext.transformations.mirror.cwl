# ext.transformations.mirror tikzlibrary
# 2022/12/09 for v0.4.2

# loads ext.transformations.mirror pgflibrary

#keyvals:\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
xmirror
xmirror=%<val or coord%>
ymirror
ymirror=%<val or coord%>
mirror x
mirror x=%<coord%>
mirror y
mirror y=%<coord%>
mirror=%<⟨pointA⟩%>--%<⟨pointB⟩%> 
xMirror
xMirror=%<val or coord%>
yMirror
yMirror=%<val or coord%>
Mirror x
Mirror x=%<coord%>
Mirror y
Mirror y=%<coord%>
Mirror=%<⟨pointA⟩%>--%<⟨pointB⟩%> 
#endkeyvals

# from ext.transformations.mirror pgflibrary
\pgftransformxmirror{value}#*
\pgftransformymirror{value}#*
\pgftransformmirror{pointA}{pointB}#*
\pgfqtransformmirror{point}#*
\pgftransformxMirror{value}#*
\pgftransformyMirror{value}#*
\pgftransformMirror{pointA}{pointB}#*
\pgfqtransformMirror{point}#*