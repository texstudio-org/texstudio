# luaplot package
# Matthew Bertucci 2023/07/04 for v1.0

#include:xkeyval
#include:luacode
#include:tikz
#include:luamplib

\luaplot{function%definition}
\luaplot[options%keyvals]{function%definition}

#keyvals:\luaplot
xmin=%<number%>
xmax=%<number%>
ymin=%<number%>
ymax=%<number%>
plotpts=%<integer%>
hor=##L
ver=##L
clr={'%<color1,color2,...%>'}
plotsty={'%<style1,style2,...%>'}
plotoptions={%<MetaPost code%>}
#endkeyvals

\luatikzpath{function%definition}{xmin}{xmax}{plot points}