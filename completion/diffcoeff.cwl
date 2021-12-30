# diffcoeff package
# Matthew Bertucci 12/28/2021 for v4.0

#include:expl3
#include:xparse
#include:l3keys2e
#include:xtemplate

#keyvals:\usepackage/diffcoeff#c
ISO
spaced
def-file=%<file name%>
#endkeyvals

\diff{arg}{var}#m
\diff[ord]{arg}{var}#m
\diff{arg}{var}[subscript]^{supscript}#m
\diff[ord]{arg}{var}[subscript]^{supscript}#*m
\diff{arg}/{var}#*m
\diff[ord]{arg}/{var}#*m
\diff[ord]{arg}/{var}[subscript]^{supscript}#*m
\diff*{arg}{var}#m
\diff*[ord]{arg}{var}#m
\diff*{arg}{var}[subscript]^{supscript}#m
\diff*[ord]{arg}{var}[subscript]^{supscript}#*m
\diff*{arg}/{var}#*m
\diff*[ord]{arg}/{var}#*m
\diff*{arg}/{var}[subscript]^{supscript}#*m
\diff*[ord]{arg}/{var}[subscript]^{supscript}#*m
\diff!{arg}{var}#m
\diff[ord]!{arg}{var}#m
\diff!{arg}{var}[subscript]^{supscript}#m
\diff[ord]!{arg}{var}[subscript]^{supscript}#*m
\diff!{arg}/{var}#*m
\diff[ord]!{arg}/{var}#*m
\diff!{arg}/{var}[subscript]^{supscript}#*m
\diff[ord]!{arg}/{var}[subscript]^{supscript}#*m

\diffp{arg}{var}#m
\diffp[ord]{arg}{var}#m
\diffp{arg}{var}[subscript]^{supscript}#m
\diffp[ord]{arg}{var}[subscript]^{supscript}#*m
\diffp{arg}/{var}#*m
\diffp[ord]{arg}/{var}#*m
\diffp[ord]{arg}/{var}[subscript]^{supscript}#*m
\diffp*{arg}{var}#m
\diffp*[ord]{arg}{var}#m
\diffp*{arg}{var}[subscript]^{supscript}#m
\diffp*[ord]{arg}{var}[subscript]^{supscript}#*m
\diffp*{arg}/{var}#*m
\diffp*[ord]{arg}/{var}#*m
\diffp*{arg}/{var}[subscript]^{supscript}#*m
\diffp*[ord]{arg}/{var}[subscript]^{supscript}#*m
\diffp!{arg}{var}#m
\diffp[ord]!{arg}{var}#m
\diffp!{arg}{var}[subscript]^{supscript}#m
\diffp[ord]!{arg}{var}[subscript]^{supscript}#*m
\diffp!{arg}/{var}#*m
\diffp[ord]!{arg}/{var}#*m
\diffp!{arg}/{var}[subscript]^{supscript}#*m
\diffp[ord]!{arg}/{var}[subscript]^{supscript}#*m

\jacob{arg1,arg2,...}{var1,var2,...}#m

\diffdef{name}{options%keyvals}

#keyvals:\diffdef
op-symbol=%<symbol%>
op-symbol-alt=%<symbol%>
op-order-sep=##L
derivand-sep=##L
/-derivand-sep=##L
*-derivand-sep=##L
*/-derivand-sep=##L
*-op-left#true,false
*-italic-nudge=##L
*/-op-wrap#true,false
long-var-wrap=#dv,d(v),(dv)
denom-term-sep=##L
/-denom-term-sep=##L
term-sep-adjust=##L
left-delim=%<delim%>
right-delim=%<delim%>
elbowroom=##L
subscr-nudge=##L
/-left-delim=%<delim%>
/-right-delim=%<delim%>
/-elbowroom=##L
/-subscr-nudge=##L
#endkeyvals

\dl{arg}#m
\dl%<<digit>%>{%<arg%>}#m
\dlp{arg}#m
\dlp%<<digit>%>{%<arg%>}#m

\negmu#*m
\nilmu#*m
\onemu#*m
\twomu#*m
