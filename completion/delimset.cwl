# delimset package
# Matthew Bertucci 2024/07/17 for v2.0

#include:amsmath
#include:keyval

#keyvals:\usepackage/delimset#c
stddef#true,false
extdef#true,false
scriptstyle#true,false
#endkeyvals

\delimsize#L
\kerndelim{width}

\usedelim

\delim{%<l%>}{%<r%>}%<flags%>{%<expr%>}#m
\delimpair{%<l%>}{%<m%>}{%<r%>}%<flags%>{%<expr1%>}{%<expr2%>}#m
\delimtriple{%<l%>}{%<m1%>}{%<m2%>}{%<r%>}%<flags%>{%<expr1%>}{%<expr2%>}{%<expr3%>}#m

\DeclareMathDelimiterSet{command}{definition}#d
\DeclareMathDelimiterSet{command}[args]{definition}#d
\selectdeliml{delim}
\selectdeliml*{delim}
\selectdelim{delim}
\selectdelim*{delim}
\selectdelim[class%plain]{delim}
\selectdelim[class%plain]*{delim}
\selectdelimr{delim}
\selectdelimr*{delim}
\DeclareMathDelimiterSel{command}{left-def%definition}{right-def%definition}#d
\parsedelimflags{compositor}{selector}

\brk%<flags%>{%<expr%>}#m
\brk[%<type%>]%<flags%>{%<expr%>}#m
# following line allows for keyval completion even with
# odd syntax in lines above. Similarly for \eval, etc. below
\brk[%<options%>]#Sm

#keyvals:\brk
r
s
c
a
#endkeyvals

\eval%<flags%>{%<expr%>}#m
\eval[%<type%>]%<flags%>{%<expr%>}#m
\eval[%<options%>]#Sm

#keyvals:\eval
v
s
#endkeyvals

\abs%<flags%>{%<expr%>}#m
\norm%<flags%>{%<expr%>}#m

#ifOption:extdef
\pair%<flags%>{%<expr1%>}{%<expr2%>}#m
\set%<flags%>{%<expr%>}#m
\setcond%<flags%>{%<expr%>}{%<cond%>}#m
\intv%<flags%>{%<expr1%>}{%<expr2%>}#m
\intv[%<type%>]%<flags%>{%<expr1%>}{%<expr2%>}#m
\intv[%<options%>]#Sm
#keyvals:\intv
c
o
l
r
#endkeyvals
\avg%<flags%>{%<expr%>}#m
\corr%<flags%>{%<expr%>}#m
\comm%<flags%>{%<expr1%>}{%<expr2%>}#m
\acomm%<flags%>{%<expr1%>}{%<expr2%>}#m
\bra%<flags%>{%<expr%>}#m
\ket%<flags%>{%<expr%>}#m
\setcond%<flags%>{%<expr1%>}{%<expr2%>}#m
#endif

#ifOption:extdef=true
\pair%<flags%>{%<expr1%>}{%<expr2%>}#m
\set%<flags%>{%<expr%>}#m
\setcond%<flags%>{%<expr%>}{%<cond%>}#m
\intv%<flags%>{%<expr1%>}{%<expr2%>}#m
\intv[%<type%>]%<flags%>{%<expr1%>}{%<expr2%>}#m
\intv[%<options%>]#Sm
#keyvals:\intv
c
o
l
r
#endkeyvals
\avg%<flags%>{%<expr%>}#m
\corr%<flags%>{%<expr%>}#m
\comm%<flags%>{%<expr1%>}{%<expr2%>}#m
\acomm%<flags%>{%<expr1%>}{%<expr2%>}#m
\bra%<flags%>{%<expr%>}#m
\ket%<flags%>{%<expr%>}#m
\braket%<flags%>{%<expr1%>}{%<expr2%>}#m
\setcond%<flags%>{%<expr1%>}{%<expr2%>}#m
\lfrac%<flags%>{%<expr1%>}{%<expr2%>}#m
\lfrac[%<type%>]%<flags%>{%<expr1%>}{%<expr2%>}#m
#endif

\bigp#m
\bigb#m
\Bigb#m
\Biggb#m
\Biggp#m
\Bigp#m
\biggb#m
\biggp#m
\bigi#m
\Bigi#m
\biggi#m
\Biggi#m
