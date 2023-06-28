# cooking-units package
# Matthew Bertucci 2022/12/11 for v3.00

#include:translations
#include:xfrac
#include:l3keys2e

#ifOption:use-fmtcount-numerals
#include:fmtcount
#endif
#ifOption:use-fmtcount-numerals=true
#include:fmtcount
#endif

#keyvals:\usepackage/cooking-units#c
use-fmtcount-numerals#true,false
#endkeyvals

\cunum{amount}{unit}
\cunum[options%keyvals]{amount}{unit}
\cunum<label>{amount}{unit}#r
\cunum<label>[options%keyvals]{amount}{unit}#r
\cunum<label>[options%keyvals]{amount}[space%l]{unit}#*r

\cutext{amount}{unit}
\cutext[options%keyvals]{amount}{unit}
\cutext<label>{amount}{unit}#r
\cutext<label>[options%keyvals]{amount}{unit}#r

\Cutext{amount}{unit}
\Cutext[options%keyvals]{amount}{unit}
\Cutext<label>{amount}{unit}#r
\Cutext<label>[options%keyvals]{amount}{unit}#r

\cuam{amount}
\cuam[options%keyvals]{amount}
\cuam<label>{amount}#r
\cuam<label>[options%keyvals]{amount}#r

\cusetup{options%keyvals}

\cudeclareunitgroup{group name}{unit list}
\cuaddtounitgroup{group name}{unit list}

#keyvals:\cunum#c,\cutext#c,\Cutext#c,\cuam#c,\cusetup#c
%<old unit%>=%<new unit%>
%<group%>=%<unit%>
add-unit-to-group={%<group={unit list},...%>}
set-option-for-%<unit%>={%<keyvals%>}
add-option-for-%<unit%>={%<keyvals%>}
set-option-for={%<unit={keyvals},...%>}
add-option-for={%<unit={keyvals},...%>}
erase-all-options
erase-all-options-for={%<unit list%>}
cutext-to-cunum#true,false
cutext-change-unit#true,false
cuam-version=#old,new
cutext-version=#old,new
commands-add-hook={%<code%>}
cunum-add-hook={%<code%>}
cutext-add-hook={%<code%>}
Cutext-add-hook={%<code%>}
cuam-add-hook={%<code%>}
expand-both=#n,o,f,x
expand-amount=#n,o,f,x
expand-unit=#n,o,f,x
set-special-sign={%<characters%>}
add-special-sign={%<characters%>}
set-unknown-message=#error,warning,none
set-cutext-translation-message=#error,warning,none
print-numerals#true,false
use-numerals-below=%<integer%>
numeral-function=%<function%>
Numeral-function=%<function%>
parse-number#true,false
range-sign=%<string%>
cunum-range-sign=%<string%>
cutext-range-sign=%<string%>
use-phrases#true,false
round-precision=%<integer%>
round-to-int#true,false
round-half=#default,commercial
eval-fraction#true,false
convert-fraction#true,false
fraction-inline={%<input%>}
mixed-fraction-space=##L
cutext-space=%<string%>
phrase-space=%<string%>
amount-unit-space=%<string%>
times-space=%<string%>
recalculate-amount#true,false
set-number-of-persons=%<integer%>
label=%<string%>*%<integer%>
get-label=%<label%>
ref=%<label%>
curef-add-forbidden-unit={%<unit list%>}
curef-remove-forbidden-unit={%<unit list%>}
curef-clear-forbidden-units#true,false
check-temperature#true,false
add-temperature-to-check={%<unit=min value,...%>}
convert-to-eV#true,false
add-natural-unit=%<unit%>
42#true,false
nothing-special#true,false
going-bonkers#true,false
fully-bonkers#true,false
xD-lol#true,false
#endkeyvals

\culabel{label}{number of persons}#l
\curef{label}#r

\declarecookingunit{unit}
\declarecookingunit[options%keyvals]{unit}
\newcookingunit{unit}
\newcookingunit[options%keyvals]{unit}
\providecookingunit{unit}
\providecookingunit[options%keyvals]{unit}

#keyvals:\declarecookingunit#c,\newcookingunit#c,\providecookingunit#c
symbol=%<symbol%>
gender=#m,f,n
set-options={%<keyvals%>}
add-to-group=%<group%>
natural-unit#true,false
#endkeyvals

\declarecookingderivatives{unit list}{unit}{relation}{unit symbol}#*
\cudefinekeychain{key specs}#*
\cudefinesinglekey{key%plain}{key specs}#*
\cuaddtokeychain{key specs}#*
\cuaddsinglekeys{key%plain}{key specs}#*

\cudefinename{language}{specs}#*
\cudefinesymbol{language}{specs}#*
\cudefinephrase{language}{specs}#*

\cusetoptionfor{unit list}{options}#*
\cuaddoptionfor{unit list}{options}#*
\cuclearoptionfor{unit list}#*

# obsolete
\cudefinekeys#S
\cuaddkeys#S
\cuaddtokeys#S
