# pxpic package
# Matthew Bertucci 11/2/2021 for v1.2

#include:xcolor
#include:expkv

\pxpic{pixel list}
\pxpic[options%keyvals]{pixel list}
\pxpicsetup{options%keyvals}

#keyvals:\pxpic,\pxpicsetup
colors=%<color list%>
colours=%<color list%>
color-list=%<choice%>
colour-list=%<choice%>
gap-hack=##L
ht=##L
mode=#px,named,rgb,cmy,cmyk,hsb,Hsb,tHsb,gray,RGB,HTML,HSB,Gray,wave
size=##L
skip=##L
wd=##L
#endkeyvals

\pxpicnewmode{name}{definition}#*
\pxpicsetmode{name}{definition}#*
\pxpicnewcolorlist{name}{color list}#*
\pxpicsetcolorlist{name}{color list}#*
\pxpicaddcolorlist{name}{color list}#*
\pxpicforget{px}#*

\px
\pxskip

\pxpicHT#*
\pxpicWD#*
\pxpiclogo#*
\pxpiclogo[size]#*