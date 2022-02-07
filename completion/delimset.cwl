# delimset package
# Matthew Bertucci 2/6/2022 for v1.1

#include:amsmath
#include:keyval

#keyvals:\usepackage/delimset#c
stddef#true,false
extdef#true,false
scriptstyle#true,false
#endkeyvals

\delim{%<l%>}{%<r%>}%<size%>{%<expr%>}#m
\delimpair{%<l%>}{%<m%>}{%<r%>}%<size%>{%<expr1%>}{%<expr2%>}#m
\delimtriple{%<l%>}{%<m1%>}{%<m2%>}{%<r%>}%<size%>{%<expr1%>}{%<expr2%>}{%<expr3%>}#m

\DeclareMathDelimiterSet{command}{definition}#d
\DeclareMathDelimiterSet{command}[args]{definition}#d
\selectdelim{delim}
\selectdelim[class%plain]{delim}

\brk%<size%>{%<expr%>}#m
\brk[%<type%>]%<size%>{%<expr%>}#m
# following line allows for keyval completion even with
# odd syntax in lines above. Similarly for \eval, etc. below
\brk[%<options%>]#Sm

#keyvals:\brk
r
s
c
a
#endkeyvals

\eval%<size%>{%<expr%>}#m
\eval[%<type%>]%<size%>{%<expr%>}#m
\eval[%<options%>]#Sm

#keyvals:\eval
v
s
#endkeyvals

\abs%<size%>{%<expr%>}#m
\norm%<size%>{%<expr%>}#m

#ifOption:extdef
\pair%<size%>{%<expr1%>}{%<expr2%>}#m
\set%<size%>{%<expr%>}#m
\setcond%<size%>{%<expr%>}{%<cond%>}#m
\intv%<size%>{%<expr1%>}{%<expr2%>}#m
\intv[%<type%>]%<size%>{%<expr1%>}{%<expr2%>}#m
\intv[%<options%>]#Sm
#keyvals:\intv
c
o
l
r
#endkeyvals
\avg%<size%>{%<expr%>}#m
\corr%<size%>{%<expr%>}#m
\comm%<size%>{%<expr1%>}{%<expr2%>}#m
\acomm%<size%>{%<expr1%>}{%<expr2%>}#m
\bra%<size%>{%<expr%>}#m
\ket%<size%>{%<expr%>}#m
\setcond%<size%>{%<expr1%>}{%<expr2%>}#m
#endif

#ifOption:extdef=true
\pair%<size%>{%<expr1%>}{%<expr2%>}#m
\set%<size%>{%<expr%>}#m
\setcond%<size%>{%<expr%>}{%<cond%>}#m
\intv%<size%>{%<expr1%>}{%<expr2%>}#m
\intv[%<type%>]%<size%>{%<expr1%>}{%<expr2%>}#m
\intv[%<options%>]#Sm
#keyvals:\intv
c
o
l
r
#endkeyvals
\avg%<size%>{%<expr%>}#m
\corr%<size%>{%<expr%>}#m
\comm%<size%>{%<expr1%>}{%<expr2%>}#m
\acomm%<size%>{%<expr1%>}{%<expr2%>}#m
\bra%<size%>{%<expr%>}#m
\ket%<size%>{%<expr%>}#m
\braket%<size%>{%<expr1%>}{%<expr2%>}#m
\setcond%<size%>{%<expr1%>}{%<expr2%>}#m
#endif

\bigp#m
\bigb#m
\Bigb#m
\Biggb#m
\Biggp#m
\Bigp#m
\biggb#m
\biggp#m