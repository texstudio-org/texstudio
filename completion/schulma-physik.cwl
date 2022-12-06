# schulma-physik package
# Matthew Bertucci 2/16/2022 for v1.2

#include:siunitx
#include:tikz
#include:tikzlibrarycircuits.ee.IEC

\Massstab{Zahl1}{Einheit1%formula}{Zahl2}{Einheit2%formula}
\tqty{Zahl}{Einheit%formula}
\tunit{Einheit%formula}
\Beschl{Zahl}
\Erdb
\Ortsf
\Elem
\Elekm
\Lichtg
\Planck
\EFK
\MFK
\MFK*
\Messschieber{Messwert}
\Messschraube{Messwert}

#keyvals:\node#c
bulb
resistor
capacitor
inductor
diode
diode=light emitting
spannungsquelle
battery
battery=adjustable
contact
amperemeter
voltmeter
messgeraet
#endkeyvals

#keyvals:\begin{tikzpicture}#c
circuit ee IEC
#endkeyvals

# deprecated
\tSI{Zahl}{Einheit%formula}#S
\tsi{Einheit%formula}#S
