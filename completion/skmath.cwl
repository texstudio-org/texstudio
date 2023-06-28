# skmath package
# Matthew Bertucci 1/25/2022 for v0.5a

#include:l3keys2e
#include:amssymb
#include:mathtools
#include:xfrac
#include:isomath

#keyvals:\usepackage/skmath#c
commonsets#true,false
notation=#iso,english,german,legacy
#endkeyvals

#ifOption:commonsets
\N
\Z
\Q
\R
\C
#endif
#ifOption:commonsets=true
\N
\Z
\Q
\R
\C
#endif

\ii
\jj
\ee

\norm{expr}#m
\abs{expr}#m
\d{var%formula}
\pd{func%formula}{var1,var2,...%formula}
\pd*{func%formula}{var1,var2,...%formula}
\td{func%formula}{var1,var2,...%formula}
\E{expr%formula}
\P{%<<expr1>%>\given%<<expr2>%>}
\P{formula}#S
\given#S
\var{expr%formula}
\cov{expr1%formula}{expr2%formula}

\sin{expr%formula}
\sin[power%formula]{expr%formula}
\arcsin{expr%formula}
\arcsin[power%formula]{expr%formula}
\cos{expr%formula}
\cos[power%formula]{expr%formula}
\arccos{expr%formula}
\arccos[power%formula]{expr%formula}
\tan{expr%formula}
\tan[power%formula]{expr%formula}
\arctan{expr%formula}
\arctan[power%formula]{expr%formula}
\cot{expr%formula}
\cot[power%formula]{expr%formula}
\sinh{expr%formula}
\sinh[power%formula]{expr%formula}
\cosh{expr%formula}
\cosh[power%formula]{expr%formula}
\tanh{expr%formula}
\tanh[power%formula]{expr%formula}

\ln{expr%formula}
\log{expr%formula}
\log[base%formula]{expr%formula}
\exp{expr%formula}
\exp*{expr%formula}

\min{expr%formula}
\min[domain%formula]{expr%formula}
\min*{expr%formula}
\min*[domain%formula]{expr%formula}
\argmin{expr%formula}
\argmin[domain%formula]{expr%formula}
\argmin*{expr%formula}
\argmin*[domain%formula]{expr%formula}
\max{expr%formula}
\max[domain%formula]{expr%formula}
\max*{expr%formula}
\max*[domain%formula]{expr%formula}
\argmax{expr%formula}
\argmax[domain%formula]{expr%formula}
\argmax*{expr%formula}
\argmax*[domain%formula]{expr%formula}
\sup{expr%formula}
\sup[domain%formula]{expr%formula}
\sup*{expr%formula}
\sup*[domain%formula]{expr%formula}
\inf{expr%formula}
\inf[domain%formula]{expr%formula}
\inf*{expr%formula}
\inf*[domain%formula]{expr%formula}

\bar{expr%formula}
\Re{expr%formula}
\Im{expr%formula}