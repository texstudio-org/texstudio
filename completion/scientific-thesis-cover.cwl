# scientific-thesis-cover package
# Matthew Bertucci 1/8/2021 for v4.0.2

#include:kvoptions
#include:ifthen

#keyvals:\usepackage/scientific-thesis-cover#c
language=#german,english
title={%<title text%>}
author={%<author%>}
type=#bachelor,master,diplom,study,projectinf,{%<text%>}
institute=#iaas,ipvs,fmi,iste,iti,iris,vis,visus,sec,fac,{%<text%>}
course=#cs,se,mcl,msv,bis,simtech,{%<text%>}
examiner={%<examiner%>}
supervisor={%<supervisor%>}
startdate={%<YYYY-MM-DD%>}
enddate={%<YYYY-MM-DD%>}
crk={%<classification codes%>}
number=%<number%>
setPageNumberToOne#true,false
setCoverPageNumberToMinusOne#true,false
#endkeyvals

\Coverpage
\Affirmation

\ifinputencloaded#*
\inputencloadedtrue#*
\inputencloadedfalse#*
\labelsenglish#*
\labelsgerman#*
\Titelblatt#*
\Versicherung#*