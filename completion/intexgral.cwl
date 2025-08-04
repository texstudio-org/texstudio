# intexgral package
# Matthew Bertucci 2025/08/04 for v1.1.0

#keyvals:\usepackage/intexgral#c
invert-limits#true,false
invert-differentials#true,false
hide-differentials#true,false
italic#true,false
upright#true,false
#endkeyvals

\integral{integrand}#m
\integral[keyvals]{integrand}#m

#keyvals:\integral
limits=%<list%>
limits*=%<list%>
int-split#true,false
limits-mode=#limits,nolimits
int-symb=%<command%>
nint=%<integer%>
lower-lim=%<lower limit%>
upper-lim=%<upper limit%>
single
single=%<limit%>
single*
single*=%<limit%>
double
double=%<limit%>
double*
double*=%<limit%>
triple
triple=%<limit%>
triple*
triple*=%<limit%>
quadruple
quadruple=%<limit%>
quadruple*
quadruple*=%<limit%>
contour
contour=%<limit%>
contour*
contour*=%<limit%>
surface
surface=%<limit%>
surface*
surface*=%<limit%>
volume*
volume*=%<limit%>
volume
volume=%<limit%>
domain={%<*-list%>}
boundary=%<lower limit%>
variable=%<list%>
jacobian#true,false
diff-symb=%<command%>
diff-star#true,false
diff-options={%<keyvals%>}
diff-vec#true,false
diff-vec-style=%<command%>
#endkeyvals

\NewIntegralSymbol{csname}
\NewLimitsKeyword{keyword}{limits}
\RenewLimitsKeyword{keyword}{limits}
\ProvideLimitsKeyword{keyword}{limits}
\DeclareLimitsKeyword{keyword}{limits}
\NewDifferentialKeyword{keyword}{differentials}
\NewDifferentialKeyword{keyword}{differentials}[jacobian]
\RenewDifferentialKeyword{keyword}{differentials}
\RenewDifferentialKeyword{keyword}{differentials}[jacobian]
\ProvideDifferentialKeyword{keyword}{differentials}
\ProvideDifferentialKeyword{keyword}{differentials}[jacobian]
\DeclareDifferentialKeyword{keyword}{differentials}
\DeclareDifferentialKeyword{keyword}{differentials}[jacobian]
\differentials