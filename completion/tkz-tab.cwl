# tkz-tab package
# Matthew Bertucci 9/17/2021 for v2.12c

#include:tikz

\tkzTabInit{expr1/height1,expr2/height2,...}{expr1,expr2,...}
\tkzTabInit[options%keyvals]{expr1/height1,expr2/height2,...}{expr1,expr2,...}

\tkzTab{list1}{list2}{list3}{list4}
\tkzTab[options%keyvals]{list1}{list2}{list3}{list4}

#keyvals:\tkzTabInit#c,\tkzTab#c
espcl=
lgt=
deltacl=
lw=##L
nocadre
color
colorC=#%color
colorL=#%color
colorT=#%color
colorV=#%color
help
#endkeyvals

\tkzTabLine{symbol1,symbol2,...}

\tkzTabVar{symbol1/expr,symbol2/expr1/expr2,...}
\tkzTabVar[options%keyvals]{symbol1/expr,symbol2/expr1/expr2,...}

#keyvals:\tkzTabVar#c
color=#%color
help
#endkeyvals

\tkzTabVal{start}{finish}{position}{antecedent}{image}
\tkzTabVal[options%keyvals]{start}{finish}{position}{antecedent}{image}
\tkzTabIma{start}{finish}{position}{antecedent}{image}
\tkzTabIma[options%keyvals]{start}{finish}{position}{antecedent}{image}
\tkzTabImaFrom{start}{finish}{antecedent}{image}
\tkzTabImaFrom[options%keyvals]{start}{finish}{antecedent}{image}

#keyvals:\tkzTabVal#c,\tkzTabIma#c,\tkzTabImaFrom#c
draw#true,false
remember=
#endkeyvals

\tkzTabTan{start}{finish}{antecedent}{image}
\tkzTabTan[options%keyvals]{start}{finish}{antecedent}{image}
\tkzTabTanFrom{start}{finish}{antecedent}{image}
\tkzTabTanFrom[options%keyvals]{start}{finish}{antecedent}{image}

#keyvals:\tkzTabTan#c,\tkzTabTanFrom#c
pos=
#endkeyvals

\tkzTabSlope{num1/leftexpr1/rightexpr1,num2/leftexpr2/rightexpr3,...}

\tkzTabSetup[options%keyvals]

#keyvals:\tkzTabSetup#c
doubledistance=##L
doublecolor=#%color
lw=##L
color=#%color
tstyle=
tcolor=#%color
tanarrowstyle=
tanstyle=
tancolor=#%color
tanwidth=##L
fromarrowstyle=
fromstyle=
fromcolor=#%color
fromwidth=##L
hcolor=#%color
hopacity=
crosslines
arrowcolor=#%color
arrowstyle=
arrowlinewidth=##L
#endkeyvals

\tkzTabColors[options%keyvals]

#keyvals:\tkzTabColors#c
color=#%color
backgroundcolor=#%color
#endkeyvals
