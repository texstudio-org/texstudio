# pdfswitch package
# Matthew Bertucci 2/3/2022 for v2.4.3

#include:ae
#include:aeguill
#include:ifthen
#include:ifpdf
#include:etoolbox
#include:hyperref
#include:xcolor
#include:graphicx
#include:thumbpdf

#keyvals:\usepackage/pdfswitch#c
nocolor
backref
pagebackref
noborder
plainpages
#endkeyvals

pdfurlcolor#B
pdfcitecolor#B
pdflinkcolor#B

#ifOption:backref
#include:backref
#endif

#ifOption:pagebackref
#include:backref
#endif