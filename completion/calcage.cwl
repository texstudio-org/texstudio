# calcage package
# Matthew Bertucci 10/5/2021 for v0.90

#include:fnumprint
#include:datenumber
#include:fp
#include:calc
#include:xkeyval
#include:kvoptions
#include:xifthen

\calcage{year}{month}{day}
\calcage[options%keyvals]{year}{month}{day}

#keyvals:\calcage
year=
month=
day=
precision=
positive#true,false
printyear#true,false
yearsuffix#true,false
numberstring#true,false
#endkeyvals
