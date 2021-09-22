# diffcoeff package
# Matthew Bertucci 9/21/2021 for v3.2

#include:expl3
#include:xparse
#include:l3keys2e
#include:xtemplate

\diff{arg}{var}#m
\diff[ord]{arg}{var}#m
\diff[ord]{arg}{var}[subscript]^{supscript}#*m
\diff*{arg}{var}#m
\diff*[ord]{arg}{var}#m
\diff*[ord]{arg}{var}[subscript]^{supscript}#*m

\diffp{arg}{var}#m
\diffp[ord]{arg}{var}#m
\diffp[ord]{arg}{var}[subscript]^{supscript}#*m
\diffp*{arg}{var}#m
\diffp*[ord]{arg}{var}#m
\diffp*[ord]{arg}{var}[subscript]^{supscript}#*m

\jacob{arg1,arg2,...}{var1,var2,...}#m

\diffdef{name}{options%keyvals}

#keyvals:\diffdef
op-symbol=
op-symbol-alt=
op-order-sep=##L
*-op-left#true,false
*-italic-nudge=##L
*/-op-wrap#true,false
long-var-wrap=
denom-term-sep=##L
/-denom-term-sep=##L
term-sep-adjust=##L
left-delim=
right-delim=
elbowroom=##L
subscr-nudge=##L
/-left-delim=
/-right-delim=
/-elbowroom=##L
/-subscr-nudge=##L
#endkeyvals

\dl{arg}#m

\negmu#*m
\nilmu#*m
\onemu#*m
\twomu#*m
