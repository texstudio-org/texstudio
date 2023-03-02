# qrbill package
# Matthew Bertucci 2022/10/20 for v1.07

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
debtorprefix=%<string%>
data-to-string#true,false
font=%<font name%>
frame=#true,false,top,bottom,none
ibanseparator=%<token list%>
icon=#swiss-cross,%<file name%>
iconwidth=##L
ignore-if-empty={%<comma list%>}
qrmode=#package,lua
qrscheme=%<name%>
referenceseparator=%<token list%>
sep-iban=%<integer%>
sep-reference=%<integer%>
separate=#false,text,symbol
replace-tilde#true,false
replace-umlauts#true,false
vrule=#true,false,symbol
#endkeyvals

#ifOption:qrmode=lua
#include:luatex
#endif

#ifOption:separate=symbol
#include:marvosym
#endif

#ifOption:vrule=symbol
#include:marvosym
#endif

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
