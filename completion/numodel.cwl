# numodel package
# Matthew Bertucci 2026/06/08 for v0.7.0

#include:amsmath
#include:amssymb
#include:xfrac
#include:tikz
#include:tikzlibraryshapes.symbols
#include:luacode
#include:siunitx
#include:float
#include:tabularray
#include:numodel-plot

\computemodel
\computemodel[options%keyvals]
\diagrammodel[options%keyvals]{xvar}{yvar}[extra]{label%plain}
\diagrammodel[options%keyvals]{xvar}{yvar}{label%plain}
\diagrammodel{xvar}{yvar}[extra]{label%plain}
\diagrammodel{xvar}{yvar}{label%plain}
\graphicmodel
\graphicmodel[options%keyvals]
\mcoordsp{prefix}{xvar}{yvar}
\mcoords{xvar}{yvar}
\mrule*[options%keyvals]{LHS}{expr}
\mrule*{LHS}{expr}
\mrule[options%keyvals]{LHS}{expr}
\mruletext[options%keyvals]{text}
\mruletext{text}
\mrule{LHS}{expr}
\mstepp{prefix}{name}{i}
\mstep{name}{i}
\mstop[options%keyvals]{expr}
\mstop{expr}
\mvar[options%keyvals]{name}{text}{start}{unit}{sig}{type}
\mvar{name}{text}{start}{unit}{sig}{type}
\newmodelprefix{name}
\NumodelForEachVar{code}
\numodelsetup{options%keyvals}
\switchmodelprefix{name}
\textmodel
\textmodel[options%keyvals]

# not documented
\NumodelDefNumCs{arg1}{arg2}{arg3}#S
\NumodelDefPreCs{arg1}{arg2}{arg3}{arg4}#S
\NumodelDefQtyCs{arg1}{arg2}{arg3}{arg4}#S