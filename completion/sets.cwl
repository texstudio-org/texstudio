# sets package
# Matthew Bertucci 10/18/2021 for v1.3

\newset{set%cmd}{elmt1|elmt2|...}#d
\newsetsimple{set%cmd}{elmt1|elmt2|...}#d
\listset{set}
\setseparator#*
\sizeofset{set}\is{counter}
\is#S
\iselementofset{element}{set}
\unionsets{set1}{set2}\to{set3}
\to{cmd}#Sd
\minussets{set1}\minus{set2}\to{set3}
\minus#S
\intersectsets{set1}{set2}\to{set3}
\sortset{set1}{set2%cmd}#d
\deleteduplicates{set1}{set2%cmd}#d