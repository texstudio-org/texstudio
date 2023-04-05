# Added as a workaround for a crash in TXS when it tries to autogenerate the CWL for MinionPro fonts.
# For details see https://github.com/texstudio-org/texstudio/issues/716

# updated 2023/04/04 for v2.3a

#include:kvoptions
#include:MinionPro-FontDef
#include:textcomp
#include:MnSymbol
#include:eufrak
#include:microtype
#include:fontaxes

#keyvals:\usepackage/MinionPro#c
smallfamily
medfamily
fullfamily
noopticals
opticals
slides
normalsize
nonormalsize
onlytext
onlymath
textosf
mathosf
osf
textlf
mathlf
lf
mathtabular
mnsy
cmsy
swash
abx
amsbb
fourierbb
lucidabb
mixedgreek
italicgreek
frenchmath
scale=%<factor%>
minionint
openg
loosequotes
footnotefigures
#endkeyvals

\figureversion{type%keyvals}

#keyvals:\figureversion
text
osf
lining
lf
tabular
tab
proportional
prop
#endkeyvals

\digamma#m
\varkappa#m
\varbeta#m
\backepsilon#m
\varbackepsilon#m
\lambdabar#m
\lambdaslash#m
\slashedzero#m
\openg#m
\eth#m
\Bbbk#m
\mathbb{text%plain}#m
\uphbar#*m
\uppartial#*m
\upell#*m
\upimath#*m
\upjmath#*m
\varsmallint#*m
\varint#*m
\variint#*m
\variiint#*m
\variiiint#*m
\varidotsint#*m
\varlandupint#*m
\varlanddownint#*m
\varstrokedint#*m
\varoint#*m
\varoiint#*m
\varrcirclerightint#*m
\varlcirclerightint#*m
\varrcircleleftint#*m
\varlcircleleftint#*m
\varsumint#*m

\smallfrac{numerator}{denominator}
\slantfrac{numerator}{denominator}

\ibycusdefault#S
