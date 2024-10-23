# mathfixs package
# Matthew Bertucci 2024/10/23 for v1.1

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
genop
sgn
sgn=%<command%>
res
res=%<command%>
lcm
lcm=%<command%>
diag
diag=%<command%>
span
span=%<command%>
spec
spec=%<command%>
const
const=%<command%>
id
id=%<command%>
tr
tr=%<command%>
reim
reim=%<<command1><command2>%>
trig
hyp
mapchar
mapchar=%<command%>
mapclass
vecdiff
vecrot
econst
econst=%<command%>
econst*
econst*=%<command%>
econstclass=%<command%>
iunit
iunit=%<command%>
iunit*
iunit*=%<command%>
iunit*nb
iunit*nb=%<command%>
piconst
piconst=%<command%>
piconst*
piconst*=%<command%>
der
der=%<command%>
der*
der*=%<command%>
diff
diff=%<command%>
diff*
diff*=%<command%>
order
order=%<command%>
Order
Order=%<command%>
Order*
Order*=%<command%>
defeq
defeq=%<command%>
eqdef
eqdef=%<command%>
lapl
lapl=%<command%>
numset
numset=%<command%>
numsetfont=%<command%>
numsets
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

#ifOption:genop
\sgn#m
\res#m
\lcm#m
\diag#m
\Span#m
\spec#m
\const#m
#endif

#ifOption:sgn
\sgn#m
#endif

#ifOption:res
\res#m
#endif

#ifOption:lcm
\lcm#m
#endif

#ifOption:diag
\diag#m
#endif

#ifOption:span
\Span#m
#endif

#ifOption:spec
\spec#m
#endif

#ifOption:const
\const#m
#endif

#ifOption:id
\id#m
#endif

#ifOption:tr
\tr#m
#endif

#ifOption:trig
\arccot#m
\arcsec#m
\arccsc#m
#endif

#ifOption:hyp
\sech#m
\csch#m
\arsinh#m
\arcosh#m
\artanh#m
\arcoth#m
\arsech#m
\arcsch#m
#endif

#ifOption:mapchar
\dom#m
\supp#m
\codom#m
\im#m
\rank#m
\coker#m
#endif

#ifOption:mapclass
\Hom#m
\Eng#m
\Isom#m
\Aut#m
#endif

#ifOption:vecdiff
\grad#m
\div#m
\curl#m
#endif

#ifOption:vecrot
\curl#m
#endif

#ifOption:econst
\econst#m
#endif
#ifOption:econst*
\econst#m
#endif

#ifOption:iunit
\iunit#m
#endif
#ifOption:iunit*
\iunit#m
#endif
#ifOption:iunit*nb
\iunit#m
#endif

#ifOption:piconst
\piconst#m
#endif
#ifOption:piconst*
\piconst#m
#endif

#ifOption:der
\der#m
#endif
#ifOption:der*
\der#m
#endif

#ifOption:diff
\diff#m
#endif
#ifOption:diff*
\diff#m
#endif

#ifOption:order
\order#m
#endif

#ifOption:Order
\Order#m
#endif
#ifOption:Order*
\Order#m
#endif

#ifOption:defeq
\defeq#m
#endif

#ifOption:eqdef
\eqdef#m
#endif

#ifOption:lapl
\lapl#m
#endif

#ifOption:numset
\numset{letter}#m
#endif

#ifOption:numsets
\Integer#m
\Rational#m
\Real#m
\Complex#m
\Quaternion#m
\Natural#m
\Octonion#m
#endif

\rfrac{numerator}{denominator}#*m
\vfrac{numerator}{denominator}#*
\mathbold{text%plain}#*m
\sgn#*m
\res#*m
\lcm#*m
\diag#*m
\Span#*m
\spec#*m
\const#*m
\id#*m
\tr#*m
\arccot#*m
\arcsec#*m
\arccsc#*m
\sech#*m
\csch#*m
\arsinh#*m
\arcosh#*m
\artanh#*m
\arcoth#*m
\arsech#*m
\arcsch#*m
\dom#*m
\supp#*m
\codom#*m
\im#*m
\rank#*m
\coker#*m
\Hom#*m
\Eng#*m
\Isom#*m
\Aut#*m
\grad#*m
\div#*m
\curl#*m
\econst#*m
\iunit#*m
\piconst#*m
\der#*m
\diff#*m
\order#*m
\Order#*m
\defeq#*m
\eqdef#*m
\lapl#*m
\numset{letter}#*m
\Integer#*m
\Rational#*m
\Real#*m
\Complex#*m
\Quaternion#*m
\Natural#*m
\Octonion#*m
