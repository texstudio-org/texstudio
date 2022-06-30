# draftwatermark package
# Matthew Bertucci 11/2/2021 for v3.0

#include:kvoptions
#include:graphicx
#include:color

\DraftwatermarkOptions{options%keyvals}

#keyvals:\DraftwatermarkOptions,\usepackage/draftwatermark#c
firstpageonly#true,false
firstpage
stamp#true,false
nostamp
final
angle=%<degrees%>
scale=%<factor%>
fontsize=##L
text=%<text%>
hpos=##L
vpos=##L
pos={%<hpos,vpos%>}
hanchor=#l,c,r
vanchor=#t,m,b
anchor=%<string%>
alignment=#l,c,r
colormodel=%<color model%>
colorspec=%<color spec%>
color=%<color%>
color={[%<model%>]{%<spec%>}}
markcmd=%<macro%>
#endkeyvals

\DraftwatermarkStdMark

## legacy interface
\SetWatermarkAngle{degrees}#S
\SetWatermarkFontSize{length}#S
\SetWatermarkScale{factor}#S
\SetWatermarkHorCenter{length}#S
\SetWatermarkVerCenter{length}#S
\SetWatermarkText{text}#S
\SetWatermarkColor{colorspec}#S
\SetWatermarkLightness{real}#S
