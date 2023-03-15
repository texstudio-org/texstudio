# schulma-physik package
# Matthew Bertucci 2023/03/15 for v1.4

#include:siunitx
#include:tikz
#include:tikzlibrarycircuits.ee.IEC

#keyvals:\usepackage/schulma-physik#c
circuitikz
#endkeyvals

#ifOption:circuitikz
#include:circuitikz
#endif

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
\Messschieber[cm|inch|cm+inch]{Messwert}
\Messschraube{Messwert}
\Kraftmesser{Messwert}{Maximalausschlag}

#keyvals:\node#c
spannungsquelle
messgeraet
#endkeyvals

# deprecated
\tSI{Zahl}{Einheit%formula}#S
\tsi{Einheit%formula}#S
