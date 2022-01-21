# xcolor-material package
# Matthew Bertucci 8/19/2021 for v0.1

#include:xcolor
#include:kvoptions

#keyvals:\usepackage/xcolor-material#c
prefix=%<prefix%>
#endkeyvals

\printcolorvalue{color}
\printcolorvalue[model]{color}
\colorsample{color}
\colorsample[model][textcolor%color][box width%l]{color}[title%text]
\colorpalette{color}
\colorpalette[options%keyvals]{color}

#keyvals:\colorpalette
width=##L
height=##L
shape=%<shape%>
title=#%color
title text color=#%color
init text color=#%color
altern text color=#%color
variation font=
value font=
title font=
colorbox sep=##L
first colorbox sep=##L
title colorbox height=##L
primary palette=
secondary palette=
percent char=
primary variation=
primary toggle at=
secondary toggle at=
color model=
both
primary
basic
#endkeyvals

MaterialRed#B
MaterialPink#B
MaterialPurple#B
MaterialDeepPurple#B
MaterialIndigo#B
MaterialBlue#B
MaterialLightBlue#B
MaterialCyan#B
MaterialTeal#B
MaterialGreen#B
MaterialLightGreen#B
MaterialLime#B
MaterialYellow#B
MaterialAmber#B
MaterialOrange#B
MaterialDeepOrange#B
MaterialBrown#B
MaterialGrey#B
MaterialBlueGrey#B
MaterialBlack#B
MaterialWhite#B
