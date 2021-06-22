# tkz-tab package
# Matthew Bertucci 6/21/2021

#include:tikz

\tkzTabInit[local options%keyvals]{expr1/height1,expr2/height2,...}{expr1,expr2,...}

\tkzTab[local options%keyvals]{list1}{list2}{list3}{list4}

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

\tkzTabLine[local options]{symbol1,symbol2,...}

\tkzTabVar[local options%keyvals]{symbol1/expr,symbol2/expr1/expr2,...}

#keyvals:\tkzTabVar#c
color=#%color
help
#endkeyvals

\tkzTabVal[local options%keyvals]{start}{finish}{position}{antecedent}{image}
\tkzTabIma[local options%keyvals]{start}{finish}{position}{antecedent}{image}
\tkzTabImaFrom[local options%keyvals]{start}{finish}{antecedent}{image}

#keyvals:\tkzTabVal#c,\tkzTabIma#c,\tkzTabImaFrom#c
draw#true,false
remember=
#endkeyvals

\tkzTabTan[local options%keyvals]{start}{finish}{antecedent}{image}
\tkzTabTanFrom[local options%keyvals]{start}{finish}{antecedent}{image}

#keyvals:\tkzTabTan#c,\tkzTabTanFrom#c
pos=
#endkeyvals

\tkzTabSlope{num1/leftexpr1/rightexpr1,num2/leftexpr2/rightexpr3,...}

\tkzTabSetup[local options%keyvals]

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

\tkzTabColors[local options%keyvals]

#keyvals:\tkzTabColors#c
color=#%color
backgroundcolor=#%color
#endkeyvals