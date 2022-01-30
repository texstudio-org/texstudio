# typogrid package
# Matthew Bertucci 1/29/2022 for v0.21

#include:calc
#include:keyval
#include:eso-pic

#keyvals:\usepackage/typogrid#c
draft
final
colorgrid
grid
#endkeyvals

\typogridsetup{options%keyvals}

#keyvals:\usepackage/typogrid#c,\typogridsetup
columns=%<number%>
headings#true,false
margin#true,false
#endkeyvals

\typogrid
\gridwidth