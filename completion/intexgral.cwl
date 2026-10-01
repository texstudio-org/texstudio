# intexgral package
# Matthew Bertucci 2026/09/18 for v4.3.0

#include:amsfonts

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
limits-mode=#limits,nolimits
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
diff-vec#true,false
diff-order=%<list%>
#endkeyvals

\IntegralSetup{keyvals}

#keyvals:\IntegralSetup
diff-symb=%<command%>
defaultvar=%<variables%>
defaultvar*=%<variables%>
varsep=%<mu expr%>
diffsep=%<mu expr%>
innersymbsep=%<mu expr%>
postsymbsep=%<mu expr%>
jacobiansep=%<mu expr%>
vectorstyle=%<command%>
domainstyle=%<command%>
delim=#brackets,bar
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
\invertdiff

\differentials#m
\jacobian#m
\variables#m

\antideriv{primitive}
\antideriv[options%keyvals]{primitive}

#keyvals:\antideriv
limits=%<list%>
delim=#brackets,bar
big
Big
bigg
Bigg
auto
#endkeyvals