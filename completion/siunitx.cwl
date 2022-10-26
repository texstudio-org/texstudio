# dbitouze/2015-03-20 for siunitx v2.6e
# thatlittleboy/2018-06-18
# r0the/2021-10-07 for siunitx v3
# Matthew Bertucci 2022-10-24 for v3.1.9

#include:translations
#include:amstext
#include:color
#include:l3keys2e
#include:array

#ifOption:use-xspace
#include:xspace
#endif

\A#*
\ampere
\amu#*
\ang[%<options%>]{%<angle%>}
\ang{%<angle%>}
\arcminute
\arcsecond
\as#*
\astronomicalunit
\atto#*
\becquerel
\bel
\bit
\byte
\C#*
\candela
\centi
\cm#*
\complexnum{%<number%>}
\complexnum[%<options%>]{%<number%>}
\complexqty{number}{unit%formula}
\complexqty[options%keyvals]{number}{unit%formula}
\coulomb
\cubed
\cubic
\dalton
\dB#*
\deca
\deci
\decibel
\DeclareSIPower{symbol-before%cmd}{symbol-after%cmd}{power}#d
\DeclareSIPrefix{prefix macro%cmd}{symbol}{power of 10}#d
\DeclareSIQualifier{qualifier%cmd}{symbol}#d
\DeclareSIUnit[options%keyvals]{unit%cmd}{definition}#d
\DeclareSIUnit{unit%cmd}{definition}#d
\degreeCelsius
\degree
\deka
\dm#*
\electronvolt
\eV#*
\exa
\exbi
\F#*
\farad
\femto
\fF#*
\fg#*
\fH#*
\fmol#*
\fs#*
\g#*
\GeV#*
\GHz#*
\gibi
\giga
\GPa#*
\gram
\gray
\GW#*
\hectare
\hecto
\henry
\hertz
\highlight
\hL#*
\hl#*
\hour
\Hz#*
\J#*
\joule
\K#*
\kA#*
\katal
\kelvin
\keV#*
\kg#*
\kHz#*
\kibi
\kilo
\kilogram
\kJ#*
\km#*
\kmol#*
\kN#*
\kohm#*
\kPa#*
\kV#*
\kW#*
\kWh#*
\L#*
\l#*
\liter
\litre
\lumen
\lux
\m#*
\mA#*
\mC#*
\mebi
\mega
\meter
\metre
\MeV#*
\meV#*
\mg#*
\mH#*
\MHz#*
\mHz#*
\micro
\milli
\minute
\mJ#*
\mL#*
\ml#*
\mm#*
\mmol#*
\MN#*
\mN#*
\Mohm#*
\mohm#*
\mol#*
\mole
\mp#*
\MPa#*
\ms#*
\mV#*
\MW#*
\mW#*
\N#*
\nA#*
\nano
\nC#*
\neper
\newton
\nF#*
\ng#*
\nm#*
\nmol#*
\ns#*
\num[%<options%>]{%<number%>}
\num{%<number%>}
\numlist[%<options%>]{%<numbers%>}
\numlist{%<numbers%>}
\numproduct[%<options%>]{%<numbers%>}
\numproduct{%<numbers%>}
\numrange[%<options%>]{%<number1%>}{%<number2%>}
\numrange{%<number1%>}{%<number2%>}
\nV#*
\nW#*
\of{text%plain}
\ohm
\Pa#*
\pA#*
\pascal
\pebi
\per
\percent
\peta
\pF#*
\pg#*
\pH#*
\pico
\pm#*
\pmol#*
\ps#*
\pV#*
\qty[options%keyvals]{number}{unit%formula}
\qty{number}{unit%formula}
\qtylist[options%keyvals]{numbers}{unit%formula}
\qtylist{numbers}{unit%formula}
\qtyproduct[options%keyvals]{numbers}{unit%formula}
\qtyproduct{numbers}{unit%formula}
\qtyrange[options%keyvals]{number1}{number2}{unit%formula}
\qtyrange{number1}{number2}{unit%formula}
\radian
\raiseto{%<power%>}
\s#*
\second
\siemens
\sievert
\sisetup{%<options%>}
\square
\squared
\steradian
\tablenum{%<number%>}#t
\tablenum[%<options%>]{%<number%>}#t
\tebi
\tera
\tesla
\TeV#*
\THz#*
\tonne
\tothe{%<power%>}
\uA#*
\uC#*
\uF#*
\ug#*
\uH#*
\uJ#*
\uL#*
\ul#*
\um#*
\umol#*
\unit[options%keyvals]{unit%formula}
\unit{unit%formula}
\us#*
\uV#*
\uW#*
\V#*
\volt
\W#*
\watt
\weber
\yobi
\yocto
\yotta
\zebi
\zepto
\zetta

# deprecated
\angstrom#S
\atomicmassunit#S
\bar#S
\barn#S
\bohr#S
\celsius#S
\clight#S
\DeclareBinaryPrefix{prefix macro%cmd}{symbol}{power of 2}#*d
\DeclareSIPostPower{power macro%cmd}{number}#*d
\DeclareSIPrePower{power macro%cmd}{number}#*d
\electronmass#S
\elementarycharge#S
\hartree#S
\knot#S
\mmHg#S
\nauticalmile#S
\planckbar#S
\SendSettingsToPgf#S
\SI[options%keyvals]{value}[pre-unit%formula]{unit commands%formula}#*
\SI[options%keyvals]{value}{unit commands%formula}#*
\SI{value}[pre-unit%formula]{unit commands%formula}#*
\SI{value}{unit commands%formula}#*
\si[options%keyvals]{unit%formula}#*
\si{unit%formula}#*
\SIlist{values}{unit commands%formula}#*
\SIlist[options%keyvals]{values}{unit commands%formula}#*
\SIrange{value1}{value2}{unit commands%formula}#*
\SIrange[options%keyvals]{value1}{value2}{unit commands%formula}#*
\SIUnitSymbolAngstrom#S
\SIUnitSymbolArcminute#S
\SIUnitSymbolArcsecond#S
\SIUnitSymbolCelsius#S
\SIUnitSymbolDegree#S
\SIUnitSymbolMicro#S
\SIUnitSymbolOhm#S

# Options
## 4.2 Printing
#keyvals:\sisetup,\ang,\complexnum,\complexqty,\DeclareSIUnit,\num,\numlist,\numproduct,\numrange,\qty,\qtylist,\qtyproduct,\qtyrange,\tablenum,\unit,\SI,\si,\SIlist,\SIrange
color=#%color
mode=#match,math,text
number-color=#%color
number-mode=#match,math,text
propagate-math-font#true,false
reset-math-version#true,false
reset-text-family#true,false
reset-text-series#true,false
reset-text-shape#true,false
text-family-to-math#true,false
text-subscript-command=%<command%>
text-superscript-command=%<command%>
text-font-command=%<commands%>
text-series-to-math#true,false
unit-color=#%color
unit-mode=#match,math,text
#endkeyvals

## 4.3 Parsing numbers
#keyvals:\sisetup,\ang,\complexnum,\complexqty,\DeclareSIUnit,\num,\numlist,\numproduct,\numrange,\qty,\qtylist,\qtyproduct,\qtyrange,\tablenum,\SI,\si,\SIlist,\SIrange
evaluate-expression#true,false
expression=%<expression%>
input-close-uncertainty=%<symbols%>
input-comparators=%<symbols%>
input-decimal-markers=%<symbols%>
input-digits=%<symbols%>
input-exponent-markers=%<symbols%>
input-ignore=%<symbols%>
input-open-uncertainty=%<symbols%>
input-signs=%<symbols%>
input-uncertainty-signs=%<symbols%>
parse-numbers#true,false
retain-explicit-decimal-marker#true,false
retain-explicit-plus#true,false
retain-negative-zero#true,false
retain-zero-uncertainty#true,false
#endkeyvals

# following math commands allowed in arg of \num etc.; listed here so not marked invalid
\ll
\gg
\le
\ge

## 4.4 Post-processing numbers
#keyvals:\sisetup,\ang,\complexnum,\complexqty,\DeclareSIUnit,\num,\numlist,\numproduct,\numrange,\qty,\qtylist,\qtyproduct,\qtyrange,\tablenum,\SI,\si,\SIlist,\SIrange
drop-exponent#true,false
drop-uncertainty#true,false
drop-zero-decimal#true,false
exponent-mode=#input,fixed,engineering,scientific
fixed-exponent=%<integer%>
minimum-integer-digits=%<integer%>
minimum-decimal-digits=%<integer%>
round-half=#up,even
round-minimum=%<number%>
round-mode=#none,figures,places,uncertainty
round-pad#true,false
round-precision=%<integer%>
round-zero-positive#true,false
#endkeyvals

## 4.5 Printing numbers
#keyvals:\sisetup,\ang,\complexnum,\complexqty,\DeclareSIUnit,\num,\numlist,\numproduct,\numrange,\qty,\qtylist,\qtyproduct,\qtyrange,\tablenum,\SI,\si,\SIlist,\SIrange
bracket-ambiguous-numbers#true,false
bracket-negative-numbers#true,false
digit-group-size=%<integer%>
digit-group-first-size=%<integer%>
digit-group-other-size=%<integer%>
exponent-base=%<value%>
exponent-product=%<symbol%>
group-digits=#none,decimal,integer
group-minimum-digits=%<integer%>
group-separator=%<separator%>
negative-color=#%color
output-close-uncertainty=%<symbol%>
output-decimal-marker=%<symbol%>
output-exponent-marker=%<symbol%>
output-open-uncertainty=%<symbol%>
print-implicit-plus#true,false
print-unity-mantissa#true,false
print-zero-exponent#true,false
print-zero-integer#true,false
separate-uncertainty#true,false
tight-spacing#true,false
uncertainty-descriptor-mode=#bracket,bracket-separator,separator,subscript
uncertainty-descriptor-separator=%<separator%>
uncertainty-descriptors={%<desc1,desc2,...%>}
uncertainty-mode=#separate,compact,compact-marker,full
uncertainty-separator=%<separator%>
zero-decimal-as-symbol#true,false
zero-symbol=%<symbol%>
#endkeyvals

## 4.6 Lists, products and ranges
#keyvals:\sisetup,\numlist,\qtylist,\SIlist
list-exponents=#individual,combine-bracket,combine
list-final-separator=%<separator%>
list-pair-separator=%<separator%>
list-separator=%<separator%>
list-units=#bracket,repeat,single
#endkeyvals

#keyvals:\sisetup,\numproduct,\qtyproduct
product-exponents=#individual,combine-bracket,combine
product-mode=#symbol,phrase
product-phrase=%<text%>
product-symbol=%<symbol%>
product-units=#bracket,bracket-power,power,repeat,single
#endkeyvals

#keyvals:\sisetup,\numrange,\qtyrange,\SIrange
range-exponents=#individual,combine-bracket,combine
range-phrase=%<text%>
range-units=#bracket,repeat,single
#endkeyvals

## 4.7 Complex numbers
#keyvals:\sisetup,\complexnum,\complexqty
complex-angle-unit=#degrees,radians
complex-mode=#cartesian,polar,input
complex-root-position=#after-number,before-number
complex-symbol-angle=%<symbol%>
complex-symbol-degree=%<symbol%>
input-complex-root=%<tokens%>
output-complex-root=%<symbol%>
print-complex-unity#true,false
#endkeyvals

## 4.8 Angles
#keyvals:\sisetup,\ang
angle-mode=#arc,decimal
angle-symbol-degree=%<symbol%>
angle-symbol-minute=%<symbol%>
angle-symbol-over-decimal#true,false
angle-symbol-second=%<symbol%>
angle-separator=%<separator%>
fill-angle-degrees#true,false
fill-angle-minutes#true,false
fill-angle-seconds#true,false
number-angle-product=%<separator%>
#endkeyvals

## 4.9 Creating units
#keyvals:\sisetup
free-standing-units#true,false
overwrite-functions#true,false
space-before-unit#true,false
unit-optional-argument#true,false
use-xspace#true,false
#endkeyvals

## 4.10 Using units
#keyvals:\sisetup,\DeclareSIUnit,\qty,\qtylist,\qtyproduct,\qtyrange,\unit,\si
bracket-unit-denominator#true,false
forbid-literal-units#true,false
fraction-command=%<command%>
inter-unit-product=%<separator%>
parse-units#true,false
per-mode=#fraction,power,power-positive-first,repeated-symbol,symbol,single-symbol
display-per-mode=#fraction,power,power-positive-first,repeated-symbol,symbol,single-symbol
inline-per-mode=#fraction,power,power-positive-first,repeated-symbol,symbol,single-symbol
per-symbol-script-correction=%<separator%>
per-symbol=%<symbol%>
power-half-as-sqrt#true,false
qualifier-mode=#subscript,bracket,combine,phrase
qualifier-phrase=%<text%>
sticky-per#true,false
unit-font-command=%<command%>
#endkeyvals

## 4.11 Quantities
#keyvals:\sisetup,\DeclareSIUnit,\qty,\qtylist,\qtyproduct,\qtyrange,\SI,\SIlist,\SIrange
allow-quantity-breaks#true,false
extract-mass-in-kilograms#true,false
prefix-mode=#input,combine-exponent,extract-exponent
quantity-product=%<symbol%>
separate-uncertainty-units=#bracket,repeat,single
#endkeyvals

## 4.12 Tabular material
#keyvals:\sisetup,\tablenum
table-align-comparator#true,false
table-align-exponent#true,false
table-align-text-after#true,false
table-align-text-before#true,false
table-align-uncertainty#true,false
table-alignment=#left,center,right
table-alignment-mode=#marker,format,none
table-auto-round#true,false
table-column-width=##L
table-fixed-width=##L
table-format=%<format value%>
table-number-alignment=#left,center,right
table-text-alignment=#left,center,right,none
#endkeyvals

## 4.13 Locale options
#keyvals:\sisetup,\ang,\complexnum,\complexqty,\DeclareSIUnit,\num,\numlist,\numproduct,\numrange,\qty,\qtylist,\qtyproduct,\qtyrange,\tablenum,\unit,\SI,\si,\SIlist,\SIrange
locale=#DE,UK,US,ZA,FR
#endkeyvals

## 4.14 Preamble-only options
#keyvals:\sisetup
table-column-type=%<tokens%>
#endkeyvals

## (deprecated) Detecting Fonts ; section 5.2
#keyvals:\sisetup
detect-all
detect-display-math#true,false
detect-family#true,false
detect-inline-family=#text,math
detect-inline-weight=#text,math
detect-mode#true,false
detect-none
detect-shape#true,false
detect-weight#true,false
#endkeyvals

## (deprecated) Font settings ; section 5.3
#keyvals:\sisetup,\ang,\DeclareSIUnit,\num,\numlist,\numrange,\SI,\si,\SIlist,\SIrange
math-rm=
math-sf=
math-tt=
text-rm=
text-sf=
text-tt=
text-tt=
#endkeyvals

## (deprecated) Font settings ; section 5.3 ; with "number-"
#keyvals:\sisetup,\ang,\DeclareSIUnit,\num,\numlist,\numrange,\SI,\SIlist,\SIrange
number-math-rm=
number-math-sf=
number-math-tt=
number-text-rm=
number-text-sf=
number-text-tt=
#endkeyvals

## (deprecated) Font settings ; section 5.3 ; with "unit-"
#keyvals:\sisetup,\ang,\DeclareSIUnit,\SI,\si,\SIlist,\SIrange
unit-math-rm=
unit-math-sf=
unit-math-tt=
unit-text-rm=
unit-text-sf=
unit-text-tt=
#endkeyvals

## (deprecated) Parsing numbers ; section 5.4
#keyvals:\sisetup,\ang,\DeclareSIUnit,\num,\numlist,\numrange,\SI,\SIlist,\SIrange
input-protect-tokens=
input-symbols=
#endkeyvals

## (deprecated) Post-processing numbers ; section 5.5
#keyvals:\sisetup,\ang,\DeclareSIUnit,\num,\numlist,\numrange,\SI,\SIlist,\SIrange
add-decimal-zero#true,false
add-integer-zero#true,false
explicit-sign=
omit-uncertainty#true,false
retain-unity-mantissa#true,false
retain-zero-exponent#true,false
round-integer-to-decimal#true,false
scientific-notation=#true,false,fixed,engineering
zero-decimal-to-integer#true,false
#endkeyvals

## (deprecated) Printing numbers ; section 5.6
#keyvals:\sisetup,\ang,\DeclareSIUnit,\num,\numlist,\numrange,\SI,\SIlist,\SIrange
bracket-numbers#true,false
close-bracket=
copy-complex-root=
copy-decimal-marker=
open-bracket=
#endkeyvals

## (deprecated) Multi-part numbers ; section 5.7
#keyvals:\sisetup,\DeclareSIUnit,\num,\numlist,\SI,\SIlist
fraction-function=
input-product=
input-quotient=
output-product=
output-quotient=
quotient-mode=#symbol,fraction
#endkeyvals

## (deprecated) Angles ; section 5.9
#keyvals:\sisetup,\ang
add-arc-degree-zero#true,false
add-arc-minute-zero#true,false
add-arc-second-zero#true,false
arc-separator=
#endkeyvals

## (deprecated) Using units ; section 5.12
#keyvals:\sisetup,\DeclareSIUnit,\SI,\si,\SIlist,\SIrange
literal-superscript-as-power#true,false
power-font=#number,unit
prefixes-as-symbols#true,false
#endkeyvals

## (deprecated) Numbers with units ; section 5.13
#keyvals:\sisetup,\DeclareSIUnit,\SI,\SIlist,\SIrange
allow-number-unit-breaks#true,false
exponent-to-prefix#true,false
number-unit-product=
#endkeyvals

#keyvals:\sisetup,\DeclareSIUnit,\SI,\SIlist
multi-part-units=#brackets,repeat,single
#endkeyvals

## (deprecated) Tabular material ; section 5.14
#keyvals:\sisetup,\DeclareSIUnit
table-align-text-pre#true,false
table-align-text-post#true,false
table-comparator#true,false
table-figures-decimal=
table-figures-exponent=
table-figures-integer=
table-figures-uncertainty=
table-parse-only#true,false
table-omit-exponent#true,false
table-space-text-pre=
table-space-text-post=
table-sign-exponent#true,false
table-sign-mantissa#true,false
table-unit-alignment=#center,right,left
#endkeyvals

## (deprecated) Symbols ; section 5.15
#keyvals:\sisetup,\DeclareSIUnit,\SI,\si,\SIlist,\SIrange
math-angstrom=
math-celsius=
math-micro=
math-ohm=
text-angstrom=
text-celsius=
text-micro=
text-ohm=
#endkeyvals

#keyvals:\sisetup,\ang,\DeclareSIUnit,\SI,\si,\SIlist,\SIrange
math-arcminute=
math-arcsecond=
math-degree=
redefine-symbols#true,false
text-arcminute=
text-arcsecond=
text-degree=
#endkeyvals
