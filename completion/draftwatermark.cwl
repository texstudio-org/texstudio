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
scale=
fontsize=##L
text=
hpos=##L
vpos=##L
pos={%<hpos,vpos%>}
hanchor=#l,c,r
vanchor=#t,m,b
anchor=%<string%>
alignment=#l,c,r
colormodel=
colorspec=
color=
markcmd=%<macro%>
#endkeyvals

\DraftwatermarkStdMark
