# pbalance package
# Matthew Bertucci 2022/07/30 for v1.4.0

#include:etoolbox
#include:expl3
#include:atbegshi
#include:atveryend
#include:zref-abspage
#include:filehook
#include:balance

#keyvals:\usepackage/pbalance#c
safe
draft
#endkeyvals

\shrinkLastPage{dimen%l}
\balancePageNum{page-number}
\nopbalance
