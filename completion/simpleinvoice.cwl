# Simpleinvoice
# Author: Mathias Lohne, mathialo@ifi.uio.no

#include:advdate
#include:hyperref
#include:url
#include:tabularx
#include:etoolbox
#include:xcolor
#include:colortbl
#include:babel

#keyvals:\usepackage/simpleinvoice#c
american
english
UKenglish
USenglish
norsk
norwegian
bokmaal
#endkeyvals

\setinvoicetitle{title}
\setinvoicenumber{number}
\setreceivername{reciever's name}
\setreceiveraddress{reciever's address}
\setname{your name}
\setaddress{your address (multiline)}{your address (single line)}
\setphonenumber{your phone number}
\setemail{your email}
\setyourref{name}
\setourref{name}
\setinvoicedate{date}
\setdeadline{days from now}
\additem{description}{price excluding vat}{vat percentage}{price including vat}
\setsubtotal{total excluding vat}
\setvat{total vat}
\settotal{total including vat}
\setaccountnumber{number}
\makeinvoice
\linesep#*
linecolor#B
