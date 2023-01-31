# milog class
# Matthew Bertucci 2022/09/09 for v1.0

#include:xkeyval
#include:xkvltxp
#include:geometry
#include:tabularx
#include:booktabs
#include:colortbl
#include:xifthen
#include:background
#include:transparent
#include:pgfplotstable

\milog{CSV file%file}
\milog[options%keyvals]{CSV file%file}
\Formular
\milogsetup{options%keyvals}

#keyvals:\milog,\milogsetup
color=#%color
companyname=%<Firma%>
company=%<Firmenname%>
namename=%<Name, Vorname%>
name=%<name%>
idname=%<Geburtsdatum, Personalnummer%>
id=%<Zusatz-Id%>
monthname=%<Monat/Jahr%>
month=%<Monat%>
heading=%<Überschrift%>
cc#true,false
#endkeyvals
