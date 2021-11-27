# titlecaps package
# Matthew Bertucci 11/26/2021 for v1.2

#include:ifnextok
#include:ifthen

\titlecap{rich text%text}
\titlecap[option]{rich text%text}
\Addlcwords{space-separated word list}
\Resetlcwords

\textnc{text}#*
\converttilde#*
\noatinsidetc#*
\usestringstringsnames#*

\SaveHardspace#S
\SoftSpace#S

# made available with \usestringstringsnames
\addlcwords#S
\resetlcwords#S
\addlcword#S
\getargs#S
\capitalizetitle#S