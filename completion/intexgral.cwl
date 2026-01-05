# intexgral package
# Matthew Bertucci 2025/12/26 for v3.0.0

#include:amsfonts
#include:derivative

\intexgralsetup{options%keyvals}

#keyvals:\intexgralsetup,\usepackage/intexgral#c
invert-limits#true,false
invert-diff#true,false
limits-mode=#limits,nolimits
italic#true,false
upright#true,false
#endkeyvals

\integral{integrand}#m
\integral[keyvals]{integrand}#m

#keyvals:\integral#c
limits=%<list%>
limits*=%<list%>
mode=#default,nested,product
symbol=%<command%>
nint=%<integer%>
llimit=%<lower limit%>
ulimit=%<upper limit%>
single
single=%<limit%>
double
double=%<limit%>
triple
triple=%<limit%>
quadruple
quadruple=%<limit%>
contour
contour=%<limit%>
surface
surface=%<limit%>
volume
volume=%<limit%>
domain={%<*-list%>}
domain*={%<*-list%>}
boundary=%<lower limit%>
variables=%<list%>
jacobian#true,false
diff-symb=%<command%>
diff-star#true,false
diff-options={%<keyvals%>}
diff-vec#true,false
#endkeyvals

\IntegralSetup{keyvals}

#keyvals:\IntegralSetup
defaultvar=%<variables%>
defaultvar*=%<variables%>
vectorstyle=%<command%>
domainstyle=%<command%>
symbolskip=%<mu expr%>
hide-diff#true,false
#endkeyvals

\NewLimitsKeyword{keyword}{limits%formula}
\RenewLimitsKeyword{keyword}{limits%formula}
\ProvideLimitsKeyword{keyword}{limits%formula}
\DeclareLimitsKeyword{keyword}{limits%formula}
\NewVariableKeyword{keyword}{variables%formula}
\NewVariableKeyword{keyword}{variables%formula}[jacobian%formula]
\RenewVariableKeyword{keyword}{variables%formula}
\RenewVariableKeyword{keyword}{variables%formula}[jacobian%formula]
\ProvideVariableKeyword{keyword}{variables%formula}
\ProvideVariableKeyword{keyword}{variables%formula}[jacobian%formula]
\DeclareVariableKeyword{keyword}{variables%formula}
\DeclareVariableKeyword{keyword}{variables%formula}[jacobian%formula]
\NewSymbolKeyword{keyword}{symbol%formula}
\RenewSymbolKeyword{keyword}{symbol%formula}
\ProvideSymbolKeyword{keyword}{symbol%formula}
\DeclareSymbolKeyword{keyword}{symbol%formula}
\differentials
