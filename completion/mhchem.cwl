# mhchem package
# edited by Stefan Kraus 2013-08-12
# edited by Matthew Bertucci 2022-05-09 for v4.09

#include:l3keys2e
#include:calc
#include:amsmath
#include:chemgreek
#include:graphics
#include:ifthen
#include:keyval

#keyvals:\usepackage/mhchem#c
version=%<version%>
#endkeyvals

\mhchemoptions{options%keyvals}

#keyvals:\usepackage/mhchem#c,\mhchemoptions
textfontname=%<font csname%>
mathfontname=%<font csname%>
font=#sf
text-greek=#textgreek,upgreek,newtx,kpfonts,mathdesign,fourier,textalpha,fontspec,default,var-default
math-greek=#textgreek,upgreek,newtx,kpfonts,mathdesign,fourier,textalpha,fontspec,default,var-default
arrows=#font,pgf,pgf-filled,pgf{%<arrow type%>}{%<width%>}
layout=#stacked,staggered-deep,staggered-flat
minus-sidebearing-left=##L
minus-sidebearing-right=##L
minus-math-sidebearing-left=##L
minus-math-sidebearing-right=##L
minus-text-sidebearing-left=##L
minus-text-sidebearing-right=##L
#endkeyvals

#keyvals:\mhchemoptions
textfontcommand=%<font command%>
mathfontcommand=%<font command%>
textminus=%<symbol%>
cdot=%<symbol%>
textelectrondot=%<symbol%>
#endkeyvals

#ifOption:arrows=pgf
#include:pgf
#include:tikz
# loads arrows.meta tikzlibrary
#endif

#ifOption:arrows=pgf-filled
#include:pgf
#include:tikz
# loads arrows.meta tikzlibrary
#endif

\ce{formula}

#\bond{-=#}
#argument of bond here suggests the three most common types of bonds

\bond{%<-=~.<> etc.%>}
# previous line \bond{-=#} did not work since # makes a comment

\cesplit{search-and-replace list}{string}

# deprecated commands
\hyphen#S
#ifOption:version=1
\cee{equation}
\cf{arg}
\cf[opt]{arg}
\cmath{arg}
\sbond
\dbond
\tbond
#endif
#ifOption:version=2
\cee{equation}
\cf{arg}
\cf[opt]{arg}
\cmath{arg}
\sbond
\dbond
\tbond
#endif
#ifOption:version=3
\cee{equation}
\cf{arg}
\cf[opt]{arg}
\cmath{arg}
\sbond
\dbond
\tbond
#endif
#cmath was removed from mhchem: "2006-12-17 v3.05, mhchem fixed: changed: $...$ replaces \cmath{...}", kept for backward compatibility. /Stefan Kraus 2013-08-12
