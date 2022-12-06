# tkz-tab package
# Matthew Bertucci 9/17/2021 for v2.12c

#include:ifthen
#include:xkeyval
#include:tikz
#include:tikzlibrarypatterns

\tkzTabInit{expr1/height1,expr2/height2,...}{expr1,expr2,...}
\tkzTabInit[options%keyvals]{expr1/height1,expr2/height2,...}{expr1,expr2,...}

\tkzTab{list1}{list2}{list3%formula}{list4}
\tkzTab[options%keyvals]{list1}{list2}{list3%formula}{list4}

#keyvals:\tkzTabInit,\tkzTab
color#true,false
colorC=#%color
colorL=#%color
colorT=#%color
colorV=#%color
deltacl=%<number%>
espcl=%<number%>
help#true,false
lgt=%<number%>
lw=##L
nocadre#true,false
textw=
#endkeyvals

\tkzTabLine{symbol1,symbol2,...%formula}
\tkzTabLine[options%keyvals]{symbol1,symbol2,...%formula}

#keyvals:\tkzTabLine
help#true,false
#endkeyvals

\tkzTabVar{symbol1/expr,symbol2/expr1/expr2,...}
\tkzTabVar[options%keyvals]{symbol1/expr,symbol2/expr1/expr2,...}

#keyvals:\tkzTabVar
color=#%color
help#true,false
#endkeyvals

\tkzTabVal{start}{finish}{position}{antecedent}{image}
\tkzTabVal[options%keyvals]{start}{finish}{position}{antecedent}{image}
\tkzTabIma{start}{finish}{position}{antecedent}{image}
\tkzTabIma[options%keyvals]{start}{finish}{position}{antecedent}{image}
\tkzTabImaFrom{start}{finish}{antecedent}{image}
\tkzTabImaFrom[options%keyvals]{start}{finish}{antecedent}{image}

#keyvals:\tkzTabVal,\tkzTabIma,\tkzTabImaFrom
draw#true,false
remember=%<name%>
#endkeyvals

\tkzTabTan{start}{finish}{antecedent}{image}
\tkzTabTan[options%keyvals]{start}{finish}{antecedent}{image}
\tkzTabTanFrom{start}{finish}{antecedent}{image}
\tkzTabTanFrom[options%keyvals]{start}{finish}{antecedent}{image}

#keyvals:\tkzTabTan,\tkzTabTanFrom
color=#%color
draw#true,false
pos
pos=%<position%>
remember=%<name%>
#endkeyvals

\tkzTabSlope{num1/leftexpr1/rightexpr1,num2/leftexpr2/rightexpr3,...}

\tkzTabSetup
\tkzTabSetup[options%keyvals]

#keyvals:\tkzTabSetup
arrowcolor=#%color
arrowlinewidth=##L
arrowstyle={%<TikZ keys%>}
backgroundcolor=#%color
color=#%color
crosslines#true,false
doublecolor=#%color
doubledistance=##L
fromarrowstyle={%<TikZ keys%>}
fromcolor=#%color
fromstyle={%<TikZ keys%>}
fromwidth=##L
hcolor=#%color
hopacity=%<factor%>
lw=##L
patterncolor=#%color
patternstyle={%<TikZ keys%>}
tanarrowstyle={%<TikZ keys%>}
tancolor=#%color
tanstyle={%<TikZ keys%>}
tanwidth=##L
tcolor=#%color
tstyle={%<TikZ keys%>}
twidth=##L
#endkeyvals

\tkzTabColors[options%keyvals]

#keyvals:\tkzTabColors
color=#%color
backgroundcolor=#%color
#endkeyvals

\ecartcl#S
\stripspaces{arg}#*
\tkzDrawArrow#*
\tkzTabDefaultArrowStyle#*
\tkzTabDefaultBackgroundColor#*
\tkzTabDefaultLineWidth#*
\tkzTabDefaultSep#*
\tkzTabDefaultWritingColor#*
