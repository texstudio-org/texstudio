# ifpxltex package
# ponte-vecchio 2023-01-17 for v0.0012

#include:hologo

\pxlThisTeX
\pxlThisTeX[%<engine%>%keyvals]
\pxlThisLaTeX
\pxlThisPLaTeX

\IfpxlTeX{%<engine%>%keyvals}{%<true%>}{%<false%>}
\IfpxlTeX*[%<T/F%>]{%<engine%>%keyvals}{%<code%>}#*
\IfpxlTeXpxl{%<pdftex cmd%>}{%<xetex cmd%>}{%<luatex cmd%>}
\IfpxlTeXpxl*{%<engine%>%keyvals}{%<engine%>%keyvals}{%<engine 1 cmd%>}{%<engine 2 cmd%>}#*
\pxlRequireTeX{%<engine%>%keyvals}

#keyvals:\pxlThisTeX#c
eTeX
LaTeX
LuaLaTeX
LuaTeX
pdfLaTeX
pdfTeX
PLaTeX
pTeX
TeX
XeLaTeX
XeTeX
#endkeyvals

#keyvals:\IfpxlTeX#c,\IfpxlTeXpxl*#c,\pxlRequireTeX#c
p
x
l
#endkeyvals

