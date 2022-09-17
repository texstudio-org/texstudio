# qrbill package
# Matthew Bertucci 2022/09/17 for v1.05

#include:iftex
#include:l3keys2e
#include:fontspec
#include:anyfontsize
#include:scrbase
#include:graphicx
#include:numprint
#include:qrcode

#keyvals:\usepackage/qrbill#c
billinginfo#true,false
creditorprefix=%<string%>
data-to-string#true,false
debtorprefix=%<string%>
font=%<font name%>
frame=#true,false,top,bottom,none
ibanseparator=%<token list%>
icon=%<file name%>
iconwidth=##L
qrscheme=%<name%>
referenceseparator=%<token list%>
replace-tilde#true,false
replace-umlauts#true,false
sep-iban=%<integer%>
sep-reference=%<integer%>
separate=#false,text,symbol
#endkeyvals

\QRbill
\QRbill[data setup%keyvals]
\QRbill*
\QRbill*[data setup%keyvals]
\qrbillsetdata{data setup%keyvals}
\qrbillsetdata*{data setup%keyvals}
\SetupQrBill{data setup%keyvals}
\qrbillsetup{data setup%keyvals}#*

#keyvals:\QRbill,\QRbill*,\SetupQrBill,\qrbillsetdata,\qrbillsetdata*,\qrbillsetup
QRType=
Version=
CodingType=
Account=
CR-AddressType=
CR-Name=
CR-Address1=
CR-Address2=
CR-PostalCode=
CR-City=
CR-Country=
UCR-AddressType=
UCR-Name=
UCR-Address1=
UCR-Address2=
UCR-ZIP=
UCR-City=
UCR-Country=
Amount=
Currency=
UD-AddressType=
UD-Name=
UD-Address1=
UD-Address2=
UD-PostalCode=
UD-City=
UD-Country=
ReferenceType=
Reference=
Message=
Trailer=
BillingInfo=
AV1-Parameters=
AV2-Parameters=
creditor=
creditor*=
debtor=
debtor*=
AV1=
AV2=
invoicenum=
invoicedate=
customerref=
vat=
vatdate=
vatdetails=
importvat=
conditions=
#endkeyvals

\QRbillParseDate{year}{month}{day}

\QRbillAddCustomReplacement{string}{replacement}

\insertcreditor
\insertcurrency
\insertdebtor

\SetStaticData{arg}#*
\SetBillingInfoScheme{scheme data}#*
\SetQrScheme{scheme data}#*
\qrbillfont#*
\qrblack#S
\qrwhite#S
\qrnewline#S
