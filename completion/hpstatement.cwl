# hpstatement package
# Matthew Bertucci 2022-05-09 for v2.00

#include:l3keys2e
#include:iflang

\hpsetup{options%keyvals}

#keyvals:\usepackage/hpstatement#c,\hpsetup
date=%<YYYY-MM-DD%>
#endkeyvals

\hpnumber{number}
\hpnumber[text1%text]{number}
\hpnumber[text1%text][text2%text]{number}
\hpstatement{number}
\hpstatement[text1%text]{number}
\hpstatement[text1%text][text2%text]{number}