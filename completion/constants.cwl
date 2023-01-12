# constants package
# Matthew Bertucci 2/8/2022 for v.1

#include:keyval

\C#m
\C[family]#m
\Cl{label%specialDef}#s#%constantslabel
\Cl[family]{label}

\Cr{label%keyvals}#m
\pagerefconstant{label%keyvals}

#keyvals:\Cr#c,\pagerefconstant#c
%constantslabel
#endkeyvals

\resetconstant
\resetconstant[family]

\newconstantfamily{family name}{options%keyvals}
\renewconstantfamily{family name}{options%keyvals}

#keyvals:\newconstantfamily,\renewconstantfamily
format=%<font command%>
symbol=%<symbol%>
reset=%<counter%>
#endkeyvals

\newlabelconstant{label}{{number}{page}{family}}#*
\refconstant{label}#*
\familyconstant{label}#*
\counterconstant{label}#*
\refstepcounterconstant{counter}#*
\labelconstant{label}{family}#*