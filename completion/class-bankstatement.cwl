# bankstatement class
# Matthew Bertucci 11/10/2021 for v0.9.2

#include:xkeyval
#include:xkvltxp
#include:geometry
#include:longtable
#include:tabularx
#include:xcolor
#include:graphicx
#include:booktabs
#include:datatool
#include:calc
#include:ifthen
#include:siunitx

\bankstatement{csv file%file}
\bankstatement[options%keyvals]{csv file%file}

#keyvals:\bankstatement
title=%<title%>
logo=%<logo%>
logowidth=##L
holder=%<account holder%>
bic=%<BIC%>
iban=%<IBAN%>
referencewidth=##L
negativecolor=#%color
sort=%<sort key%>
openingbalance=
closingbalance=
#endkeyvals
