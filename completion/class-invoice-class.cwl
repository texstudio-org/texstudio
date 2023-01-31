# invoice-class class
# Matthew Bertucci 2022.06/24 for v1.0

#include:geometry
#include:datatool
#include:multicol
#include:array
#include:tabularx
#include:longtable
#include:dcolumn
#include:fancyhdr

\ConfigPrefix{file prefix}
\InputFile{CSV file%file}
\waybill{number}
\shippingdate{date}
\toaddress{address%text}
\destination{country}
\carrier{carrier name}
\weight{pounds}{ounces}
\packages{number}
\packingcost{cost}
\shippingcost{cost}
\insurancecost{cost}
\fromaddress{address%text}
\shipper{name}
\location{location%text}
\printinvoice
