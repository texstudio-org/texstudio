# numodel package
# Matthew Bertucci 2026/10/13 for v0.11.0

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
\copymodel[options%keyvals]{source}{copy}
\copymodel{source}{copy}
\diagrammodel[options%keyvals]{xvar}{yvar}[extra]{label%plain}
\diagrammodel[options%keyvals]{xvar}{yvar}{label%plain}
\diagrammodel{xvar}{yvar}[extra]{label%plain}
\diagrammodel{xvar}{yvar}{label%plain}
\graphicmodel
\graphicmodel[options%keyvals]
\mcoordsp{prefix}{xvar}{yvar}
\mcoords{xvar}{yvar}
\mremoverule[prefix]{name}
\mremoverule{name}
\mrule*[options%keyvals]{LHS}{expr}
\mrule*{LHS}{expr}
\mrule[options%keyvals]{LHS}{expr}
\mruletext[options%keyvals]{text}
\mruletext{text}
\mrule{LHS}{expr}
\mstepatp{prefix}{name}{var}{value}
\mstepat{name}{var}{value}
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
\tablemodel[options%keyvals]{name1,name2,...}
\tablemodel{name1,name2,...}
\textmodel
\textmodel[options%keyvals]

# not documented
\numodelmaxiterwarning#S
\NumodelDefNumCs{arg1}{arg2}{arg3}{arg4}{arg5}#S
\NumodelDefPreCs{arg1}{arg2}{arg3}{arg4}#S
\NumodelDefQtyCs{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\NumodelNumInput{arg}#S
\NumodelNumRounded{arg1}{arg2}#S
\NumodelQtyInput{arg1}{arg2}#S
\NumodelQtyRounded{arg1}{arg2}{arg3}#S
\NumodelStartNum{arg1}{arg2}{arg3}{arg4}#S
\NumodelStartQty{arg1}{arg2}{arg3}{arg4}{arg5}#S