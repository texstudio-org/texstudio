# mathfixs package
# Matthew Bertucci 2/3/2022 for v1.01

#include:keyval

\ProvideMathFix{options%keyvals}

#keyvals:\usepackage/mathfixs#c,\ProvideMathFix
frac
fracclass=%<class%>
fracdelimclass=%<class%>
rfrac
rfrac=%<command%>
vfrac
vfrac=%<command%>
vfracclass=%<class%>
vfracskippre=%<muskip%>
vfracskippost=%<muskip%>
root
rootclass=%<class%>
rootskipend=%<muskip%>
rootskippre=%<muskip%>
rootskippost=%<muskip%>
rootclose=##L
multskip
multskip=%<muskip%>
greekcaps
greekcaps=%<prefix%>
greeklower
greeklower=%<prefix%>
autobold
mathbold
mathbold=%<command%>
#endkeyvals

#ifOption:rfrac
\rfrac{numerator}{denominator}#m
#endif

#ifOption:vfrac
\vfrac{numerator}{denominator}#m
#endif

#ifOption:mathbold
\mathbold{text%plain}#m
#endif

\rfrac{numerator}{denominator}#*m
\vfrac{numerator}{denominator}#*
\mathbold{text%plain}#*m