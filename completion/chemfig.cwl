# chemfig package
# Matthew Bertucci 10/14/2021 for v1.6b

#include:simplekv
#include:tikz

\chemfig{code%formula}
\chemfig[options%keyvals]{code%formula}
\setchemfig{options%keyvals}

#keyvals:\chemfig,\setchemfig
chemfig style=
atom style=
bond join#true,false
fixed length#true,false
cram rectangle#true,false
cram width=##L
cram dash width=##L
cram dash sep=##L
atom sep=##L
bond offset=##L
double bond sep=##L
angle increment=%<degrees%>
node style=
bond style=
cycle radius coeff=
stack sep=##L
show cntcycle#true,false
autoreset cntcycle#true,false
compound style=
compound sep=
arrow offset=##L
arrow angle=%<degrees%>
arrow coeff=
arrow style=
arrow double sep=##L
arrow double coeff=
arrow double harpoon#true,false
arrow label sep=##L
arrow head=
+ sep left=##L
+ sep right=##L
+ vshift=##L
#endkeyvals

#keyvals:\setchemfig
debug#true,false
scheme debug#true,false
#endkeyvals

\resetchemfig

\printatom{code}#*

\hflipnext
\vflipnext

\definesubmol{name%cmd}{code%formula}#d
\definesubmol{name%cmd}[code1%formula]{code2%formula}#d
\redefinesubmol{name%cmd}{code%formula}#d
\redefinesubmol{name%cmd}[code1%formula]{code2%formula}#d

\chemskipalign

\charge{[%<parameters%>]%<position%>[%<TikZ code%>]}{%<atom%>}
\Charge{[%<parameters%>]%<position%>[%<TikZ code%>]}{%<atom%>}

\setcharge{options%keyvals}

#keyvals:\setcharge
debug#true,false
macro atom=%<cmd%>
circle#true,false
macro charge=%<cmd%>
extra sep=##L
overlay#true,false
shortcuts#true,false
lewisautorot#true,false
.radius=##L
:sep=##L
.style=
"length=##L
"width=##L
"style=
|style=
#endkeyvals

\resetcharge
\chargeangle

\chemmove %<TikZ code%>
\chemmove[%<TikZ options%>] %<TikZ code%>

\chemabove{txt1%formula}{txt2%formula}
\chemabove[dim%l]{txt1%formula}{txt2%formula}
\chembelow{txt1%formula}{txt2%formula}
\chembelow[dim%l]{txt1%formula}{txt2%formula}
\Chemabove{txt1%formula}{txt2%formula}
\Chemabove[dim%l]{txt1%formula}{txt2%formula}
\Chembelow{txt1%formula}{txt2%formula}
\Chembelow[dim%l]{txt1%formula}{txt2%formula}

\chemname{molecule}{name}
\chemname[dim%l]{molecule}{name}
\chemname*{name}#*
\chemnameinit{arg}

\schemestart
\schemestart[angle,coeff,style]
\schemestart[angle,coeff,style][position]
\schemestop

\arrow
\arrow[angle,coeff,style]
\arrow{type}
\arrow{type}[angle,coeff,style]
\arrow(%<n1.a1%>[%<s1%>]--%<n2.a2%>[%<s2%>]){%<type%>}[%<angle,coeff,style%>]

\setcompoundstyle{TikZ code}

\+#S
\|#S

\subscheme{code}

\definearrow{number}{name}{code}

\chemleft{delim%formula}
\chemright{delim%formula}
\chemup{delim%formula}
\chemdown{delim%formula}

\polymerdelim{node1}{node2}
\polymerdelim[options%keyvals]{node1}{node2}

#keyvals:\polymerdelim
delimiters=
height=##L
depth=##L
h align#true,false
auto rotate#true,false
rotate=%<degrees%>
open xshift=##L
close x shift=##L
indice=%<integer%>
#endkeyvals

\merge{%<dir%>}(%<n1.a1%>)%<(n2.a2)...(ni.ai)%>--(%<n.a[s]%>)
\merge{%<dir%>}(%<n1.a1%>)%<(n2.a2)...(ni.ai)%>--(%<n.a[s]%>)[%<c1,c2,c,style%>]
\merge{%<dir%>}[%<labelup%>][%<labeldown%>](%<n1.a1%>)%<(n2.a2)...(ni.ai)%>--(%<n.a[s]%>)[%<c1,c2,c,style%>]

\CFver#S
\CFname#S
\CFver#S
\CFdate#S